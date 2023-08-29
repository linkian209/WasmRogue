#ifndef PLATFORM_H
#define PLATFORM_H

#ifndef SEG
#define SEG(n) __attribute__((section("sec_" #n)))
#endif

#ifndef __size_t__
#define __size_t__
typedef unsigned long size_t; // This *really* doesn't belong here
#endif

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 160

#define TEMPFILENAME "rgtemp"

#define gettext(a) a
	// FIXME: This has to go as soon as sgt is used on this port

#define get_entropy TimGetSeconds
#define strcpy StrCopy
#define memset(a,b,c) MemSet(a,c,b)
void *memcpy(void *dst, const void *src, size_t sz);
#define strlen StrLen
#define strcat StrCat

void *malloc_throw(size_t N);
void *calloc(size_t N, size_t S);
void *realloc(void *data, size_t S);
#define realloc_throw realloc
//#define malloc_throw MemPtrNew
#define free MemPtrFree
#define calloc_throw calloc

void Graph_DrawLine(short x0, short y0, short x1, short y1) SEG(5);
void Graph_ScrRectXor(int left, int top, int width, int height) SEG(5);
void Graph_DrawRect(int left, int top, int right, int bottom) SEG(5);
extern int high_density_font;
int getColor(int red, int green, int blue);
void init_colors(void);
extern int monochrome_screen;
extern int game_running;
extern int game_repeat;
void handle_events(void) SEG(5);
int default_event_handler(EventType *ev) SEG(5);
int retrieve_event(EventType *event) SEG(5);
void retrieve_event_block(EventType *event) SEG(5);

#define PEN_TAP      0
#define PEN_DRAG     1
#define PEN_RETURN   2
#define PEN_SQUIGGLE 3
#define PEN_WALK     0
#define PEN_RUN      1
#define PEN_FIRE     2
#define PEN_SCROLL   3
int event_pen_down(int x, int y) SEG(5);
void event_pen_move(int x, int y) SEG(5);
int event_pen_up(int x, int y) SEG(5);

#define NUM_DIRECTIONAL_ACTIONS 4
typedef int (*directional_action)(int dx, int dy);
extern directional_action pen_actions[NUM_DIRECTIONAL_ACTIONS];

void configure_pen(void) SEG(2);
void configure_buttons(void) SEG(2);
int direction_walk  (int dx, int dy) SEG(2);
int direction_run   (int dx, int dy) SEG(2);
int direction_fire  (int dx, int dy) SEG(2);
int direction_scroll(int dx, int dy) SEG(2);
int pen_tap_center(void) SEG(2);
int hard_button(int button) SEG(2);
int should_trap_button(int button) SEG(2);

#define BUTTONBAR_X 0
#define BUTTONBAR_Y 151
#define BUTTON_WIDTH 9
#define BUTTON_HEIGHT 8
void buttonbar_draw(void) SEG(5);
int buttonbar_which_button(int x, int y) SEG(5);
void buttonbar_xor(int buttonnum) SEG(5);
int button_press(int buttonnum);

extern int color_lit, color_unlit, color_unexplored;
extern int color_red,     color_lred,
           color_green,   color_lgreen,
           color_yellow,  color_lyellow,
           color_blue,    color_lblue,
           color_magenta, color_lmagenta,
           color_cyan,    color_lcyan,
           color_white,   color_lwhite;


int isqrt(int n);

#define OPTIONS_SUBMENUS 2
void pick_submenu(int choice);
void options_submenu(int n, char *buf);
#define OPTION_PEN_PREFIX 0x0100

#define TAP_CENTER_DEFAULT 1

#endif

