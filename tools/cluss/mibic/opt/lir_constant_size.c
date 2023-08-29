#include <limits.h>
#include "lir.h"

/*
 * Constant size reduction:
 *   Reduce Load Immediate Long (LDIL) instructions with LDIB, LDIW, LDIZ and
 * LDIO as appropriate.
 */

void lir_opt_constant_size(void)
{
	int ii;
	
	for(ii=0; ii<instr_num; ii++)
	{
		if(lir_data[ii].type == LIR_LDIL)
		{
			if(lir_data[ii].args.immed_val == 0)
				lir_data[ii].type = LIR_LDIZ;
			else if(lir_data[ii].args.immed_val == 1)
				lir_data[ii].type = LIR_LDIO;
			else if(lir_data[ii].args.immed_val <= SCHAR_MAX && lir_data[ii].args.immed_val >= SCHAR_MIN)
				lir_data[ii].type = LIR_LDIB;
			else if(lir_data[ii].args.immed_val <= SHRT_MAX && lir_data[ii].args.immed_val >= SHRT_MIN)
				lir_data[ii].type = LIR_LDIW;
		}
	}
}
