#include "crogue.h"

//{{{
void Graph_DrawTile(UI_Tilefield *tf, int x, int y, UI_TF_TileInfo tile)
{
	void *light;
	void *dark;
	const uchar *lighttile;
	const uchar *darktile;
	
	if(GrayCheckRunning())
	{
		light = GrayGetPlane(LIGHT_PLANE);
		dark = GrayGetPlane(DARK_PLANE);
		switch(tile.lighting)
		{
			case LIGHTING_LIT:
				lighttile = darktile = tf->graphics + tile.tile*tf->tileheight;
				break;
			case LIGHTING_DARK:
				lighttile = tf->graphics + (tf->tileheight * blacktile);
				darktile = tf->graphics + tile.tile*tf->tileheight;
				break;
			case LIGHTING_UNEXPLORED:
				lighttile = tf->graphics + (tf->tileheight * whitetile);
				darktile = tf->graphics + (tf->tileheight * blacktile);
				break;
			default:
				return;
		}
		GraySprite8_BLIT(tf->pos.x + x * tf->tilewidth,
			tf->pos.y + y * tf->tileheight,
			tf->tileheight,
			lighttile,
			darktile,
			0xFF >> tf->tileheight,
			light,
			dark);
	} else {
		switch(tile.lighting)
		{
			case LIGHTING_LIT:
				if(tile.tile == 3) tile.tile = 4;
			case LIGHTING_DARK:
				darktile = tf->graphics + tile.tile * tf->tileheight;
				break;
			case LIGHTING_UNEXPLORED:
				darktile = tf->graphics + 17 * tf->tileheight;
				break;
			default:
				return;
		}
		GraySprite8_BLIT(tf->pos.x + x * tf->tilewidth,
			tf->pos.y + y * tf->tileheight,
			tf->tileheight,
			darktile,
			darktile,
			0xFF >> tf->tileheight,
			LCD_MEM,
			LCD_MEM);
	}
}
//}}}
//{{{
void Graph_ClrScr(void)
{
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(LIGHT_PLANE);
		clrscr();
		GraySetAMSPlane(DARK_PLANE);
	}
	clrscr();
}
//}}}
//{{{
void Graph_ClearRect(int left, int top, int right, int bottom)
{
	SCR_RECT r = {{ left, top, right, bottom }};
	
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(LIGHT_PLANE);
		ScrRectFill(&r, &r, A_REVERSE);
		GraySetAMSPlane(DARK_PLANE);
	}
	ScrRectFill(&r, &r, A_REVERSE);
}
//}}}
//{{{
void Graph_DrawLine(short x0, short y0, short x1, short y1)
{
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(LIGHT_PLANE);
		DrawLine(x0, y0, x1, y1, A_NORMAL);
		GraySetAMSPlane(DARK_PLANE);
	}
	DrawLine(x0, y0, x1, y1, A_NORMAL);
}
//}}}
//{{{
void Graph_DrawChar (short x, short y, char c)
{
	const char *spr;
	
	if(CurFont == OPTION_FONT_MEDIUM)
	{
		spr = Font_5x7 + (c<<3);
		GraySprite8_BLIT(x, y, 7, spr+1, spr+1, 0xFF>>*spr,
			GrayGetPlane(LIGHT_PLANE), GrayGetPlane(DARK_PLANE));
		return;
	}
	
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(LIGHT_PLANE);
		DrawChar(x, y, c, A_NORMAL);
		GraySetAMSPlane(DARK_PLANE);
	}
	DrawChar(x, y, c, A_NORMAL);
}
//}}}
//{{{
void Graph_DrawStr(short x, short y, const char *str)
{
	if(CurFont == OPTION_FONT_MEDIUM)
	{
		while(*str != '\0') {
			Graph_DrawChar(x, y, *str);
			x += FontWidth(*str);
			str++;
		}
		return;
	}
	
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(LIGHT_PLANE);
		DrawStr(x, y, str, A_NORMAL);
		GraySetAMSPlane(DARK_PLANE);
	}
	DrawStr(x, y, str, A_NORMAL);
}
//}}}
//{{{
void Graph_DrawStr_Reverse(short x, short y, const char *str)
{
	if(CurFont == OPTION_FONT_MEDIUM)
	{
		while(*str != '\0') {
			Graph_DrawChar(x, y, *str);
			x += FontWidth(*str);
			str++;
		}
		return;
	}
	
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(LIGHT_PLANE);
		DrawStr(x, y, str, A_REVERSE);
		GraySetAMSPlane(DARK_PLANE);
	}
	DrawStr(x, y, str, A_REVERSE);
}
//}}}

