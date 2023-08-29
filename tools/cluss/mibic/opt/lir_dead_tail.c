#include <stdio.h>
#include "lir.h"
#include "namespace.h"

/*
 * Dead tail removal:
 *   (1) Remove any label (except function starts) which isn't called anywhere
 *   (2) Remove any code which can't be reached, assuming any label is
 *       reachable, by using a DFA which kills instructions between a
 *       guaranteed branch and the next label.
 */

static void remove_dead_labels(void);
static void remove_dead_paths(void);
static int lir_targets_label(lir_instr_t *instr, id_handle_t label);
static int lir_always_branches(lir_instr_t *instr);

//{{{
void lir_opt_dead_tails(void)
{
	remove_dead_labels();
	remove_dead_paths();
}
//}}}
//{{{
static void remove_dead_labels(void)
{
	int read_pos, write_pos=0;
	int ii, dead;
	int new_instr_num = instr_num;
	const char *label_str;
	
	for(read_pos=0; read_pos<instr_num; read_pos++)
	{
		dead = 0;
		
		if(lir_data[read_pos].type == LIR_LABEL)
		{
			label_str = get_identifier_string(lir_data[read_pos].args.lbl.identifier);
			
			// Only remove internal labels, not function starts
			if( label_str[0] == '_' && label_str[1] == '_' )
			{
				dead = 1;
				
				// Check already-written instructions
				for(ii=0; ii<=write_pos; ii++) {
					if(lir_targets_label(&lir_data[ii], lir_data[read_pos].args.lbl.identifier))
					{
						dead=0;
						break;
					}
				}
				
				if(dead)
				{
					// Check not-yet-reached instructions
					for(ii=read_pos+1; ii<instr_num; ii++)
					{
						if(lir_targets_label(&lir_data[ii], lir_data[read_pos].args.lbl.identifier)) {
							dead=0;
							break;
						}
					}
				}
			}
		}
		
		lir_data[write_pos] = lir_data[read_pos];
		
		if(dead == 0)
			write_pos ++;
		else
			new_instr_num--;
	}
	
	instr_num = new_instr_num;
}
//}}}
//{{{
static void remove_dead_paths(void)
{
	int read_pos, write_pos = 0;
	int new_instr_num = instr_num;
	int dead = 0;
	
	for(read_pos=0; read_pos<instr_num; read_pos++)
	{
		if(lir_data[read_pos].type == LIR_LABEL)
		{
			dead = 0;
		}
		else if(dead && lir_data[read_pos].type != LIR_CHAR && lir_data[read_pos].type != LIR_SPLITPOINT)
		{
			new_instr_num--;
			continue;
		}
		else if(lir_always_branches(&lir_data[read_pos]))
			dead = 1;
		
		lir_data[write_pos++] = lir_data[read_pos];
	}
	
	instr_num = new_instr_num;
}
//}}}

//{{{
static int lir_targets_label(lir_instr_t *instr, id_handle_t label)
{
	switch(instr->type)
	{
		case LIR_BRA:
		case LIR_JMP:
		case LIR_CALL: case LIR_LDLBL:
		case LIR_FLINK:
			return idcmp(instr->args.target, label);
		default:
			return 0;
	}
}
//}}}
//{{{
static int lir_always_branches(lir_instr_t *instr)
{
	switch(instr->type)
	{
		case LIR_JMP:
		case LIR_RET:
			return 1;
	}
	
	return 0;
}
//}}}

