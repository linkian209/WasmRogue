#include <ctype.h>
#include "crogue.h"
#include "export.h"

static int selected=0;
static int offset=0;
static int persistence=0;

static void UI_Menu_Redraw( coord pos, coord size, int numchoices, void (*getchoice)(int N, char *buf), int scrollpos, int rows ) SEG(3);

//{{{
void UI_Menu_Set_Persist(ushort p)
{
	persistence = p;
	selected = 0;
	offset = 0;
}
//}}}

//{{{
int UI_Menu_Pick( rect r, int numchoices, void (*getchoice)(int N, char *buf) )
{
	int rows;
	int redraw;
	int prev_select, prev_offset;
//	int prev_tap_x=0, prev_tap_y=0;
	int dragging = 0;
	int targetted_position;
	long last_drag_time=0;
//	long last_tap_time=0;
	EventType event;
	
	if(!persistence) {
		selected = 0;
		offset=0;
	} else {
		if(selected >= numchoices)
			selected = numchoices - 1;;
		if(offset >= selected)
			offset = selected;
	}
	
	rows = r.extent.y/FontHeight();
	
	UI_Menu_Redraw(r.topleft, r.extent, numchoices, getchoice, offset, rows);
	
	Graph_ScrRectXor(r.topleft.x + 1, r.topleft.y +
		(selected-offset)*FontHeight()+1, r.extent.x-1, FontHeight());
	
	while(1)
	{
		prev_select = selected;
		prev_offset = offset;
		redraw = 0;
		
		retrieve_event_block(&event);
		
		switch(event.eType)
		{
			case keyDownEvent: //{{{
				switch(event.data.keyDown.chr)
				{
					case 'p':
					case '\n':
					case '\r':
					case ' ':
						return selected;
					case 'Z':
					case 'Q':
						return -1;
					case KEY_NORTH:
					case upArrowChr:
						if(selected==0) selected=numchoices-1;
						else            selected--;
						break;
					case KEY_SOUTH:
					case downArrowChr:
						selected++;
						if(selected>=numchoices) selected=0;
						break;
					case pageUpChr:
					case '<':
						if(offset!=0) redraw=1;
						selected -= rows;
						if(selected<0) selected=0;
						offset -= rows;
						if(offset<0) offset=0;
						break;
					case pageDownChr:
					case '>':
						selected += rows;
						if( selected>=numchoices )
							selected = numchoices-1;
						offset += rows;
						if( offset+rows>=numchoices )
							offset = numchoices-rows;
						if( offset<0 )
							offset = 0;
						redraw = 1;
						break;
				}
				break; //}}}
			case penDownEvent: //{{{
				// Inside the menu area
				if(event.screenY >= r.topleft.y &&
				   event.screenY <= r.topleft.y+r.extent.y &&
				   event.screenX >= r.topleft.x &&
				   event.screenX <= r.topleft.x+r.extent.x)
				{
					dragging=1;
					targetted_position = (event.screenY-r.topleft.y-1) /
					                     FontHeight();
					if(targetted_position >= rows) break;
					targetted_position += offset;
					if(targetted_position >= numchoices) break;
					selected = targetted_position;
					if(selected == prev_select) // Double-tap
						return selected;
				}
				else
				{
#if 0
					// Outside the menu area. A double-tap here means 'cancel'
					if(last_tap_time+SysTicksPerSecond()/2 > TimGetTicks() &&
					   distancesquare(prev_tap_x, prev_tap_y,
					                  event.screenX, event.screenY) < 40)
						return -1;
					
					last_tap_time = TimGetTicks();
					prev_tap_x = event.screenX;
					prev_tap_y = event.screenY;
#endif
					// Outside the menu area. A *single* tap here means cancel.
					return -1;
				}
				break; //}}}
			case penMoveEvent: //{{{
				if(last_drag_time+SysTicksPerSecond()/5 > TimGetTicks())
					break;
				if(!dragging) break;
				if(event.screenY < r.topleft.y)
				{
					if(offset==0 || selected==0) break;
					offset--; selected--;
					redraw = 1;
					last_drag_time = TimGetTicks();
				}
				else if(event.screenY > r.topleft.y+r.extent.y)
				{
					if(selected+1>=numchoices || offset+rows>=numchoices)
						break;
					offset++; selected++;
					redraw = 1;
					last_drag_time = TimGetTicks();
				}
				else
				{
					targetted_position = (event.screenY-r.topleft.y-1)/
					                     FontHeight();
					if(targetted_position >= rows) break;
					targetted_position += offset;
					if(targetted_position>=0 && targetted_position<numchoices)
						selected = targetted_position;
				}
				break; //}}}
			case penUpEvent: //{{{
				dragging = 0;
				break; //}}}
			default: //{{{
				default_event_handler(&event);
				break; //}}}
		}
		
		if(selected>=offset+rows) {
			offset += rows/2;
			if(offset+rows>=numchoices) offset = numchoices-rows;
			redraw=1;
		}
		if(selected<offset) {
			offset -= rows/2;
			if(offset<0) offset=0;
			redraw=1;
		}
		if( selected-offset < 0 || selected-offset >= rows ) {
			offset = selected - rows/2;
			if( offset<0 ) offset=0;
			if( offset+rows > numchoices ) offset = numchoices - rows;
		}
		
		if(redraw) {
			UI_Menu_Redraw(r.topleft, r.extent, numchoices, getchoice,
			               offset, rows);
		}
		
		if(prev_select != selected && !redraw)
		{
			// Un-highlight the current selection
			Graph_ScrRectXor(r.topleft.x + 1, r.topleft.y + (prev_select-
				prev_offset)*FontHeight()+1, r.extent.x-1, FontHeight());
		}
		if(prev_select != selected || redraw)
		{
			// Highlight the new selection
			Graph_ScrRectXor(r.topleft.x + 1, r.topleft.y +
				(selected-offset)*FontHeight()+1, r.extent.x-1, FontHeight());
		}
	}
	
	return 0;
}
//}}}
//{{{
static void UI_Menu_Redraw( coord pos, coord size, int numchoices, void (*getchoice)(int N, char *buf), int scrollpos, int rows )
{
	char buf[256];
	char *drawbuf;
	int i;
	
	// Clear a space
	Graph_ClearRect( pos.x, pos.y, pos.x+size.x, pos.y+size.y );
	// Draw a frame
	Graph_DrawRect( pos.x, pos.y, pos.x+size.x, pos.y+size.y );
	
	// Draw contents
	for(i=scrollpos; i<numchoices && i<rows+scrollpos; i++) {
		getchoice(i, buf);
		// Newline character used to indicate a non-selectable entry (hack)
		if(buf[0]=='\n') drawbuf = buf+1;
		else             drawbuf = buf;
		draw_string(drawbuf, NULL, pos.x+2, pos.y+FontHeight()*(i-scrollpos)+1,
		    size.x, FontHeight(), 0);
	}
}
//}}}

