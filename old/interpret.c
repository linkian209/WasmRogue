/* {{{
 * CalcRogue, a roguelike game for PCs, calculators and PDAs
 * Copyright (C) 2003 Jim Babcock
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * }}} */
// interpret.c
/// @file
/// @brief Bytecode interpreter

#include "crogue.h"
#ifdef INTERPRETER_DEBUG
	#include <assert.h>
#endif

#ifdef INTERPRETER_DEBUG
	#ifndef INLINE
		#define INLINE
	#endif
#else
	#ifndef INLINE
		#define INLINE inline
	#endif
#endif

//{{{
#define OP_NOP     0x00
#define OP_HALT    0x01
#define OP_DISC    0x02
#define OP_DISCN   0x03
#define OP_DUP     0x04
#define OP_ALLOCA  0x05
//}}}
//{{{
#define OP_RET     0x10
#define OP_CALL    0x11
#define OP_STA     0x12
#define OP_MVA     0x13
#define OP_LINK    0x14
#define OP_CCALL   0x15
//}}}
//{{{
#define OP_LDR     0x20
#define OP_LDR2    0x21
#define OP_STR     0x22
#define OP_MOV     0x23
#define OP_LDIB    0x24
#define OP_LDIW    0x25
#define OP_LDIL    0x26
#define OP_LDIZ    0x27
#define OP_LDIO    0x28
//}}}
//{{{
#define OP_ADD     0x30
#define OP_SUB     0x31
#define OP_MUL     0x32
#define OP_DIV     0x33
#define OP_MOD     0x34
#define OP_ASL     0x35
#define OP_ASR     0x36
#define OP_AND     0x37
#define OP_OR      0x38
#define OP_XOR     0x39
#define OP_NEG     0x3A
#define OP_INCR    0x3B
#define OP_DECR    0x3C
//}}}
//{{{
#define OP_BOOL    0x40
#define OP_BOOL2   0x41
#define OP_NOT     0x42
#define OP_TEQ     0x43
#define OP_TLT     0x44
#define OP_TGT     0x45
//}}}
//{{{
#define OP_JMPB    0x50
#define OP_JMPW    0x51
#define OP_JMPL    0x52
#define OP_BRAB    0x53
#define OP_BRAW    0x54
#define OP_BRAL    0x55
//}}}
//{{{
#define OP_DEREFB  0x60
#define OP_DEREFW  0x61
#define OP_DEREFL  0x62
#define OP_POKEB   0x63
#define OP_POKEW   0x64
#define OP_POKEL   0x65
#define OP_LDLBL   0x66
//}}}

//{{{
typedef union instruction_args
{
	signed   char bytes[6];
	unsigned char ubytes[4];
	signed   short words[2];
	signed   long dword;
} instruction_args_t;
//}}}

static const char *interpreter_call_stack[32];
static int interpreter_call_stack_pos = 0;

#define pop_stack() (*(--stack_pos))
#define push_stack(n) (*(stack_pos++) = (n))
#define write_arg(v) (*(arg_pos++) = (v))
#define load_register(n) (register_pos[n])
#define save_register(n,v) (register_pos[n] = (v))
#define start_args() (arg_pos = register_pos + register_used + 1)

//{{{
static const char *interp_func_name(const char *pos)
{
	pos--;
	do {
		pos--;
	} while(*pos != '\0');
	pos++;
	return pos;
}
//}}}

