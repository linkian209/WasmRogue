#include "crogue.h"
#include "export.h"

static sint UI_Menu_Hotkey(char key, int numchoices, void (*getchoice)(int N, char *buf));

/*
UI_Menu_Pick parameters:
r: menu rectangle
numchoices: number of entries on the menu
getchoice: pointer to function taking int N and returning Nth entry on the list

Return codes:
-2 Error
-1 User aborted (no selection)
[0, numchoices): user selection #
*/

static int selected=0;
static int offset=0;
static int persistence=0;

//{{{
void Graph_ScrRectFill(const SCR_RECT *rect, const SCR_RECT *clip, short Attr)
{
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(LIGHT_PLANE);
		ScrRectFill(rect, clip, Attr);
		GraySetAMSPlane(DARK_PLANE);
	}
	ScrRectFill(rect, clip, Attr);
}
//}}}

//{{{
void UI_Menu_Set_Persist(ushort p)
{
	persistence = p;
	selected = 0;
	offset = 0;
}
//}}}
//{{{
static sint UI_Menu_Hotkey(char key, int numchoices, void (*getchoice)(int N, char *buf))
{
	char buf[256];
	int i;
	
	for(i=0; i<numchoices; i++)
	{
		getchoice(i, buf);
		if(key == buf[0])
			return i;
	}
	return -1;
}
//}}}

//{{{
static void UI_Menu_Redraw( coord pos, coord size, int numchoices, void (*getchoice)(int N, char *buf), int scrollpos, int rows )
{
	char buf[256];
	char *drawbuf;
	int i;
	SCR_RECT rect = {{pos.x, pos.y, pos.x+size.x, pos.y+size.y}};
	
	SetCurClip(&rect);
	
	// Clear a space
	Graph_ClearRect( pos.x, pos.y, pos.x+size.x, pos.y+size.y );
	
	// Draw a frame
	Graph_DrawLine(pos.x, pos.y, pos.x+size.x, pos.y);
	Graph_DrawLine(pos.x, pos.y, pos.x, pos.y+size.y);
	Graph_DrawLine(pos.x+size.x, pos.y, pos.x+size.x, pos.y+size.y);
	Graph_DrawLine(pos.x, pos.y+size.y, pos.x+size.x, pos.y+size.y);
	
	// Draw contents
	for(i=scrollpos; i<numchoices && i<rows+scrollpos; i++) {
		getchoice(i, buf);
		// Newline character used to indicate a non-selectable entry (hack)
		if(buf[0]=='\n') drawbuf = buf+1;
		else             drawbuf = buf;
		draw_string(drawbuf, NULL, pos.x+2, pos.y+6*(i-scrollpos)+2,
		    size.x, FontHeight(), 0);
	}
}
//}}}
//{{{
int UI_Menu_Pick( rect r, int numchoices, void (*getchoice)(int N, char *buf) )
{
	int rows;
	int in;
	int redraw;
	SCR_RECT selectbox;
	
	if(!persistence) {
		selected = 0;
		offset=0;
	} else {
		if(selected >= numchoices)
			selected = numchoices - 1;;
		if(offset >= selected)
			offset = selected;
	}
	
	rows = r.extent.y/6;
	
	SetFont(OPTION_FONT_SMALL);
	UI_Menu_Redraw(r.topleft, r.extent, numchoices, getchoice, offset, rows);
	
	selectbox = (SCR_RECT){{r.topleft.x+1,
					   r.topleft.y+(selected-offset)*6+1,
					   r.topleft.x+r.extent.x-1,
					   r.topleft.y+(selected-offset)*6+6}};
	Graph_ScrRectFill(&selectbox, &selectbox, A_XOR);
	
	while(1) {
		redraw = 0;
		
		in = read_char();
		
		selectbox = (SCR_RECT){{r.topleft.x+1,
								r.topleft.y+(selected-offset)*6+1,
								r.topleft.x+r.extent.x-1,
								r.topleft.y+(selected-offset)*6+6}};
		Graph_ScrRectFill(&selectbox, &selectbox, A_XOR);
		
		if(isdigit(in)) { // Hotkey
			return UI_Menu_Hotkey(in, numchoices, getchoice);
		}
		else if(in==KEY_UP)
		{
			if(selected==0)
				selected=numchoices-1;
			else
				selected--;
		} else if(in==KEY_DOWN)
		{
			selected++;
			if(selected>=numchoices)
				selected=0;
		} else if(in==KEY_UP+4096)	// 2nd+Up
		{
			selected -= rows;
			if( selected<0 )
				selected = 0;
			offset -= rows;
			if( offset<0 )
				offset = 0;
			redraw = 1;
		} else if(in==KEY_DOWN+4096)	// 2nd+Down
		{
			selected += rows;
			if( selected>=numchoices )
				selected = numchoices-1;
			offset += rows;
			if( offset+rows>=numchoices )
				offset = numchoices-rows;
			if( offset<0 )
				offset = 0;
			redraw = 1;
		} else if(in==KEY_CONFIRM || in==KEY_SCROLL_RIGHT) {
			return selected;
		} else if(in==KEY_ESC) {
			return -1;
		}
		
		if(selected>=offset+rows) {
			offset += rows/2;
			if(offset+rows>=numchoices) offset = numchoices-rows;
			redraw=1;
		}
		if(selected<=offset) {
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
			UI_Menu_Redraw(r.topleft, r.extent, numchoices, getchoice, offset, rows);
		}
		
		selectbox = (SCR_RECT){{r.topleft.x+1,
								r.topleft.y+(selected-offset)*6+1,
								r.topleft.x+r.extent.x-1,
								r.topleft.y+(selected-offset)*6+6}};
		Graph_ScrRectFill(&selectbox, &selectbox, A_XOR);
	}
	
	return 0;
}
//}}}

