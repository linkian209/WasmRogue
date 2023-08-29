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
	int ret;
	if(get_option(OPTION_PROMPT_DLG) == OPTION_YES)
	{
		w->interrupt = 1;
		if(!monochrome_screen) WinPushDrawState();
		ret = FrmCustomAlert(DialogYesNo, msg, NULL, NULL);
		if(!monochrome_screen) WinPopDrawState();
		return (ret == 0);
	}
	else
	{
		message(gettext("%s [Y/N]"), msg);
		draw();
		switch(read_char())
		{
			case 'Y':
			case 'y':
			case KEY_ACKNOWLEDGE:
				return 1;
			default:
				return 0;
		}
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
	
	switch(input)
	{
		case KEY_RUN_NORTHWEST: case KEY_NORTHWEST:
			*dir = DIRECTION(-1, -1); break;
		case KEY_RUN_NORTH: case KEY_NORTH:
			*dir = DIRECTION( 0, -1); break;
		case KEY_RUN_NORTHEAST: case KEY_NORTHEAST:
			*dir = DIRECTION( 1, -1); break;
		case KEY_RUN_EAST: case KEY_EAST:
			*dir = DIRECTION( 1, 0); break;
		case KEY_RUN_SOUTHEAST: case KEY_SOUTHEAST:
			*dir = DIRECTION( 1, 1); break;
		case KEY_RUN_SOUTH: case KEY_SOUTH:
			*dir = DIRECTION( 0, 1); break;
		case KEY_RUN_SOUTHWEST: case KEY_SOUTHWEST:
			*dir = DIRECTION(-1, 1); break;
		case KEY_RUN_WEST: case KEY_WEST:
			*dir = DIRECTION(-1, 0); break;
		case KEY_ESC:
			*dir = DIRECTION(0, 0); break;
		default:
			message(gettext("Invalid direction,"));
			goto retry;
	}
}
//}}}