//{{{
//
// *** This function MUST be reentrant when exiting via OP_CCALL! ***
//
long run_program(const unsigned char *program_data, int num_params, va_list params)
{
	int ii;
	long new_pc;
	long param1, param2;
	const unsigned char *execution_pos;
	instruction_args_t args;
	return_info_t ret;
	
	long *stack_pos;
	long *register_pos;
	long *arg_pos;
	long pc;
	short call_pos;
	short register_used;
	long active_stack[ACTIVE_STACK_DEPTH];
	long register_stack[REGISTER_STACK_DEPTH];
	short call_stack[CALL_STACK_DEPTH];
	
	pc = 0;
	register_used = 0;
	stack_pos = active_stack;
	register_pos = register_stack;
	call_pos = 0;
	
	start_args();
	
	for(ii=0; ii<num_params; ii++)
		write_arg(va_arg(params, long));
	va_end(params);
	
	new_pc = pc;
	
	while(1)
	{
		pc = new_pc;
		new_pc++;
		execution_pos = program_data + pc;
		
		args.bytes[0] = execution_pos[1];
		args.bytes[1] = execution_pos[2];
		args.bytes[2] = execution_pos[3];
		args.bytes[3] = execution_pos[4];
		
		switch(*execution_pos)
		{
//{{{
		case OP_NOP:
			break;
		case OP_HALT:
			return 0;
		case OP_DISC:
			(void)pop_stack();
			break;
		case OP_DISCN:
			new_pc++;
			for(ii=0; ii<args.ubytes[0]; ii++)
				(void)pop_stack();
			break;
		case OP_DUP:
			param1 = pop_stack();
			push_stack(param1);
			push_stack(param1);
			break;
		case OP_ALLOCA:
			param1 = pop_stack();
			push_stack( (long)(register_pos + register_used) );
			register_used += ((param1+3) & (~3)) >> 2;
				// use size/4 rounded up registers
			start_args();
			break;
//}}}
//{{{
		case OP_RET:
			interpreter_call_stack_pos--;
			if(call_pos == 0)
			{
				if(stack_pos > active_stack) {
					param1 = pop_stack();
					return param1;
				}
				else {
					return 0;
				}
			}
			
			// Unlink registers
			register_pos--;
			register_used = *register_pos;
			register_pos -= register_used;
			
			new_pc = call_stack[--call_pos];
			start_args();
			interpreter_call_stack[interpreter_call_stack_pos] = NULL;
			break;
		case OP_CALL:
			new_pc += 2;
			call_stack[call_pos++] = new_pc;
			new_pc = pc + args.words[0];
			break;
		case OP_STA:
			write_arg(pop_stack());
			break;
		case OP_MVA:
			new_pc++;
			write_arg(load_register(args.ubytes[0]));
			break;
		case OP_LINK:
			new_pc++;
			
			// Allocate registers
			register_pos[register_used] = register_used;
			register_pos += register_used + 1;
			register_used = args.ubytes[0];
			
			start_args();
			interpreter_call_stack[interpreter_call_stack_pos++] = interp_func_name(execution_pos);
			break;
		case OP_CCALL:
			new_pc += 2;
			// Call C interface function by index (see table in interpret_aux.c)
			ret = interpret_call(args.words[0],
			                    register_pos + register_used + 1);
			if(ret.returns)
				push_stack( ret.retval );
			start_args();
			break;
//}}}
//{{{
		case OP_LDR2:
			new_pc+=2;
			push_stack(load_register(args.ubytes[0]));
			push_stack(load_register(args.ubytes[1]));
			break;
			
		case OP_LDR:
			new_pc++;
			push_stack(load_register(args.ubytes[0]));
			break;
		case OP_STR:
			new_pc++;
			save_register(args.ubytes[0], pop_stack());
			break;
		case OP_MOV:
			new_pc += 2;
			save_register(args.ubytes[1], load_register(args.ubytes[0]));
			break;
		case OP_LDIB:
			new_pc++;
			push_stack((long)(args.bytes[0]));
			break;
		case OP_LDIW:
			new_pc += 2;
			push_stack((long)(args.words[0]));
			break;
		case OP_LDIL:
			new_pc += 4;
			push_stack( args.dword );
			break;
		case OP_LDIZ:
			push_stack(0);
			break;
		case OP_LDIO:
			push_stack(1);
			break;
//}}}
//{{{
		case OP_ADD:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 + param2);
			break;
		case OP_SUB:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 - param2);
			break;
		case OP_MUL:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 * param2);
			break;
		case OP_DIV:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 / param2);
			break;
		case OP_MOD:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 % param2);
			break;
		case OP_ASL:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 << param2);
			break;
		case OP_ASR:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 >> param2);
			break;
		case OP_AND:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 & param2);
			break;
		case OP_OR:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 | param2);
			break;
		case OP_XOR:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 ^ param2);
			break;
		case OP_NEG:
			param1 = -pop_stack();
			push_stack(param1);
			break;
		case OP_INCR:
			new_pc++;
			save_register(args.ubytes[0], load_register(args.ubytes[0]) + 1);
			break;
		case OP_DECR:
			new_pc++;
			save_register(args.ubytes[0], load_register(args.ubytes[0]) - 1);
			break;
//}}}
//{{{
		case OP_BOOL:
			param1 = !!pop_stack();
			push_stack(param1);
			break;
		case OP_BOOL2:
			param1 = pop_stack();
			param2 = pop_stack();
			push_stack(!!param2);
			push_stack(!!param1);
			break;
		case OP_NOT:
			param1 = pop_stack();
			push_stack(!param1);
			break;
		case OP_TEQ:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 == param2);
			break;
		case OP_TLT:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 < param2);
			break;
		case OP_TGT:
			param2 = pop_stack();
			param1 = pop_stack();
			push_stack(param1 > param2);
			break;
//}}}
//{{{
		case OP_JMPB:
			new_pc = pc + args.bytes[0];
			break;
		case OP_JMPW:
			new_pc = pc + args.words[0];
			break;
		case OP_JMPL:
			new_pc = pc + args.dword;
			break;
		case OP_BRAB:
			if(pop_stack())
				new_pc = pc + args.bytes[0];
			else
				new_pc++;
			break;
		case OP_BRAW:
			if(pop_stack()) {
				new_pc = pc + args.words[0];
			} else {
				new_pc+=2;
			}
			break;
		case OP_BRAL:
			if(pop_stack())
				new_pc = pc + args.dword;
			else
				new_pc+=4;
			break;
//}}}
//{{{
		case OP_DEREFB:
			param1 = pop_stack();
			#ifdef INTERPRETER_DEBUG
				assert(param1 > 1024);
			#endif
			push_stack( *((char*)param1) );
			break;
		case OP_DEREFW:
			param1 = pop_stack();
			#ifdef INTERPRETER_DEBUG
				assert(param1 > 1024);
			#endif
			push_stack( *((short*)param1) );
			break;
		case OP_DEREFL:
			param1 = pop_stack();
			#ifdef INTERPRETER_DEBUG
				assert(param1 > 1024);
			#endif
			push_stack( *((long*)param1) );
			break;
		case OP_POKEB:
			param1 = pop_stack();
			param2 = pop_stack();
			#ifdef INTERPRETER_DEBUG
				assert(param2 > 1024);
			#endif
			*((char*)param2) = param1;
			break;
		case OP_POKEW:
			param1 = pop_stack();
			param2 = pop_stack();
			#ifdef INTERPRETER_DEBUG
				assert(param2 > 1024);
			#endif
			*((short*)param2) = param1;
			break;
		case OP_POKEL:
			param1 = pop_stack();
			param2 = pop_stack();
			#ifdef INTERPRETER_DEBUG
				assert(param2 > 1024);
			#endif
			*((long*)param2) = param1;
			break;
		case OP_LDLBL:
			push_stack((long)(execution_pos + args.dword));
			new_pc += 4;
			break;
//}}}
//{{{
		default:
			break;
//}}}
		}
	}
}
//}}}

