
#define DATA_FILE
#define CONST
#define TYPEDEF(a)

#include "config.h"
#include "util.h"
#include "items.h"
#include "timer.h"
#include "player.h"
#include "map.h"
#include "monst.h"
#include "constdata.h"
#include "options.h"
#include "world.h"


extern void message(char *str) = 0;
extern int random(int max, int min) = 1;
extern void plr_mod_stat(int stat, int amt) = 2;
extern void base_coat(void)=3;
extern int place_room(char *roominfo)=4;
extern void place_hole(void)=5;
extern int place_corridors(void)=6;
extern void place_doors(void)=7;
extern void fill_room(char *roominfo)=8;
extern void UI_Dialog_Default(void) = 9;
extern void make_connections(void)=10;
extern void place_items(void)=11;
extern void make_noise(int floor, int wall)=12;
extern void cave_generation(int floor, int wall)=13;
extern int prompt(char *str)=14;
extern void prompt_dir(char *prompt, char *ret)=15;
extern void illuminate(int x, int y, int rsquared)=16;
extern void calc_light(void)=17;
extern int attack_tile(int x, int y, char *description, char *causeofdeath, short damage)=18;
extern void delay(void)=19;
extern void UI_TF_DrawEffect(int x, int y, int c)=20;
extern void UI_TF_ClearEffects(void)=21;
extern int monstbytile(int x, int y)=22;
extern int tile_is_passable(int x, int y)=23;
extern int tile_is_transparent(int x, int y)=24;
extern int tile_is_occupied(int x, int y)=25;
extern struct player *get_plr(void)=26;
extern int plr_restore_stat(void)=27;
extern struct world *get_w(void)=28;
extern int player_gold()=29;
extern void debit_gold(int amt)=30;
extern char* deref_file_ptr(void)=31;
extern void place_item(struct item *i, int x, int y)=32;
extern void scare_monster(int m)=33;
extern void update_player(void)=34;
extern int identify(void)=35;
extern void UI_Menu_Set_Persist(int s)=36;
extern void draw_tile(int x, int y)=37;
extern void entangle(int time)=38;
extern void UI_MF_wait(void)=39;
extern int study_book(int num_spells, int type)=40;
extern void plr_moveto(int x, int y, int displace_monst)=41;
extern int give_item(struct item *itm, int silent)=42;
extern void confuse(int duration)=43;
extern void hallucinate(int duration)=44;
extern void timepass(int duration)=45;
extern void identify_type(int type)=46;
extern void addmonster(struct filelink *type, int x, int y)=47;
extern void end_game(char *cause)=48;
extern void die(char *cause)=49;
extern int fix_rust(void)=50;
extern char *monstname(int monstid)=51;
extern int strcmp(char *one, char *two)=52;
extern void monst_heal(int monst, int amt)=53;
extern void numb(int duration)=54;
extern void detect_invisible(int duration)=55;
extern void place_player_randomly(void)=56;
extern void removecurses(void)=57;
extern int enchant_item(void)=58;
extern char *n_itemname(int which)=59;
extern void monstmoveto(int monst, int x, int y)=60;
extern void webspinner_build(int monst, int tile_web, int tile_floor)=61;
extern void webspinner_cower(int monst, int tile_web, int tile_wall)=62;
extern int monst_battle_pet(int monst)=63;
extern int monst_detect_player(int monst)=64;
extern int monst_can_attack_player(int monst)=65;
extern void monstmovetowardsplayer(int monst)=66;
extern void monst_chat(int monst)=67;
extern char *retprintf(char *fmt)=68;
extern char *indefinite_article(char *str)=69;
extern void paralyze(int duration)=70;
extern void rust_inventory(int which)=71;
extern void monst_remove(int which)=72;
extern int monst_facing(int monst)=73;
extern int player_can_see(int monst)=74;
extern void monst_takedamage(int monst, int damage, int is_melee)=75;
extern int monstcanmove(int monst, int x, int y)=76;
extern void engulf_in_darkness(int duration)=77;
extern int top_item(int x, int y)=78;
extern int mkmap_big(void)=79;
extern void cave_partial_gen(int floor, int wall)=80;
extern void full_redraw(void)=81;
extern void monst_anger(int monstid)=82;
extern void confuse_monster(int monstid)=83;
extern void follow_connection(void)=84;
extern void plr_step(int x, int y)=85;

