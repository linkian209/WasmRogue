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
// prompt.c
/// @file
/// @brief Ask the user to answer a question

#include "crogue.h"

//{{{
/// @todo Handle different prompt keys
int prompt(const char *msg)
{
	message(gettext("%s [Y/N]"), msg);
	draw();
	switch(read_char())
	{
		case 'Y' : case 'y' :
		case '\n': case '\r':
			return 1;
		default:
			return 0;
	}
}
//}}}
//{{{
void prompt_dir(const char *msg, direction *dir)
{
	int input;

retry:
	message("%s", msg);
	draw();
	input = read_char();
	
	if(input=='\e' || input=='Z') // ESC
	{
		dir->x = 0;
		dir->y = 0;
	}
	else if( '0' < input && input <= '9' ) {
		dir->x = (input-'0'-1)%3-1;
		dir->y = -(input-'0'-1)/3+1;
		w->plr.facing_forced = w->plr.facing = facing(dir->x, dir->y);
	} else {
		message(gettext("Invalid direction,"));
		goto retry;
	}
}
//}}}

