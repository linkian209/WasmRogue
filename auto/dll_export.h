/* Generated file - do not edit */
typedef struct export_functions
{
void (*no_op)(void); // Fill slot 0 (null)
/* dll/bigmap.c */
int (*mkmap_big)(void);
/* dll/debug.c */
void (*debug)(void);
/* dll/dll.c */
int (*tool_holysymbol)(void);
void (*spell_shield)(void);
void (*spell_confusion)(void);
void (*spell_gain_strength)(void);
void (*spell_heal)(void);
void (*spell_adrenaline)(void);
void (*read_tutorial_sign)(unsigned short x, unsigned short y);
void (*auto_follow_connection)(unsigned short x, unsigned short y);
void (*force_follow_connection)(unsigned short x, unsigned short y);
void (*dll_fill_room)(room *r);
/* dll/drawstring.c */
void (*clear_string)(int x, int y, int width, int height);
void (*setTabStops)(int num, ...);
void (*draw_string)(const char *string, draw_string_info *start_state, short x, short y, short width, short height, short wrap);
/* dll/help.c */
void (*help)(void);
void *terminator;
} export_functions;
