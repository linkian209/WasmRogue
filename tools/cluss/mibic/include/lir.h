#ifndef LIR_H
#define LIR_H

#include "namespace.h"

//{{{
#define LIR_HALT    0x0000
#define LIR_NOP     0x0001
#define LIR_DISC    0x0002
#define LIR_DUP     0x0003
#define LIR_ALLOCA  0x0004

#define LIR_RET     0x0005
#define LIR_CALL    0x0006
#define LIR_STA     0x0007
#define LIR_MVA     0x0008
#define LIR_LINK    0x0009
#define LIR_CCALL   0x000A

#define LIR_LDR     0x000B
#define LIR_LDR2    0x000C
#define LIR_STR     0x000D
#define LIR_MOV     0x000E
#define LIR_LDIB    0x000F
#define LIR_LDIW    0x0010
#define LIR_LDIL    0x0011
#define LIR_LDIZ    0x0012
#define LIR_LDIO    0x0013

#define LIR_ADD     0x0014
#define LIR_SUB     0x0015
#define LIR_MUL     0x0016
#define LIR_DIV     0x0017
#define LIR_MOD     0x0018
#define LIR_ASL     0x0019
#define LIR_ASR     0x001A
#define LIR_AND     0x001B
#define LIR_OR      0x001C
#define LIR_XOR     0x001D
#define LIR_NEG     0x001E
#define LIR_INCR    0x001F
#define LIR_DECR    0x0020

#define LIR_BOOL    0x0021
#define LIR_BOOL2   0x0022
#define LIR_NOT     0x0023
#define LIR_TEQ     0x0024
#define LIR_TLT     0x0025
#define LIR_TGT     0x0026

#define LIR_JMP     0x0027
#define LIR_BRA     0x0028

#define LIR_DEREFB  0x0029
#define LIR_DEREFW  0x002A
#define LIR_DEREFL  0x002B
#define LIR_POKEB   0x002C
#define LIR_POKEW   0x002D
#define LIR_POKEL   0x002E
#define LIR_LDLBL   0x002F

#define LIR_LABEL   0x0100
#define LIR_FLINK   0x0101
#define LIR_EVEN    0x0102
#define LIR_CHAR    0x0103
#define LIR_UCHAR   0x0104
#define LIR_SHORT   0x0105
#define LIR_USHORT  0x0106
#define LIR_LONG    0x0107
#define LIR_ULONG   0x0108

#define LIR_SPLITPOINT 0x0109
//}}}

//{{{
typedef struct argument_info
{
	int size;
	int is_label;
} argument_info;
//}}}
//{{{
typedef struct instruction_info
{
	int opcode;
	const char *mnemonic;
	int size;
	int num_params;
	argument_info *params;
	id_handle_t identifier;
} instruction_info_t;
//}}}

extern const int num_instructions;
extern instruction_info_t instructions[];

//{{{
typedef struct reg_pair
{
	short reg1, reg2;
} reg_pair_t;
//}}}
//{{{
typedef struct label_info
{
	id_handle_t identifier;
	short flags;
	short forced_offset;
	char force_offset;
} label_info_t;
//}}}
//{{{
typedef struct lir_instr
{
	short type;
	long location;
	union {
		long immed_val;
		label_info_t lbl;
		id_handle_t target;
		short reg;
		reg_pair_t regpair;
	} args;
} lir_instr_t;
//}}}

void lir_write_instruction(lir_instr_t instruction);
void lir_write_inst(int op);
void lir_write_inst_reg(int op, int reg);
void lir_write_inst_2_reg(int op, int reg1, int reg2);
void lir_write_inst_immediate(int op, long val);
void lir_write_inst_label(int op, id_handle_t label);
void lir_write_label(id_handle_t identifier);
void lir_write_label_flags(id_handle_t identifier, short flags, short forced_offset, char force_offset);

void lir_print(void);
void lir_assemble(void);

extern lir_instr_t *lir_data;
extern int instr_num, instr_alloc;

void lir_opt_dead_tails(void);
void lir_opt_constant_size(void);

#endif

