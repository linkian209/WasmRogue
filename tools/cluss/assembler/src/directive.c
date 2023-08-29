#include <string.h>
#include "cluss.h"

//{{{
int evaluate_directive(const char *directive, FILE *input, code_object *obj)
{
	short S;
	long L, L2;
	
#define DIRECTIVE_CASE(str) if( !strcasecmp(directive, str) )
	DIRECTIVE_CASE(".char") {
		write_byte(obj, get_numeric_argument(input));
	} else DIRECTIVE_CASE(".short") {
		write_alignment(obj, short_alignment, 0, 0);
		S = htots(get_numeric_argument(input));
		write_data(obj, (char*)&S, sizeof S);
	} else DIRECTIVE_CASE(".long") {
		write_alignment(obj, long_alignment, 0, 0);
		L = htotl(get_numeric_argument(input));
		write_data(obj, (char*)&L, sizeof L);
	} else DIRECTIVE_CASE(".even") {
		write_alignment(obj, 2, 0, 0);
	} else DIRECTIVE_CASE(".align") {
		write_alignment(obj, get_numeric_argument(input), 0, 0);
	} else DIRECTIVE_CASE(".align_off") {
		L = get_numeric_argument(input);
		write_alignment(obj, L, 0, get_numeric_argument(input));
	} else DIRECTIVE_CASE(".export") {
		L = read_label(obj, input);
		write_label(obj, L, get_numeric_argument(input));
		eat_argument(input);
	} else DIRECTIVE_CASE(".extern") {
		L = read_label(obj, input);
		L2 = get_numeric_argument(input);
		write_extern(obj, L, L2, get_numeric_argument(input));
		eat_argument(input);
	} else DIRECTIVE_CASE(".link") {
		write_reference(obj, read_label(obj, input), 0);
	} else DIRECTIVE_CASE(".split") {
		write_splitpoint(obj);
	} else {
		error("Unrecognized directive: %s", directive);
		return 0;
	}
	return 1;
}
//}}}

