#ifndef PLATFORM_H
#define PLATFORM_H

#include <tigcclib.h>

//HACK: This needs to be defined even on AMSes that don't support it
#define SetAlphaStatus _rom_call(void,(char),163)

extern LCD_BUFFER *saved_screen;

#define SCREEN_WIDTH   LCD_WIDTH
#define SCREEN_HEIGHT  LCD_HEIGHT

#define get_entropy() (*(volatile char*)0x600017)

void SetFont(short font);
void GraySprite8_BLIT(short x, short y, short h, const uchar *sprite1, const uchar *sprite2, uchar maskval, void *dest1, void* dest2);
void Graph_DrawLine(short x0, short y0, short x1, short y1);
void Graph_DrawStr_Reverse(short x, short y, const char *str);

extern const uchar Font_5x7[128*8];

#endif
