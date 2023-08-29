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
// drawstring.c
/// @file
/// @brief Draws a line-wrapped string with tab support.
///
/// Rules for setting tab stops:\n
///  setTabStops takes a variable number of arguments, the first of which is the
///  number of tabs to use. All arguments must be of type int, and the first tab
///  stop is always at 0 (that way, a tab which crosses onto a new line starts
///  at the beginning of the next line.)

#include "crogue.h"
#include "dll.h"

//{{{
static int StringWidth(const char *str)
{
	uint len=0;
	
	while(*str != '\0') {
		len += FontWidth(*str);
		str++;
	}
	
	return len;
}
//}}}

//{{{
/// Clear the space allocated to a string
void clear_string(int x, int y, int width, int height)
{
	Graph_ClearRect(x, y, x+width-1, y+height*FontHeight()-1);
}
//}}}

static int numTabStops = 1;
static uchar tabStops[16]={0};

//{{{
/// Set tab stops
void setTabStops(int num, ...)
{
	va_list varargs;
	int i;
	numTabStops = num;
	
	va_start(varargs, num);
	for(i=0; i<num; i++)
		tabStops[i] = va_arg(varargs, int);
	va_end(varargs);
}
//}}}
//{{{
/// Find the next tab stop after a position
static int findTab(int pos)
{
	int i;
	for(i=0; i<numTabStops; i++)
	{
		if(tabStops[i] > pos)
			return tabStops[i];
	}
	return SCREEN_WIDTH * 2;
}
//}}}

/*
 * height=0 means no wrapping allowed; instead, clip the right edge (don't
 * pause, either)
 * Tab stops are given as distance from x, not from the left edge of the screen
 * Rows are in textual lines; width, x, and y are in pixels.
 */
//{{{
/// @brief Draw a line-wrapped, tabstop-including, length-limited string
///
/// Draws a string. Any instances of the tab character are handled as expected
/// using the tab stops set with #setTabStops. If @a wrap is set, text will
/// wrap at the end of a line. If @a start_state is non-null, it can be used
/// to keep track of a write cursor. If the text fills more rows than will
/// fit in @a height (the number of rows depends on the font), a "-More-"
/// prompt will be displayed until the player presses a key.
void draw_string(const char *string, draw_string_info *start_state, short x, short y, short width, short height, short wrap)
{
	int i, ii;
	int curX=0;
	int tempX;
	int curRow=0;
	int maxWidth;
	int rows = height/FontHeight();
	
	if(start_state)
	{
		curX = start_state->curX;
		curRow = start_state->curRow;
	}
	
	tempX = curX;
	
	i=0;
	
	while( string[i] != '\0' )
	{
		maxWidth = width;
		if( wrap && curRow+1 == rows )
			maxWidth -= StringWidth(gettext(" -More-"));
		
		if( string[i] == '\t' )
		{
			if(findTab(tempX) > maxWidth)
				goto startNewLine;
			else
				tempX = findTab(tempX);
		}
		else
		{
			tempX += FontWidth(string[i]);
		}
		
		// If past the end of the line
		if(tempX >= maxWidth || string[i] == '\n') {
startNewLine:
			if(!wrap)
				break;
			
			if(string[i] != '\n' && string[i] != '\t')
			{
				// Back up until (a) it fits and (b) it isn't in the middle of a word
				while(i >= 0 && string[i] != ' ' && tempX>0)
					tempX -= FontWidth(string[i--]);
				if(tempX<=0) // Overshot; this line needs to be broken on a non-word-break
				{
					while(tempX<=maxWidth)
						tempX += FontWidth(string[++i]);
					tempX -= FontWidth(string[--i]);
				}
			}
			
			// Print it out
			for(ii=0; ii<i; ii++) {
				if(string[ii]!='\t')
					Graph_DrawChar(x+curX, y + curRow*FontHeight(), string[ii]);
				if(string[ii]=='\t')
					curX = findTab(curX);
				else
					curX += FontWidth(string[ii]);
			}
			
			// If out of lines, print the -More- prompt
			if( curRow+1 == rows ) {
				Graph_DrawStr(curX+x, curRow*FontHeight() + y, gettext(" -More-"));
				read_char();
				clear_string(x, y, width, rows);
				
				curRow = -1;
				curX = tempX = 0;
			}
			
			string += i;
			string++;
			
			i=0;
			
			curRow++;
			curX = tempX = 0;
		} else {
			i++;
		}
	}
	
	// Print the remainder
	for( i=0; string[i]!='\0'; i++ ) {
		if(string[i] == '\t')
		{
			curX = findTab(curX);
			continue;
		}
		Graph_DrawChar( x+curX, y + curRow*FontHeight(), string[i]);
		curX += FontWidth( string[i] );
	}
	
	if(start_state)
	{
		start_state->curX = curX;
		start_state->curRow = curRow;
	}
}
//}}}
