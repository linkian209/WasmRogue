#include "crogue.h"
#include "export.h"

//{{{
int read_char(void)
{
	refresh();
	feed_entropy(get_entropy());
	return wgetch(stdscr);
}
//}}}
//{{{
int key_pending(void)
{
	return 0;
}
//}}}
//{{{
void delay(void)
{
	refresh();
#ifdef UNIX
	usleep(DELAY_AMOUNT_PC * 1000);
#else
	delay_output(DELAY_AMOUNT_PC);
#endif
}
//}}}

//{{{
#ifndef min
int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}
#endif
//}}}
//{{{
#ifndef max
int max(int a, int b)
{
	if(a<b)
		return b;
	else
		return a;
}
#endif
//}}}

//{{{
void *malloc_throw(size_t size)
{
	void *ret = malloc(size);
	if(ret == NULL)
		panic("Out of memory.");
	return ret;
}
//}}}
//{{{
void *calloc_throw(size_t N, size_t S)
{
	void *ret = calloc(N, S);
	if(ret == NULL)
		panic("Out of memory.");
	return ret;
}
//}}}
//{{{
void *realloc_throw(void *ptr, size_t size)
{
	void *ret = realloc(ptr, size);
	if(ret == NULL && size>0)
		panic("Out of memory.");
	return ret;
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
void UI_Dialog_Display(rect r, const char *content)
{
	coord pos = r.topleft;
	coord size = r.extent;
	clrscr();
	draw_string(content, NULL, pos.x+2, pos.y+2, size.x-4, size.y-4, 1);
	read_char();
}
//}}}

//{{{
short FontHeight(void)
{
	return 1;
}
//}}}
//{{{
short FontWidth(unsigned char c)
{
	return 1;
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
	clrscr();
	puts(str);
	fflush(stdout);
	getchar();
	cleanup();
	exit(1);
}
//}}}

//{{{
const char *get_keyname(short key)
{
	static char ret[16];
	// Workaround for apparent pdcurses bug: handle printing characters without
	// using keyname().
	if(key >= ' ' && key < 128) {
		sprintf(ret, "%c", key);
		return ret;
	}
	if(key==27) return "ESC";
	if(key=='\n') return "ENTER";
	
	return keyname(key);
}
//}}}
