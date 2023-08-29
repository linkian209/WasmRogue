/* dll/bigmap.c */
int mkmap_big(void) SEG(7);
/* dll/debug.c */
void debug(void) SEG(7);
/* dll/dll.c */
const void **dll_load(const void *f);
void no_op(void) SEG(7);
int tool_holysymbol(void) SEG(7);
void spell_shield(void) SEG(7);
void spell_confusion(void) SEG(7);
void spell_gain_strength(void) SEG(7);
void spell_heal(void) SEG(7);
void spell_adrenaline(void) SEG(7);
void spell_adrenaline_low(void) SEG(7);
void spell_adrenaline_expire(void) SEG(7);
void spell_adrenaline_high_effect(void) SEG(7);
void spell_adrenaline_low_effect(void) SEG(7);
void read_tutorial_sign(unsigned short x, unsigned short y) SEG(7);
void auto_follow_connection(unsigned short x, unsigned short y) SEG(7);
void force_follow_connection(unsigned short x, unsigned short y) SEG(7);
void dll_fill_room(room *r) SEG(7);
/* dll/drawstring.c */
void clear_string(int x, int y, int width, int height) SEG(7);
void setTabStops(int num, ...) SEG(7);
void draw_string(const char *string, draw_string_info *start_state, short x, short y, short width, short height, short wrap) SEG(7);
/* dll/help.c */
void help(void) SEG(7);
