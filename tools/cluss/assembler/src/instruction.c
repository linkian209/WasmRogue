#include "cluss.h"
#include <string.h>

//{{{
int evaluate_instruction(const char *instruction,FILE *input,code_object *obj)
{
#define INSTR_CASE(str) if( !strcasecmp(instruction, str) )
	// MISC OPERATIONS
	INSTR_CASE("halt") {
		write_byte(obj, 0x00);
	} else INSTR_CASE("nop") {
		write_byte(obj, 0x01);
	} else INSTR_CASE("disc") {
		write_byte(obj, 0x02);
	} else INSTR_CASE("dup") {
		write_byte(obj, 0x03);
	} else INSTR_CASE("alloca") {
		write_byte(obj, 0x04);
	// FUNCTION CALLING OPERATIONS
	} else INSTR_CASE("ret") {
		write_byte(obj, 0x05);
	} else INSTR_CASE("call") {
		write_byte(obj, 0x06);
		write_abs_3byte(obj, read_label(obj, input), 0);
	} else INSTR_CASE("sta") {
		write_byte(obj, 0x07);
	} else INSTR_CASE("mva") {
		write_byte(obj, 0x08);
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("link") {
		write_byte(obj, 0x09);
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("ccall") {
		write_byte(obj, 0x0A);
		write_short(obj, get_numeric_argument(input));
	// LOAD AND STORE OPERATIONS
	} else INSTR_CASE("ldr") {
		write_byte(obj, 0x0B);
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("ldr2") {
		write_byte(obj, 0x0C);
		write_byte(obj, get_numeric_argument(input));
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("str") {
		write_byte(obj, 0x0D);
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("mov") {
		write_byte(obj, 0x0E);
		write_byte(obj, get_numeric_argument(input));
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("ldib") {
		write_byte(obj, 0x0F);
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("ldiw") {
		write_byte(obj, 0x10);
		write_short(obj, get_numeric_argument(input));
	} else INSTR_CASE("ldil") {
		write_byte(obj, 0x11);
		write_long(obj, get_numeric_argument(input));
	} else INSTR_CASE("ldiz") {
		write_byte(obj, 0x12);
	} else INSTR_CASE("ldio") {
		write_byte(obj, 0x13);
	// ARITHMETIC OPERATIONS
	} else INSTR_CASE("add") {
		write_byte(obj, 0x14);
	} else INSTR_CASE("sub") {
		write_byte(obj, 0x15);
	} else INSTR_CASE("mul") {
		write_byte(obj, 0x16);
	} else INSTR_CASE("div") {
		write_byte(obj, 0x17);
	} else INSTR_CASE("mod") {
		write_byte(obj, 0x18);
	} else INSTR_CASE("asl") {
		write_byte(obj, 0x19);
	} else INSTR_CASE("asr") {
		write_byte(obj, 0x1A);
	} else INSTR_CASE("and") {
		write_byte(obj, 0x1B);
	} else INSTR_CASE("or") {
		write_byte(obj, 0x1C);
	} else INSTR_CASE("xor") {
		write_byte(obj, 0x1D);
	} else INSTR_CASE("neg") {
		write_byte(obj, 0x1E);
	} else INSTR_CASE("incr") {
		write_byte(obj, 0x1F);
		write_byte(obj, get_numeric_argument(input));
	} else INSTR_CASE("decr") {
		write_byte(obj, 0x20);
		write_byte(obj, get_numeric_argument(input));
	// LOGICAL OPERATIONS
	} else INSTR_CASE("bool") {
		write_byte(obj, 0x21);
	} else INSTR_CASE("bool2") {
		write_byte(obj, 0x22);
	} else INSTR_CASE("not") {
		write_byte(obj, 0x23);
	} else INSTR_CASE("teq") {
		write_byte(obj, 0x24);
	} else INSTR_CASE("tlt") {
		write_byte(obj, 0x25);
	} else INSTR_CASE("tgt") {
		write_byte(obj, 0x26);
	// CONTROL FLOW OPERATIONS
	} else INSTR_CASE("jmp") {
		write_byte(obj, 0x27);
		write_abs_short(obj, read_label(obj, input), 0);
	} else INSTR_CASE("bra") {
		write_byte(obj, 0x28);
		write_abs_short(obj, read_label(obj, input), 0);
	// MEMORY OPERATIONS
	} else INSTR_CASE("derefb") {
		write_byte(obj, 0x29);
	} else INSTR_CASE("derefw") {
		write_byte(obj, 0x2A);
	} else INSTR_CASE("derefl") {
		write_byte(obj, 0x2B);
	} else INSTR_CASE("pokeb") {
		write_byte(obj, 0x2C);
	} else INSTR_CASE("pokew") {
		write_byte(obj, 0x2D);
	} else INSTR_CASE("pokel") {
		write_byte(obj, 0x2E);
	} else INSTR_CASE("ldlbl") {
		write_byte(obj, 0x2F);
		write_abs_3byte(obj, read_label(obj, input), 0);
	} else {
		error("Invalid instruction: %s", instruction);
		return 0;
	}
	return 1;
}
//}}}

