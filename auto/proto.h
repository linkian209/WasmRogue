/* src/actions.c */
int actions_menu(void) SEG(0);
/* src/ai.c */
void monstmove(signed short monst) SEG(0);
void webspinner_build(unsigned short monst, unsigned short tile_web, unsigned short tile_floor) SEG(0);
void webspinner_cower(unsigned short monst, unsigned short tile_web, unsigned short tile_wall) SEG(0);
void monst_chat(unsigned short monst) SEG(0);
/* src/calls.c */
void call_stepfunc(filelink f, ...) SEG(0);
void call_genericfunc(filelink f) SEG(0);
void call_throwhitfunc(filelink f, ...) SEG(0);
int call_usefunc(filelink f, ...) SEG(0);
int call_attackfunc(filelink f, ...) SEG(0);
long call_generic(int index, int num_args, ...) SEG(0);
/* src/construct.c */
coord construct_coord(unsigned char x, unsigned char y) SEG(0);
rect construct_rect(unsigned char x, unsigned char y, unsigned char w, unsigned char h) SEG(0);
direction construct_direction(signed char x, signed char y) SEG(0);
range construct_range(unsigned char max, unsigned char min) SEG(0);
/* src/crogue.c */
void initialize(void) SEG(0);
void resize_map_store(int size_x, int size_y) SEG(0);
void eventloop(void) SEG(0);
void timepass(unsigned short amt) SEG(1);
void die(const char *cause_of_death) SEG(0);
void end_game(const char *cause_of_death) SEG(0);
void quit(void) SEG(0);
void cleanup(void) SEG(0);
/* src/draw.c */
void UI_Status_Place(int y, int h) SEG(1);
void full_redraw(void) SEG(1);
void draw(void) SEG(1);
void draw_all_tiles(void) SEG(1);
void draw_tile(unsigned short x, unsigned short y) SEG(1);
void add_dead_zone(int left, int top, int right, int bottom) SEG(4);
void clear_dead_space(void) SEG(4);
/* src/facing.c */
signed short facing(signed short x, signed short y) SEG(1);
signed short facing_towards(signed short x, signed short y) SEG(1);
signed short facing_opposite(signed short x, signed short y) SEG(1);
signed short player_facing(void) SEG(1);
unsigned short delta_facing(signed short facing_one, signed short facing_two) SEG(1);
/* src/files.c */
void link_data_file(void) SEG(1);
void save_game(void) SEG(1);
void save_checkpoint(void) SEG(3);
void save_to_file(const char *filename) SEG(1);
int restore_game(void) SEG(1);
const char *levelfile_name(int levelnum) SEG(4);
void save_level(void) SEG(1);
int load_level(int source, coord pos) SEG(1);
void cleanup_save(void) SEG(1);
void compress_tiles(void) SEG(1);
/* src/huffman.c */
void fhuffmaninit_write(void) SEG(1);
void fhuffmanputc(unsigned char c, FILE *f) SEG(1);
void fhuffmanflush(FILE *f) SEG(1);
void fhuffmaninit_read(void) SEG(1);
char fhuffmangetc(FILE *f) SEG(1);
/* src/interpret.c */
long run_program(const unsigned char *program_data, long start_pc, int num_params, va_list params) SEG(1);
/* src/interpret_aux.c */
return_info_t interpret_call(int which_func, long *params) SEG(1);
/* src/items.c */
int filter_none(const item *i) SEG(1);
int filter_cursed(const item *i) SEG(1);
int filter_worn(const item *i) SEG(1);
int filter_wearable(const item *i) SEG(1);
int filter_unidentified(const item *i) SEG(1);
int filter_usable(const item *i) SEG(1);
int filter_enchantable(const item *i) SEG(2);
int filter_plural(const item *i) SEG(2);
int filter_rusty(const item *i) SEG(2);
int pick_item(inventoryfilter f) SEG(2);
void pick_multiple(inventoryfilter f, void (*function)(int which)) SEG(2);
int filter_matches(inventoryfilter f) SEG(2);
void init_inventory(void) SEG(2);
item split_item(int slot) SEG(2);
void merge_item(int slot, item it) SEG(2);
int give_item(const item *itm, signed short silent) SEG(2);
void give_item_slip(const item *itm) SEG(2);
item *player_equipment(int slot) SEG(2);
unsigned short count_inventory(void) SEG(2);
int iterate_item_property(const item_properties *pr, unsigned short type, short (*func)(const item_property *pr)) SEG(2);
const item_property_desc *get_item_property(const item *itm, unsigned short type) SEG(2);
void apply_item_property(const item *itm, unsigned short stat, signed short *n) SEG(2);
void apply_all_item_properties(const item *itm, int trigger) SEG(2);
const char *shortitemname(const item *i) SEG(2);
unsigned char *n_itemname(unsigned long which) SEG(2);
unsigned char *itemname(const item *i) SEG(2);
void award_item_points(void) SEG(2);
void rust_inventory(unsigned short which) SEG(2);
unsigned short fix_rust(void) SEG(2);
void give_gold(unsigned long amt) SEG(2);
unsigned long player_gold(void) SEG(2);
void debit_gold(unsigned long amt) SEG(2);
unsigned long item_cost(const item *i) SEG(2);
unsigned long sale_price(const item *i) SEG(2);
void list_discoveries(void) SEG(2);
void init_discoveries(void) SEG(2);
void identify_type(unsigned short t) SEG(2);
unsigned long type_is_identified(unsigned long t) SEG(2);
void compress_items(void) SEG(2);
void place_item(const item *i, unsigned short x, unsigned short y) SEG(2);
unsigned char draw_item(unsigned char x, unsigned char y) SEG(2);
short count_items(unsigned short x, unsigned short y) SEG(2);
short top_item(unsigned short x, unsigned short y) SEG(2);
colorinfo color_item(unsigned char x, unsigned char y) SEG(2);
void init_items(void) SEG(2);
void cleanup_items(void) SEG(2);
item randitem(filelink type) SEG(2);
void drop_item(void) SEG(2);
void drop_multiple(void) SEG(2);
void wear_item(void) SEG(2);
void wear_multiple(void) SEG(2);
void takeoff_item(void) SEG(2);
void takeoff_multiple(void) SEG(2);
void item_step(void) SEG(2);
void pickup(unsigned short pickup_prompt) SEG(2);
void hotkey_item(void) SEG(2);
/* src/light.c */
void calc_light(void) SEG(2);
unsigned short tracevision(signed short x1, signed short y1, signed short x2, signed short y2) SEG(2);
void illuminate(signed short x, signed short y, signed short radiussquared) SEG(3);
/* src/magic.c */
unsigned short attack_tile(unsigned short x, unsigned short y, const char *str, const char *death_message, unsigned short damage) SEG(3);
unsigned short identify(void) SEG(3);
void entangle(unsigned short duration) SEG(3);
void confuse(unsigned short duration) SEG(3);
void hallucinate(unsigned short duration) SEG(3);
void paralyze(unsigned short duration) SEG(3);
void engulf_in_darkness(signed short duration) SEG(3);
void numb(unsigned short duration) SEG(3);
void detect_invisible(unsigned short duration) SEG(3);
void removecurses(void) SEG(3);
int enchant_item(void) SEG(3);
/* src/messagefield.c */
void UI_MF_Place(short ypos, short rows) SEG(4);
void message(const char *format, ...) SEG(3);
void vmessage(const char *format, va_list args) SEG(3);
void UI_MF_clear(void) SEG(3);
void UI_MF_history(void) SEG(3);
void UI_MF_sendmsg(const char *msg) SEG(3);
void UI_MF_wait(void) SEG(3);
/* src/mkmap.c */
void gen_map(int source, coord pos) SEG(3);
int mkmap_big_front(void) SEG(3);
void base_coat(void) SEG(3);
signed short place_room(room *r) SEG(3);
void place_hole(void) SEG(3);
void make_noise(unsigned short floor, unsigned short wall) SEG(3);
void cave_pass(unsigned short floor, unsigned short wall, void (*effect)(unsigned short floor, unsigned short wall, int x, int y, int neighbors)) SEG(3);
void cb_cave_partial(unsigned short floor, unsigned short wall, int x, int y, int neighbors) SEG(3);
void cave_partial_gen(unsigned short floor, unsigned short wall) SEG(3);
void cb_cave(unsigned short floor, unsigned short wall, int x, int y, int neighbors) SEG(3);
void cave_generation(unsigned short floor, unsigned short wall) SEG(3);
signed short place_corridors(void) SEG(3);
void fill_room(room *r) SEG(3);
void place_doors(void) SEG(3);
int make_door(int x, int y) SEG(3);
void place_items(void) SEG(3);
void make_connections(void) SEG(3);
void place_player_on_map(int source, coord pos) SEG(3);
/* src/monst.c */
signed short monstcanmove(signed short monst, signed short x, signed short y) SEG(3);
int monst_is_aligned_with_plr(int m) SEG(3);
signed short monstbytile(unsigned short x, unsigned short y) SEG(3);
void compress_monsters(void) SEG(3);
void place_monster(monster *monst, unsigned short x, unsigned short y) SEG(3);
const char *monstname(signed short n) SEG(3);
signed short player_can_see(unsigned short m) SEG(3);
int calculate_hit(int to_hit, int defense) SEG(3);
signed short monst_facing(signed short monst) SEG(3);
int monst_hit_plr(int attacknum, int monster) SEG(3);
int monst_hit_monst(int attacknum, int attacker, int target) SEG(3);
int monst_attack_type(int trigger, int monst, int always_hit) SEG(3);
void addrandommonst(void) SEG(3);
void addmonster(unsigned short x, unsigned short y, filelink type) SEG(3);
void addmonster_ptr(filelink *type, unsigned short x, unsigned short y) SEG(3);
void monst_remove(unsigned short monstid) SEG(3);
void monst_takedamage(signed short monstid, signed short damage, signed short is_melee) SEG(3);
void monst_heal(unsigned short monstid, unsigned short amt) SEG(4);
void monstmoveto(signed short monst, signed short x, signed short y) SEG(4);
unsigned short monst_detect_player(unsigned short i) SEG(4);
unsigned short monst_can_attack_player(unsigned short i) SEG(4);
void monstmoverandomly(signed short i, unsigned short attack) SEG(4);
void monstmovetowardsplayer(signed short i) SEG(4);
void monstmoveawayfromplayer(signed short i) SEG(4);
int monst_is_peaceful(int monstid) SEG(4);
int monst_is_pet(int monstid) SEG(4);
void monst_anger(unsigned short monstid) SEG(2);
void scare_monster(unsigned short monstid) SEG(4);
void scare_monster_force(int monstid) SEG(4);
void confuse_monster(unsigned short monstid) SEG(4);
void gather_wandering_monsters(void) SEG(4);
void place_wandering_monsters(void) SEG(4);
/* src/options.c */
int get_option(int option) SEG(0);
void set_option(int option, int value) SEG(0);
int count_options(void) SEG(6);
int count_choices(const char **choices) SEG(6);
void options_menu(void) SEG(4);
void load_options(void) SEG(5);
void save_options(void) SEG(0);
/* src/pet.c */
void pet_move(int pet) SEG(4);
void monst_swing_monst(int attacker, int target, int trigger) SEG(4);
void monst_attack_monst(int attacknum, int attacker, int target) SEG(4);
unsigned short monst_battle_pet(unsigned short monst) SEG(4);
/* src/player.c */
int plr_attack_monster_roll(int monstid, int modifier) SEG(4);
void init_player(unsigned short is_tutorial) SEG(4);
void apply_stat_mod_desc(signed short *target, const stat_mod_desc *s, signed char plus) SEG(4);
void update_player(void) SEG(4);
void enter_map(void) SEG(4);
void follow_connection(void) SEG(4);
void goto_level(filelink target_level_link, const spec_descriptor_ext_level *connection) SEG(3);
void plr_move(void) SEG(4);
void place_player_randomly(void) SEG(4);
void plr_step(signed short x, signed short y) SEG(5);
void plr_mod_stat(signed short which, signed short amt) SEG(4);
short plr_restore_stat(short which, short amt) SEG(4);
void plr_moveto(unsigned short x, unsigned short y, signed short displace_monst) SEG(4);
void plr_search(void) SEG(4);
void char_info(void) SEG(4);
/* src/rand.c */
unsigned char xrandom(unsigned short range) SEG(4);
unsigned char rrandom(range r) SEG(4);
signed short nrandom(signed short max, signed short min) SEG(4);
void lsrand(unsigned long s) SEG(4);
unsigned long lrand(void) SEG(4);
void feed_entropy(unsigned long entropy) SEG(4);
/* src/rle.c */
unsigned long checksum_bytes(void *data, unsigned int length) SEG(4);
int frleverify(FILE *f) SEG(4);
void frlewrite(void *data, size_t s, size_t granularity, FILE *f) SEG(4);
void frleread(void *data, size_t s, size_t granularity, FILE *f) SEG(5);
void frleinit(void) SEG(5);
void frleinit_read(FILE *f) SEG(5);
void frleinit_write(FILE *f, void (*outfunc)(unsigned char c, FILE *f)) SEG(5);
void frleinit_write_nochecksum(void (*outfunc)(unsigned char c, FILE *f)) SEG(5);
void frlefinalize(FILE *f) SEG(5);
void frleflush(FILE *fout) SEG(5);
void frleputc(unsigned char c, FILE *fout) SEG(5);
unsigned char rlegetc(void) SEG(5);
void rle_set_source(rle_source_type t, const void *s) SEG(5);
/* src/score.c */
void display_scores(unsigned long score) SEG(5);
void award_high_score(unsigned long score, const char *cause_of_death) SEG(5);
/* src/skill.c */
void init_skills(void) SEG(5);
void award_mark(void) SEG(5);
signed short weapon_skill_attack(void) SEG(5);
signed short weapon_skill_damage(void) SEG(5);
void print_skills(char *buf) SEG(5);
/* src/spell.c */
signed short study_book(unsigned short num_spells, unsigned short type, va_list spells) SEG(5);
void init_spells(void) SEG(5);
void cast_spell(void) SEG(5);
/* src/throw.c */
void throw_item_from_menu(void) SEG(5);
void throw_readied_item(void) SEG(5);
void fire_dir(int x, int y) SEG(6);
/* src/tilefield.c */
void UI_TF_MoveCamera(int x, int y) SEG(5);
void UI_TF_PlaceCamera(int x, int y) SEG(5);
void UI_TF_Scroll(int x, int y) SEG(5);
void UI_TF_Init(coord size) SEG(5);
void UI_TF_Place(coord pos, coord dimensions, const unsigned char *graphics, unsigned char tileheight, unsigned char tilewidth) SEG(5);
void UI_TF_Deinit(void) SEG(5);
void UI_TF_PutTile(int x, int y, unsigned char tnum, unsigned char lighting) SEG(5);
void UI_TF_PutTile_Color(int x, int y, unsigned char tnum, unsigned char lighting, colorinfo color) SEG(5);
void UI_TF_FullRedraw(void) SEG(5);
void UI_TF_PlaceCursor(int x, int y) SEG(5);
void UI_TF_DrawEffect(signed short x, signed short y, unsigned short tnum) SEG(5);
void UI_TF_ClearEffects(void) SEG(5);
/* src/tiles.c */
/* src/timer.c */
void init_timers(void) SEG(5);
void apply_timers(void) SEG(5);
int remove_expired_timers(void) SEG(5);
void add_timer(const timer_desc *desc, unsigned short duration) SEG(5);
/* src/use.c */
void use_item(void) SEG(5);
/* src/util.c */
void catprintf(char *target, const char *format, ...) SEG(5);
const char *retprintf(const char *format, ...) SEG(5);
const char *vretprintf(const char *format, va_list args) SEG(5);
coord trace_path(int x, int y, direction dir, int distance) SEG(5);
const char *pluralize(int num, const char *str) SEG(5);
const char *indefinite_article(const char *noun) SEG(5);
monstdesc *find_monster_description(int m) SEG(5);
void init_shuffle_tab(void) SEG(5);
const void *deref_file_ptr(filelink p) SEG(5);
filelink deref_file_ptr_partial(filelink p) SEG(6);
int isNull(filelink p) SEG(4);
/* sys/stub/graph.c */
void Graph_DrawTile(UI_Tilefield *tf, int x, int y, UI_TF_TileInfo tile) SEG(6);
void Graph_ClrScr(void) SEG(6);
void Graph_DrawChar(short x, short y, char c) SEG(6);
void Graph_DrawStr(short x, short y, const char *str) SEG(6);
void Graph_ClearRect(int left, int top, int right, int bottom) SEG(6);
/* sys/stub/main.c */
void display_title_screen(void) SEG(6);
void init_layout(void) SEG(6);
void sys_init(void) SEG(6);
void sys_init_data_file(void) SEG(6);
void sys_cleanup(void) SEG(6);
/* sys/stub/menu.c */
void UI_Menu_Set_Persist(unsigned short p) SEG(6);
int UI_Menu_Pick(rect r, int numchoices, void (*getchoice)(int N, char *buf)) SEG(6);
/* sys/stub/prompt.c */
int prompt(const char *msg) SEG(4);
void prompt_dir(const char *msg, direction *dir) SEG(4);
/* sys/stub/sysutil.c */
int read_char(void) SEG(6);
int key_pending(void) SEG(6);
void delay(void) SEG(6);
void UI_Dialog_Default(const char *content) SEG(6);
void UI_Dialog_Display(rect r, const char *content) SEG(6);
short FontHeight(void) SEG(6);
short FontWidth(unsigned char c) SEG(6);
void panic(const char *fmt, ...) SEG(6);
const char *get_keyname(short key) SEG(6);
