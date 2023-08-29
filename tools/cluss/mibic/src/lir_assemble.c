#include <stdio.h>
#include <stdlib.h>
#include "lir.h"
#include "compile.h"
#include "util.h"

static int lir_instr_size(lir_instr_t *instr);
static void lir_write_instr(unsigned char *location, lir_instr_t *instr);
static int find_label(id_handle_t lbl);
static int label_flags(id_handle_t lbl);
static void write_immediate(char *location, int length, unsigned long value);

//{{{
void lir_assemble(void)
{
	int ii;
	int data_size;
	char *output;
	FILE *fout;
	
	lir_data[0].location = 0;
	
	// Place instructions
	for(ii=1; ii<instr_num; ii++)
	{
		lir_data[ii].location = lir_data[ii-1].location + lir_instr_size(&lir_data[ii-1]);
	}
	
	data_size = lir_data[instr_num-1].location + lir_instr_size(&lir_data[instr_num-1]);
	output = malloc(data_size);
	
	for(ii=0; ii<instr_num; ii++)
	{
		lir_write_instr((void*)(output + lir_data[ii].location), &lir_data[ii]);
	}
	
	fout = fopen(output_filename, "wb");
	if(!fout)
	{
		error_opening_file(output_filename);
		return;
	}
	
	fwrite(output, data_size, 1, fout);
	free(output);
	fclose(fout);
}
//}}}

//{{{
static int lir_instr_size(lir_instr_t *instr)
{
	if(instr->type < num_instructions)
		return instructions[instr->type].size;
	else
	{
		switch(instr->type)
		{
			case LIR_EVEN  : return (instr->location % 2);
			case LIR_CHAR  : return 1;
			case LIR_UCHAR : return 1;
			case LIR_SHORT : return 2;
			case LIR_USHORT: return 2;
			case LIR_LONG  : return 4;
			case LIR_ULONG : return 4;
			case LIR_FLINK : return 4;
			default:
				return 0;
		}
	}
}
//}}}
//{{{
static void lir_write_instr(unsigned char *location, lir_instr_t *instr)
{
	if(instr->type < num_instructions)
	{
		*location = instructions[instr->type].opcode;
		location++;
	}
	
	switch(instr->type)
	{
		// Special
		case LIR_EVEN:
			if((long)location % 2)
				write_immediate((void*)location, 1, 0);
			break;
		
		// Value only
		case LIR_CHAR  : write_immediate((void*)location, 1, instr->args.immed_val); break;
		case LIR_UCHAR : write_immediate((void*)location, 1, instr->args.immed_val); break;
		case LIR_SHORT : write_immediate((void*)location, 2, instr->args.immed_val); break;
		case LIR_USHORT: write_immediate((void*)location, 2, instr->args.immed_val); break;
		case LIR_LONG  : write_immediate((void*)location, 4, instr->args.immed_val); break;
		case LIR_ULONG : write_immediate((void*)location, 4, instr->args.immed_val); break;
		
		// Links
		case LIR_FLINK:
			*(location++) = label_flags(instr->args.target);
			*(location++) = 0;
			write_immediate((void*)location, 2, find_label(instr->args.target));
			break;
		
		// Single immediate value
		case LIR_LDIB:
		case LIR_LINK:
			write_immediate((void*)location, 1, instr->args.immed_val);
			break;
		case LIR_LDIW:
		case LIR_CCALL:
			write_immediate((void*)location, 2, instr->args.immed_val);
			break;
		case LIR_LDIL:
			write_immediate((void*)location, 4, instr->args.immed_val);
			break;
		
		// Single register
		case LIR_MVA:
		case LIR_LDR:
		case LIR_STR:
		case LIR_INCR:
		case LIR_DECR:
			write_immediate((void*)location, 1, instr->args.reg);
			break;
		
		// Double register
		case LIR_LDR2:
		case LIR_MOV:
			write_immediate((void*)location, 1, instr->args.regpair.reg1);
			location++;
			write_immediate((void*)location, 1, instr->args.regpair.reg2);
			break;
		
		// Single label
		case LIR_BRA:
		case LIR_JMP:
		case LIR_CALL:
			write_immediate((void*)location, 2, find_label(instr->args.target) - instr->location);
			break;
		case LIR_LDLBL:
			write_immediate((void*)location, 4, find_label(instr->args.target) - instr->location);
			break;
		
		// No args
		default:
			break;
	}
}
//}}}
//{{{
static int find_label(id_handle_t lbl)
{
	int ii;
	for(ii=0; ii<instr_num; ii++)
	{
		if(lir_data[ii].type != LIR_LABEL)
			continue;
		if(!idcmp(lir_data[ii].args.lbl.identifier, lbl))
			continue;
		if(lir_data[ii].args.lbl.force_offset)
			return lir_data[ii].args.lbl.forced_offset;
		return lir_data[ii].location;
	}
	
	fprintf(stderr, "Error: Undefined reference to '%s'\n", get_identifier_string(lbl));
	return 0;
}
//}}}
//{{{
static int label_flags(id_handle_t lbl)
{
	int ii;
	for(ii=0; ii<instr_num; ii++)
	{
		if(lir_data[ii].type != LIR_LABEL)
			continue;
		if(!idcmp(lir_data[ii].args.lbl.identifier, lbl))
			continue;
		return lir_data[ii].args.lbl.flags;
	}
	
	return 0;
}
//}}}

//{{{
static void write_immediate(char *location, int length, unsigned long value)
{
	int ii;
	
	if(reverse_endian)
	{
		location += length;
		
		for(ii=0; ii<length; ii++)
		{
			*(--location) = (unsigned char)value;
			value >>= 8;
		}
	}
	else
	{
		for(ii=0; ii<length; ii++)
		{
			*(location++) = (unsigned char)value;
			value >>= 8;
		}
	}
}
//}}}

