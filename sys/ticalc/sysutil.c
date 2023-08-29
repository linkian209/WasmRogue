#include "crogue.h"
#include "export.h"

// low power mode, wake up CPU only on AI 1 (grayscale), 2 (keypress), 3 (AMS
// clock), 5 (AMS timer base, needed for APD) and 6 (ON, always wakes up the
// CPU)
#define GrayIdle() pokeIO(0x600005,0b10111)
//{{{
int read_char(void)
{
	// NOTE: The contents of this function have a large effect on battery
	// usage.
	ushort key;
	void *kbq = kbd_queue();
	
	feed_entropy( get_entropy() );
	OSTimerRestart(APD_TIMER);
	
	if(GrayCheckRunning())
	{
		while(OSdequeue (&key, kbq)) {
			GrayIdle();
			if(OSTimerExpired(APD_TIMER)) {
				off();
				OSTimerRestart(APD_TIMER);
			}
		}
	} else {
		while(OSdequeue (&key, kbq)) {
			idle();
			if(OSTimerExpired(APD_TIMER)) {
				off();
				OSTimerRestart(APD_TIMER);
			}
		}
	}
	return key;
}
//}}}
//{{{
int key_pending(void)
{
	short scratch;
	return OSqinquire(&scratch, kbd_queue());
}
//}}}
//{{{
void delay(void)
{
	OSRegisterTimer(USER_TIMER, DELAY_AMOUNT);
	if(GrayCheckRunning())
	{
		do {
			GrayIdle();
		} while(!OSTimerExpired(USER_TIMER));
	} else {
		do {
			GrayIdle();
		} while(!OSTimerExpired(USER_TIMER));
	}
	OSFreeTimer(USER_TIMER);
}
//}}}

//{{{
void UI_Dialog_Default(const char *content)
{
	UI_Dialog_Display(default_dialog_rect, content);
	UI_MF_clear();
	full_redraw();
}
//}}}
//{{{
void UI_Dialog_Display(rect win, const char *content)
{
	coord pos = win.topleft;
	coord size = win.extent;
	int fontHeight;
	SCR_RECT r= {{pos.x, pos.y, pos.x+size.x, pos.y+size.y}};
	
	SetCurClip(&r);
	
	// Clear a space
	Graph_ClearRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
	
	// Draw a frame
	Graph_DrawLine(pos.x, pos.y, pos.x+size.x, pos.y);
	Graph_DrawLine(pos.x, pos.y, pos.x, pos.y+size.y);
	Graph_DrawLine(pos.x+size.x, pos.y, pos.x+size.x, pos.y+size.y);
	Graph_DrawLine(pos.x, pos.y+size.y, pos.x+size.x, pos.y+size.y);
	
	SetFont(get_option(OPTION_FONTSIZE));
	fontHeight = FontHeight();
	draw_string(content, NULL, pos.x+2, pos.y+2, size.x-4, (size.y-4), 1);
	read_char();
}
//}}}

static short CurFont = OPTION_FONT_SMALL;
//{{{
void SetFont(short font)
{
	CurFont = font;
	
	switch(CurFont)
	{
		case OPTION_FONT_SMALL:
			FontSetSys(F_4x6);
			break;
		case OPTION_FONT_MEDIUM:
			break;
		case OPTION_FONT_LARGE:
			FontSetSys(F_6x8);
			break;
	}
}
//}}}
//{{{
short FontHeight(void)
{
	switch(CurFont)
	{
		case OPTION_FONT_SMALL:
		default:
			return 6;
		case OPTION_FONT_MEDIUM:
			return 7;
		case OPTION_FONT_LARGE:
			return 8;
	}
}
//}}}
//{{{
short FontWidth(unsigned char c)
{
	if(CurFont == OPTION_FONT_MEDIUM) {
		return Font_5x7[c<<3];
	} else {
		return FontCharWidth(c);
	}
}
//}}}

