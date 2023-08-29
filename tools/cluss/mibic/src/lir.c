#include <stdio.h>
#include <stdlib.h>
#include "lir.h"
#include "util.h"
#include "compile.h"

const int num_instructions = 54;

//{{{
argument_info single_register[] = { {1, 0}         };
argument_info double_register[] = { {1, 0}, {1, 0} };
argument_info immediate_byte[]  = { {1, 0}         };
argument_info immediate_word[]  = { {2, 0}         };
argument_info immediate_long[]  = { {4, 0}         };
argument_info immediate_call[]  = { {2, 1}         };
argument_info offset_byte[]     = { {1, 1}         };
argument_info offset_word[]     = { {2, 1}         };
argument_info offset_long[]     = { {4, 1}         };
//}}}
//{{{
instruction_info_t instructions[] = {
	{ 0x00, "HLT",    1,  0,  NULL,                 id_null },
	{ 0x01, "NOP",    1,  0,  NULL,                 id_null },
	{ 0x02, "DISC",   1,  0,  NULL,                 id_null },
	{ 0x03, "DUP",    1,  0,  NULL,                 id_null },
	{ 0x04, "ALLOCA", 1,  0,  NULL,                 id_null },
	{ 0x05, "RET",    1,  0,  NULL,                 id_null },
	{ 0x06, "CALL",   3,  0,  NULL,                 id_null },
	{ 0x07, "STA",    1,  0,  NULL,                 id_null },
	{ 0x08, "MVA",    2,  1,  single_register,      id_null },
	{ 0x09, "LINK",   2,  1,  immediate_byte,       id_null },
	{ 0x0A, "CCALL",  3,  0,  NULL,                 id_null },
	{ 0x0B, "LDR",    2,  1,  single_register,      id_null },
	{ 0x0C, "LDR2",   3,  2,  double_register,      id_null },
	{ 0x0D, "STR",    2,  1,  single_register,      id_null },
	{ 0x0E, "MOV",    3,  2,  double_register,      id_null },
	{ 0x0F, "LDIB",   2,  1,  immediate_byte,       id_null },
	{ 0x10, "LDIW",   3,  1,  immediate_word,       id_null },
	{ 0x11, "LDIL",   5,  1,  immediate_long,       id_null },
	{ 0x12, "LDIZ",   1,  0,  NULL,                 id_null },
	{ 0x13, "LDIO",   1,  0,  NULL,                 id_null },
	{ 0x14, "ADD",    1,  0,  NULL,                 id_null },
	{ 0x15, "SUB",    1,  0,  NULL,                 id_null },
	{ 0x16, "MUL",    1,  0,  NULL,                 id_null },
	{ 0x17, "DIV",    1,  0,  NULL,                 id_null },
	{ 0x18, "MOD",    1,  0,  NULL,                 id_null },
	{ 0x19, "ASL",    1,  0,  NULL,                 id_null },
	{ 0x1A, "ASR",    1,  0,  NULL,                 id_null },
	{ 0x1B, "AND",    1,  0,  NULL,                 id_null },
	{ 0x1C, "OR",     1,  0,  NULL,                 id_null },
	{ 0x1D, "XOR",    1,  0,  NULL,                 id_null },
	{ 0x1E, "NEG",    1,  0,  NULL,                 id_null },
	{ 0x1F, "INCR",   2,  0,  single_register,      id_null },
	{ 0x20, "DECR",   2,  0,  single_register,      id_null },
	{ 0x21, "BOOL",   1,  0,  NULL,                 id_null },
	{ 0x22, "BOOL2",  1,  0,  NULL,                 id_null },
	{ 0x23, "NOT",    1,  0,  NULL,                 id_null },
	{ 0x24, "TEQ",    1,  0,  NULL,                 id_null },
	{ 0x25, "TLT",    1,  0,  NULL,                 id_null },
	{ 0x26, "TGT",    1,  0,  NULL,                 id_null },
	{ 0x27, "JMP",    3,  1,  offset_word,          id_null },
	{ 0x28, "BRA",    3,  1,  offset_word,          id_null },
	{ 0x29, "DEREFB", 1,  1,  NULL,                 id_null },
	{ 0x2A, "DEREFW", 1,  1,  NULL,                 id_null },
	{ 0x2B, "DEREFL", 1,  1,  NULL,                 id_null },
	{ 0x2C, "POKEB",  1,  1,  NULL,                 id_null },
	{ 0x2D, "POKEW",  1,  1,  NULL,                 id_null },
	{ 0x2E, "POKEL",  1,  1,  NULL,                 id_null },
	{ 0x2F, "LDLBL",  5,  1,  offset_long,          id_null }
	};
//}}}

lir_instr_t *lir_data = NULL;
int instr_num=0, instr_alloc=0;

static void lir_print_instruction(lir_instr_t *instruction, FILE *fout);

