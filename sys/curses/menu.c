#include "crogue.h"
#include "export.h"

static sint UI_Menu_Hotkey(char key, int numchoices, void (*getchoice)(int N, char *buf));

/*
UI_Menu_Pick parameters:
pos: top-left corner of the window
size: distance from top-left corner to bottom-left corner
numchoices: number of entries on the menu
getchoice: pointer to function taking int N and returning Nth entry on the list

Return codes:
-2 Error
-1 User aborted (no selection)
[0, numchoices): user selection #
*/

static int offset=0;
static int persistence=0;

//{{{
void UI_Menu_Set_Persist(ushort p)
{
	persistence = p;
#ifdef IS_CALCULATOR
	selected = 0;
#endif
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
static void UI_Menu_Redraw( coord pos, coord size, int numchoices, void (*getchoice)(int N, char *buf), int scrollpos )
{
	int i;
	char outbuf[256];
	char buf[256];
	
	// Draw border
	mvaddch(pos.y,          pos.x,          '+');
	mvaddch(pos.y,          pos.x+size.x-1, '+');
	mvaddch(pos.y+size.y-1, pos.x+size.x-1, '+');
	mvaddch(pos.y+size.y-1, pos.x,          '+');
	for(i=pos.x+1; i<pos.x+size.x-1; i++) {
		mvaddch(pos.y, i, '-');
		mvaddch(pos.y+size.y-1, i, '-');
	}
	for(i=pos.y+1; i<pos.y+size.y-1; i++) {
		mvaddch(i, pos.x, '|');
		mvaddch(i, pos.x+size.x-1, '|');
	}
	
	// Clear interior
	for(i=0; i<size.x-2; i++)
		outbuf[i] = ' ';
	outbuf[i] = '\0';
	for(i=pos.y+1; i<pos.y+size.y-1; i++)
		mvaddstr(i, pos.x+1, outbuf);
	
	// Draw contents
	for(i=0; i<size.y-2; i++) {
		if(i+scrollpos < numchoices) {
			getchoice(i+scrollpos, buf);
			if(buf[0]=='\n')
				sprintf(outbuf, " %s", buf+1);
			else
				sprintf(outbuf, " %c - %s", i+'a', buf);
			draw_string(outbuf, NULL, pos.x+1, i+pos.y+1, SCREEN_WIDTH,
				FontHeight(), 0);
		}
	}
}
//}}}
//{{{
int UI_Menu_Pick( rect r, int numchoices, void (*getchoice)(int N, char *buf) )
{
	static int offset=0;
	int in;
	coord pos = r.topleft;
	coord size = r.extent;
	
	if(!persistence) {
		offset= 0;
	} else {
		if(offset>=numchoices)
			offset=0;
	}
	
	do
	{
		UI_Menu_Redraw(pos, size, numchoices, getchoice, offset);
		
		in = read_char();
		
		if(isdigit(in))
			return UI_Menu_Hotkey(in, numchoices, getchoice);
		else if(in==KEY_ESC || in=='Z' || in=='Q')
			return -1;
		else if(in==' ' || in=='\n' || in=='>') {
			offset += r.extent.y - 2;;
			if(offset>=numchoices)
				return -1;
		}
		else if(in=='<') {
			offset -= r.extent.y - 2;
			if(offset<0) offset=0;
		}
		else if(islower(in)) {
			if(offset+in-'a' < 0 || offset+in-'a' >= numchoices)
				continue;
			return offset+in-'a';
		}
	}
	while(1);
}
//}}}

