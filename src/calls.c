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
// calls.c
/// @file
/// @brief Interface for calling bytecode-interpretted functions referenced
/// in the data file.
///
/// Each function here corresponds to a function type for interpretted code.

#include "crogue.h"

//{{{
void call_stepfunc(filelink f, ...)
{
	va_list params;
	
	if(isNull(f)) return;
	f = deref_file_ptr_partial(f);
	
	va_start(params, 2);
	
	if(f.type == PTR_INTERPCALL)
		run_program(w->const_file[f.segment], f.offset, 2, params);
	else
	{
	 	uint x = (uint) va_arg(params, unsigned short);
		uint y = (uint) va_arg(params, unsigned short);
		((void (*)(uint x, uint y))(w->dll_functions[f.offset]))(x, y);
	}

	va_end(params);
}
//}}}
//{{{
void call_genericfunc(filelink f)
{
	if(isNull(f)) return;
	f = deref_file_ptr_partial(f);
	
	if(f.type == PTR_INTERPCALL)
		run_program(w->const_file[f.segment], f.offset, 0, NULL);
	else
		((void (*)(void))(w->dll_functions[f.offset]))();
}
//}}}
//{{{
void call_throwhitfunc(filelink f, ...)
{
	va_list params;
	
	if(isNull(f)) return;
	f = deref_file_ptr_partial(f);

	va_start(params, 1);
	
	if(f.type == PTR_INTERPCALL)
		run_program(w->const_file[f.segment], f.offset, 1, params);
	else 
	{
		int monst = va_arg(params, int);
		((void (*)(int monst))(w->dll_functions[f.offset]))(monst);
	}

	va_end(params);
}
//}}}
//{{{
int call_usefunc(filelink f, ...)
{
	int retval;
	va_list params;
	
	if(isNull(f)) return 0;
	f = deref_file_ptr_partial(f);

	va_start(params, 1);
	
	if(f.type == PTR_INTERPCALL)
		return run_program(w->const_file[f.segment], f.offset, 1, params);
	else
	{
		int which_item = va_arg(params, int);
		retval = ((int (*)(int))(w->dll_functions[f.offset]))(which_item);
	}

	va_end(params);
	return retval;
}
//}}}
//{{{
int call_attackfunc(filelink f, ...)
{
	int retval;
	va_list params;
	
	if(isNull(f)) return 0;
	f = deref_file_ptr_partial(f);
	
	va_start(params, 3);
	
	if(f.type == PTR_INTERPCALL)
		return run_program(w->const_file[f.segment], f.offset, 3, params);
	else
	{
		uint monst = (uint) va_arg(params, unsigned short);
		uint damage = (uint)va_arg(params, unsigned short);
		sint target = (sint) va_arg(params, signed short);
		retval = ((int (*)(uint, uint, sint))
			(w->dll_functions[f.offset]))
			(monst, damage, target);
	}

	va_end(params);
	return retval;
}
//}}}

//{{{
long call_generic(int index, int num_args, ...)
{
	va_list args;
	long retval;
	const filelink *table = deref_file_ptr(w->desc.function_entries);
	filelink function = table[index];
	va_start(args, num_args);
	retval = run_program(w->const_file[function.segment], function.offset,
	                   num_args, args);
	va_end(args);
	return retval;
}
//}}}

