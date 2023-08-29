void plr_heal(int amt);
void monst_drop_item(int monstid, int item_type, int qty);
void satiate(int amt);
void spell_teleport(void);
void plr_takedamage(int amt, char *cause_of_death);
void boost_max_stat(int stat, int amt);
void become_knight(void);
int attempt_lich_transformation(void);
int mspell_windblast(int caster, int damage, int target);
void clear_shops(void);

#define IS_IN_SHOP             0
#define HAVE_SPOKEN_TO_ORACLE  1
#define ENTERED_MAIN_TOWN      2
#define BOOK_PROGRESS_WEAPONRY 4
#define BOOK_PROGRESS_GEMOLOGY 5
#define HAVE_PET_ANGEL         6
#define HAVE_PET_HORSE         7
#define REFUSED_HORSE          8
#define REFUSED_SMITH          9
#define QUEST_TROLL            10
#define TROLL_PAID             11
#define QUEST_ILLUMINYTE       12
#define QUEST_DRAGON_INCAVE    13
#define QUEST_DRAGON_STATUS    14
#define GFLAG(a) (get_w()->game_flags[a])

#define QUEST_TROLL_BEGIN   0
#define QUEST_TROLL_GIVEN   1
#define QUEST_TROLL_SPAWNED 2
#define QUEST_TROLL_KILLED  3
#define QUEST_TROLL_DONE    4

#define QUEST_ILLUMINYTE_BEGIN   0
#define QUEST_ILLUMINYTE_PENDING 1
#define QUEST_ILLUMINYTE_DONE    2

#define FOUNTAIN_HEALING        0
#define FOUNTAIN_MANA           1
#define FOUNTAIN_POISON         2
#define FOUNTAIN_HALLUCINOGEN   3
#define FOUNTAIN_RESTORE        4
#define FOUNTAIN_NUMB           5
#define FOUNTAIN_ELEMENTAL      6
#define FOUNTAIN_DEPLETED_COLD  0
#define FOUNTAIN_DEPLETED_WARM  1
#define FOUNTAIN_DEPLETED_DIRTY 2
#define FOUNTAIN_INFO(a,b) (((a)<<4) + (b))
void drain_fountain(int x, int y);


