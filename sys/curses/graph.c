#include "crogue.h"

//{{{
void Graph_DrawTile(UI_Tilefield *tf, int x, int y, UI_TF_TileInfo tile)
{
	uchar target_color;
	if(tile.lighting == LIGHTING_LIT)
		target_color = tile.color.lit;
	else
		target_color = tile.color.dark;
	attroff(COLOR_PAIR(DEFAULT_COLOR));
	if(target_color & COLOR_BOLD)
		attron(A_BOLD);
	if(use_color) attron(COLOR_PAIR((target_color&~COLOR_BOLD)+1));
	mvaddch(y+tf->pos.y, x+tf->pos.x, tiles[tile.tile]);
	if(target_color & COLOR_BOLD)
		attroff(A_BOLD);
	if(use_color) {
		attroff(COLOR_PAIR((target_color&~COLOR_BOLD)+1));
		attron(COLOR_PAIR(DEFAULT_COLOR));
	}
}
//}}}
//{{{
void Graph_ClrScr(void)
{
	clrscr();
}
//}}}
//{{{
void Graph_DrawChar (short x, short y, char c)
{
	mvaddch(y, x, c);
}
//}}}
//{{{
void Graph_DrawStr(short x, short y, const char *str)
{
	mvaddstr(y, x, (char*)str);
}
//}}}
//{{{
void Graph_ClearRect(int left, int top, int right, int bottom)
{
	int i, j;
	for(i=left; i<=right; i++)
	for(j=top; j<=bottom; j++) {
		mvaddch(j, i, ' ');
	}
}
//}}}


