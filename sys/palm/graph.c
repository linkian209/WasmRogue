#include "crogue.h"

static void Graph_DrawTile_Monochrome(UI_Tilefield *tf, int x, int y, UI_TF_TileInfo tile) SEG(1);

//{{{
void Graph_DrawTile(UI_Tilefield *tf, int x, int y, UI_TF_TileInfo tile)
{
	int tile_map;
	uchar target_color;
	RectangleType r;
	
	if(monochrome_screen || get_option(OPTION_COLOR)!=OPTION_YES) {
		Graph_DrawTile_Monochrome(tf, x, y, tile);
		return;
	}
	
	WinPushDrawState();
	r.topLeft.x = tf->pos.x + x*tf->tilewidth;
	r.topLeft.y = tf->pos.y + y*tf->tileheight;
	r.extent.x = tf->tilewidth;
	r.extent.y = tf->tileheight;
	
	FntSetFont(TileFont);
	
	if(tile.lighting == LIGHTING_LIT) target_color = tile.color.lit;
	else                              target_color = tile.color.dark;
	
	switch(target_color)
	{
		case RED:      WinSetTextColor(color_red);      break;
		case GREEN:    WinSetTextColor(color_green);    break;
		case YELLOW:   WinSetTextColor(color_yellow);   break;
		case BLUE:     WinSetTextColor(color_blue);     break;
		case MAGENTA:  WinSetTextColor(color_magenta);  break;
		case CYAN:     WinSetTextColor(color_cyan);     break;
		case LRED:     WinSetTextColor(color_lred);     break;
		case LGREEN:   WinSetTextColor(color_lgreen);   break;
		case LYELLOW:  WinSetTextColor(color_lyellow);  break;
		case LBLUE:    WinSetTextColor(color_lblue);    break;
		case LMAGENTA: WinSetTextColor(color_lmagenta); break;
		case LCYAN:    WinSetTextColor(color_lcyan);    break;
		case WHITE:    WinSetTextColor(color_white);    break;
		case LWHITE:   WinSetTextColor(color_lwhite);    break;
	}
	
	tile_map = tile.tile;
	if(tile_map < 32) // Ctl char range. In Palm font, this is mapped to 128+N
		tile_map += 128;
	
	switch(tile.lighting)
	{
		case LIGHTING_LIT:
			WinSetBackColor(color_lit);
			Graph_DrawChar(tf->pos.x + x*tf->tilewidth,
						   tf->pos.y + y*tf->tileheight,
						   tile_map);
			break;
		case LIGHTING_DARK:
			WinSetBackColor(color_unlit);
			Graph_DrawChar(tf->pos.x + x*tf->tilewidth,
						   tf->pos.y + y*tf->tileheight,
						   tile_map);
			break;
		case LIGHTING_UNEXPLORED:
			WinSetForeColor(color_unexplored);
			WinDrawRectangle(&r, 0);
			break;
	}
	FntSetFont(TextFont);
	WinPopDrawState();
}
//}}}
//{{{
static void Graph_DrawTile_Monochrome(UI_Tilefield *tf, int x, int y, UI_TF_TileInfo tile)
{
	int tile_map;
	RectangleType r;
	
	r.topLeft.x = tf->pos.x + x*tf->tilewidth;
	r.topLeft.y = tf->pos.y + y*tf->tileheight;
	r.extent.x = tf->tilewidth;
	r.extent.y = tf->tileheight;
	
	FntSetFont(TileFont);
	
	switch(tile.lighting)
	{
		case LIGHTING_LIT:
			if(tile.tile == 3) tile.tile = 4;
		case LIGHTING_DARK:
			tile_map = tile.tile;
			if(tile_map < 32) // Ctl char range, mapped to 128+N
				tile_map += 128;
			
			Graph_DrawChar(tf->pos.x + x*tf->tilewidth,
						   tf->pos.y + y*tf->tileheight,
						   tile_map);
			break;
		case LIGHTING_UNEXPLORED:
			Graph_DrawChar(tf->pos.x + x*tf->tilewidth,
						   tf->pos.y + y*tf->tileheight,
						   128+17);
			break;
	}
	FntSetFont(TextFont);
}
//}}}

//{{{
void Graph_ClrScr(void)
{
	WinEraseWindow();
}
//}}}
//{{{
void Graph_ClearRect(int left, int top, int right, int bottom)
{
	RectangleType r;
	r.topLeft.x = left;
	r.topLeft.y = top;
	r.extent.x = right-left+1;
	r.extent.y = bottom-top+1;
	WinEraseRectangle(&r, 0);
}
//}}}
//{{{
void Graph_DrawRect(int left, int top, int right, int bottom)
{
	Graph_DrawLine(left, top, right, top);
	Graph_DrawLine(right, top, right, bottom);
	Graph_DrawLine(right, bottom, left, bottom);
	Graph_DrawLine(left, bottom, left, top);
}
//}}}
//{{{
void Graph_DrawLine(short x0, short y0, short x1, short y1)
{
	WinDrawLine(x0, y0, x1, y1);
	WinDrawLine(x0, y0, x1, y1);
}
//}}}
//{{{
void Graph_DrawChar(short x, short y, char c)
{
	WinGlueDrawChar((unsigned char)c, x, y);
}
//}}}
//{{{
void Graph_DrawStr(short x, short y, const char *str)
{
	WinDrawChars(str, strlen(str), x, y);
}
//}}}
//{{{
void Graph_ScrRectXor(int left, int top, int width, int height)
{
	RectangleType r;
	r.topLeft.x = left;
	r.topLeft.y = top;
	r.extent.x = width;
	r.extent.y = height;
	WinInvertRectangle(&r, 0);
}
//}}}

//{{{
int getColor(int red, int green, int blue)
{
	RGBColorType rgb;
	rgb.r = red;
	rgb.g = green;
	rgb.b = blue;
	return WinRGBToIndex(&rgb);
}
//}}}

