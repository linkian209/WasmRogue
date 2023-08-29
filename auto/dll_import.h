/* Generated file - do not edit */
typedef struct
{
/* src/actions.c */
/* src/ai.c */
/* src/calls.c */
long (*call_generic)(int index, int num_args, ...);
/* src/construct.c */
/* src/crogue.c */
void (*timepass)(unsigned short amt);
/* src/draw.c */
void (*full_redraw)(void);
void (*draw_tile)(unsigned short x, unsigned short y);
/* src/facing.c */
/* src/files.c */
/* src/huffman.c */
/* src/interpret.c */
/* src/interpret_aux.c */
/* src/items.c */
int (*give_item)(const item *itm, signed short silent);
unsigned char *(*itemname)(const item *i);
void (*identify_type)(unsigned short t);
void (*place_item)(const item *i, unsigned short x, unsigned short y);
short (*top_item)(unsigned short x, unsigned short y);
item (*randitem)(filelink type);
/* src/light.c */
void (*illuminate)(signed short x, signed short y, signed short radiussquared);
/* src/magic.c */
/* src/messagefield.c */
void (*message)(const char *format, ...);
/* src/mkmap.c */
int (*make_door)(int x, int y);
/* src/monst.c */
signed short (*monstbytile)(unsigned short x, unsigned short y);
const char *(*monstname)(signed short n);
void (*addmonster)(unsigned short x, unsigned short y, filelink type);
void (*monst_takedamage)(signed short monstid, signed short damage, signed short is_melee);
void (*monst_heal)(unsigned short monstid, unsigned short amt);
int (*monst_is_peaceful)(int monstid);
void (*scare_monster)(unsigned short monstid);
void (*scare_monster_force)(int monstid);
void (*confuse_monster)(unsigned short monstid);
/* src/options.c */
int (*get_option)(int option);
/* src/pet.c */
/* src/player.c */
void (*apply_stat_mod_desc)(signed short *target, const stat_mod_desc *s, signed char plus);
void (*update_player)(void);
void (*follow_connection)(void);
void (*goto_level)(filelink target_level_link, const spec_descriptor_ext_level *connection);
void (*place_player_randomly)(void);
void (*plr_mod_stat)(signed short which, signed short amt);
short (*plr_restore_stat)(short which, short amt);
/* src/rand.c */
unsigned char (*xrandom)(unsigned short range);
signed short (*nrandom)(signed short max, signed short min);
unsigned long (*lrand)(void);
/* src/rle.c */
/* src/score.c */
/* src/skill.c */
/* src/spell.c */
/* src/throw.c */
/* src/tilefield.c */
void (*UI_TF_DrawEffect)(signed short x, signed short y, unsigned short tnum);
void (*UI_TF_ClearEffects)(void);
/* src/tiles.c */
/* src/timer.c */
void (*add_timer)(const timer_desc *desc, unsigned short duration);
/* src/use.c */
/* src/util.c */
const char *(*retprintf)(const char *format, ...);
coord (*trace_path)(int x, int y, direction dir, int distance);
monstdesc *(*find_monster_description)(int m);
const void *(*deref_file_ptr)(filelink p);
filelink (*deref_file_ptr_partial)(filelink p);
int (*isNull)(filelink p);
/* sys/stub/graph.c */
void (*Graph_ClrScr)(void);
void (*Graph_DrawChar)(short x, short y, char c);
void (*Graph_DrawStr)(short x, short y, const char *str);
void (*Graph_ClearRect)(int left, int top, int right, int bottom);
/* sys/stub/main.c */
/* sys/stub/menu.c */
void (*UI_Menu_Set_Persist)(unsigned short p);
int (*UI_Menu_Pick)(rect r, int numchoices, void (*getchoice)(int N, char *buf));
/* sys/stub/prompt.c */
int (*prompt)(const char *msg);
void (*prompt_dir)(const char *msg, direction *dir);
/* sys/stub/sysutil.c */
int (*read_char)(void);
void (*delay)(void);
void (*UI_Dialog_Default)(const char *content);
void (*UI_Dialog_Display)(rect r, const char *content);
short (*FontHeight)(void);
short (*FontWidth)(unsigned char c);
const char *(*get_keyname)(short key);
void *terminator;
} import_functions;