//{{{
void lir_write_instruction(lir_instr_t instruction)
{
	expand_table((void*)&lir_data, &instr_alloc, instr_num+1, sizeof(lir_instr_t));
	lir_data[instr_num++] = instruction;
}
//}}}
//{{{
void lir_write_inst(int op)
{
	lir_instr_t addition;
	addition.type = op;
	lir_write_instruction(addition);
}
//}}}
//{{{
void lir_write_inst_reg(int op, int reg)
{
	lir_instr_t addition;
	addition.type = op;
	addition.args.reg = reg;
	lir_write_instruction(addition);
}
//}}}
//{{{
void lir_write_inst_2_reg(int op, int reg1, int reg2)
{
	reg_pair_t regpair;
	lir_instr_t addition;
	regpair.reg1 = reg1;
	regpair.reg2 = reg2;
	addition.type = op;
	addition.args.regpair = regpair;
	lir_write_instruction(addition);
}
//}}}
//{{{
void lir_write_inst_immediate(int op, long val)
{
	lir_instr_t addition;
	addition.type = op;
	addition.args.immed_val = val;
	lir_write_instruction(addition);
}
//}}}
//{{{
void lir_write_inst_label(int op, id_handle_t label)
{
	lir_instr_t addition;
	addition.type = op;
	addition.args.target = label;
	lir_write_instruction(addition);
}
//}}}
//{{{
void lir_write_label(id_handle_t identifier)
{
	lir_write_label_flags(identifier, CODE_LABEL_FLAGS, 0, 0);
}
//}}}
//{{{
void lir_write_label_flags(id_handle_t identifier, short flags, short forced_offset, char force_offset)
{
	lir_instr_t addition;
	addition.type = LIR_LABEL;
	addition.args.lbl.identifier = identifier;
	addition.args.lbl.flags = flags;
	addition.args.lbl.force_offset = force_offset;
	addition.args.lbl.forced_offset = forced_offset;
	lir_write_instruction(addition);
}
//}}}

//{{{
void lir_print(void)
{
	int i;
	FILE *fout;
	if(output_filename) {
		fout = fopen(output_filename, "w");
		if(!fout) {
			error_opening_file(output_filename);
			exit(1);
		}
	} else
		fout = stdout;
	
	for(i=0; i<instr_num; i++)
		lir_print_instruction(&lir_data[i], fout);
	
	fclose(fout);
}
//}}}

//{{{
static void lir_print_instruction(lir_instr_t *instruction, FILE *fout)
{
	if(instruction->type >= num_instructions)
	{
		switch(instruction->type)
		{
			case LIR_LABEL:
				if(instruction->args.lbl.forced_offset) {
					fprintf(fout, ".EXTERN %s %i %i:\n",
						get_identifier_string(instruction->args.lbl.identifier),
						(int)instruction->args.lbl.flags,
						(int)instruction->args.lbl.forced_offset);
				} else {
					fprintf(fout, ".EXPORT %s %i:\n",
						get_identifier_string(instruction->args.lbl.identifier),
						(int)instruction->args.lbl.flags);
				}
				break;
			
			case LIR_EVEN      : fprintf(fout, "\t.EVEN\n");  break;
			case LIR_SPLITPOINT: fprintf(fout, "\t.SPLIT\n"); break;
			
			case LIR_CHAR      : fprintf(fout, "\t.CHAR %li\n",   instruction->args.immed_val); break;
			case LIR_UCHAR     : fprintf(fout, "\t.UCHAR %li\n",  instruction->args.immed_val); break;
			case LIR_SHORT     : fprintf(fout, "\t.SHORT %li\n",  instruction->args.immed_val); break;
			case LIR_USHORT    : fprintf(fout, "\t.USHORT %li\n", instruction->args.immed_val); break;
			case LIR_LONG      : fprintf(fout, "\t.LONG %li\n",   instruction->args.immed_val); break;
			case LIR_ULONG     : fprintf(fout, "\t.ULONG %li\n",  instruction->args.immed_val); break;
			case LIR_FLINK     : fprintf(fout, "\t.LINK %s\n",   get_identifier_string(instruction->args.target)); break;
			default:
				fprintf(fout, "INVALID INSTRUCTION\n");
				break;
		}
	}
	else
	{
		fprintf(fout, "\t%s", instructions[instruction->type].mnemonic);
		
		switch(instruction->type)
		{
			// Single immediate value
			case LIR_LDIB:
			case LIR_LDIW:
			case LIR_LDIL:
			case LIR_CCALL:
			case LIR_LINK:
				fprintf(fout, " %li", instruction->args.immed_val);
				break;
			
			// Single register
			case LIR_MVA:
			case LIR_LDR:
			case LIR_STR:
			case LIR_INCR:
			case LIR_DECR:
				fprintf(fout, " %i", instruction->args.reg);
				break;
			
			// Double register
			case LIR_LDR2:
			case LIR_MOV:
				fprintf(fout, " %i %i", instruction->args.regpair.reg1, instruction->args.regpair.reg2);
				break;
			
			// Single label
			case LIR_CALL:
			case LIR_JMP:
			case LIR_BRA:
			case LIR_LDLBL:
				fprintf(fout, " %s", get_identifier_string(instruction->args.target));
				break;
			
			// No args
			default:
				break;
		}
		
		fprintf(fout, "\n");
	}
}
//}}}