//{{{
void panic(const char *fmt, ...)
{
	const char *str;
	va_list varargs;
	va_start(varargs, fmt);
	str = vretprintf(fmt, varargs);
	va_end(varargs);
	
	sys_cleanup();
	printf(str);
	read_char();
	cleanup();
	exit(1);
}
//}}}

//{{{
static const char *keys[] =
	{
		"??",    "\x08"
		"STO>",  "SIN",  
		"COS",   "TAN",  
		"LN",    "CLEAR",  
		"ESC",   "APPS",  
		"MODE",  "ON",  
		"F1",    "F2",  
		"F3",    "F4",  
		"F5",    "F6",  
		"F7",    "F8",  
		"(-)",   "HOME",  
		"CAT"
	};
//}}}
//{{{
const char *get_keyname(short key)
{
	static char ret[16];
	char *pos = ret;
	int used_meta = 0;
	
	if(key & KEY_DIAMOND) {
		key &= ~KEY_DIAMOND;
		*(pos++) = 0x7F;
		used_meta = 1;
	}
	if(key & KEY_SHIFT) {
		key &= ~KEY_SHIFT;
		*(pos++) = 0x1B;
		used_meta = 1;
	}
	if(key & 0x1000)
	{
		strcpy(pos, "2nd+");
		pos+= 4;
		key &= ~0x1000;
		used_meta = 1;
	}
	
	// Handle special keys with a table
	if(key > 0x101 && key < 0x117) {
		int index = key-0x101;
		strcpy(pos, keys[index]);
//		strcpy(pos, keys[key-0x101]);
		return ret;
	}
	
	if(key < 256) // ASCII range. Assume that everything here has
	              // a good matching char in the font.
	{
		// If this is a lowecase letter, on a TI-89, show alpha meta char
		if(islower(key) && TI89) {
			if(key!='x' && key!='y' && key!='z' && key!='t') {
				*(pos++) = 0x80;
				*(pos++) = '-';
			}
		}
		else if(isupper(key) && !used_meta) {
			*(pos++) = 0x1B; // Shift
		}
		if(key==' ') {
			strcpy(pos, "Space");
		} else if(key==0xAD) {
			strcpy(pos, "(-)");
		} else if(key==0x0D) {
			strcpy(pos, "ENTER");
		} else {
			*(pos++) = toupper(key);
			*pos= '\0';
		}
	}
	else if(key == KEY_LEFT)
		strcpy(pos, "left");
	else if(key == KEY_RIGHT)
		strcpy(pos, "right");
	else if(key == KEY_UP)
		strcpy(pos, "up");
	else if(key == KEY_DOWN)
		strcpy(pos, "down");
	else if(key == KEY_UPRIGHT)
		strcpy(pos, "up-right");
	else if(key == 339)
		strcpy(pos, "up-left");
	else if(key == KEY_DOWNLEFT)
		strcpy(pos, "down-left");
	else if(key == 348)
		strcpy(pos, "down-right");
	else
		strcpy(pos, "??");
	
	return ret;
}
//}}}

//{{{
void GraySprite8_BLIT(short x,short y,short h,
                      const unsigned char* sprite1,
                      const unsigned char* sprite2,
                      unsigned char maskval,
                      void* dest1,
                      void* dest2)
{
	register long           offset = (y<<5)-(y<<1)+((x>>3)&0x1e);
	register long           addr1  = (long)dest1+offset;
	register long           addr2  = (long)dest2+offset;
	register unsigned short cnt      = 24-(x&15);
	register long           maskval2 = ~((long)(~(maskval)&0xff)<<cnt);
		for (;h;h--,addr1+=30,addr2+=30) {
		*(long*)addr1&=maskval2;
		*(long*)addr1|=(long)(*sprite1++)<<cnt;
		*(long*)addr2&=maskval2;
		*(long*)addr2|=(long)(*sprite2++)<<cnt;
	}
}
//}}}

