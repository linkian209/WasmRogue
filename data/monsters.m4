even;

m4_define(numMonsters, 0)
m4_define(monsterFreq, 0)

//{{{
m4_define(MONSTER, 
  {@m4_define({@numMonsters@}, m4_eval(numMonsters+1))
  m4_divert(SEQUENCE_STRINGS)
  m4_define({@MONSTER_NAME@}, {@MONSTER@}{@@}numMonsters{@@}NAME)
  export MONSTER_NAME;
  string: {@$2@};
  
  m4_divert(SEQUENCE_TABLES)
  even;
  export MONSTER_{@@}$1;
  link:  MONSTER_NAME;      //name
  uchar: $3;                //drawchar
  uchar: {@$5@};            //level
  uchar: {@$6@};            //dv
  uchar: {@$7@};            //pv
  sint:  {@$8@};            //hps
  uchar: {@$9@};            //spd
  uchar: {@$13@};           //power max
  uint:  {@$10@};           //AI
  link:  {@$15@};           //ai_active
  link:  {@$16@};           //ai_idle
  link:  {@$17@};           //ai_anger
  link:  {@$11@};           //on death
  link:  {@$12@};           //chat
  m4_divert(SEQUENCE_TEMP)
  m4_define({@numAttacks@}, 0)
  $19
  m4_divert(SEQUENCE_TABLES)
  uchar: numAttacks;         //numattacks
  uint:  {@$14@};            //xp
  uint:  {@$18@};            //flags
#ifdef SUPPORT_COLOR
  uchar: $4; uchar: $4;
#endif
  m4_undivert(SEQUENCE_TEMP)
  even;
 @})
//}}}
//{{{
m4_define(BASE_ATTACK,
 {@m4_define({@numAttacks@}, m4_eval(numAttacks+1))
  even;
  link: $1;       // Type
  range($3,$2)    // Damage
  schar: $4;      // To-hit
  uchar: $5;      // Trigger
  even;
 @})
//}}}

m4_define(ATT,         {@BASE_ATTACK(att_normal, $1, $2, 0,  MTRIGGER_NORMAL)@})
m4_define(ATTACK,      {@BASE_ATTACK($1,         $2, $3, $4, MTRIGGER_NORMAL)@})
m4_define(RANGEATTACK, {@BASE_ATTACK($1,         $2, $3, $4, MTRIGGER_RANGED)@})
m4_define(DEFATTACK,   {@BASE_ATTACK($1,         $2, $3, $4, MTRIGGER_DEFENSE)@})
m4_define(DEATHATTACK, {@BASE_ATTACK($1,         $2, $3, $4, MTRIGGER_DEATH)@})
m4_define(SEEATTACK,   {@BASE_ATTACK($1,         $2, $3, $4, MTRIGGER_SEEN)@})
m4_define(PREATTACK,   {@BASE_ATTACK($1,         $2, $3, $4, MTRIGGER_PREEMPT)@})

//{{{
BEGIN_JUMPTAB(MONSTERTABLE, jt_avglevel)
//        Monster                        Freq   Level range
  JTENTRY(MONSTERTABLE_INDEPTH,          93,    range(255,1))
  JTENTRY(MONSTERTABLE_OUTOFDEPTH,       6,     range(255,2))
  JTENTRY(MONSTERTABLE_WAYOUTOFDEPTH,    1,     range(255,3))
END_JUMPTAB()
//}}}
//{{{
BEGIN_JUMPTAB(MONSTERTABLE_INDEPTH, jt_avglevel)
  JTENTRY(MONSTER_BAT,                   2,     range(2,1))
  JTENTRY(MONSTER_EMU,                   2,     range(2,1))
  JTENTRY(MONSTER_SNAKE,                 3,     range(3,1))
  JTENTRY(MONSTER_GIANTRAT,              2,     range(3,1))
  JTENTRY(MONSTER_JACKAL,                1,     range(3,1))
  JTENTRY(MONSTER_KOBOLD,                3,     range(4,1))
  JTENTRY(MONSTER_GIANTANT,              3,     range(5,2))
  JTENTRY(MONSTER_GOBLIN,                3,     range(5,3))
  JTENTRY(MONSTER_RATTLESNAKE,           3,     range(6,3))
  JTENTRY(MONSTER_MIMIC,                 3,     range(7,4))
  JTENTRY(MONSTER_ORC,                   3,     range(7,4))
  JTENTRY(MONSTER_GIANTSPIDER,           1,     range(8,4))
  JTENTRY(MONSTER_ZOMBIE,                3,     range(9,5))
  JTENTRY(MONSTER_DARK_WIZARD,           1,     range(11,5))
  JTENTRY(MONSTER_VORTEX,                2,     range(11,5))
  JTENTRY(MONSTER_LEPRECHAUN,            2,     range(11,5))
  JTENTRY(MONSTER_NYMPH,                 1,     range(12,6))
  JTENTRY(MONSTER_AQUATOR,               1,     range(14,6))
  JTENTRY(MONSTER_HOBGOBLIN,             3,     range(11,6))
  JTENTRY(MONSTER_GRUE,                  1,     range(12,7))
  JTENTRY(MONSTER_ICEMONSTER,            3,     range(13,7))
  JTENTRY(MONSTER_KILLERBEE,             3,     range(15,7))
  JTENTRY(MONSTER_FIRE_MAGE,             1,     range(17,8))
  JTENTRY(MONSTER_WIND_MAGE,             1,     range(17,8))
  JTENTRY(MONSTER_PHANTOM,               3,     range(17,8))
  JTENTRY(MONSTER_TROLL,                 2,     range(25,8))
  JTENTRY(MONSTER_WRAITH,                2,     range(27,9))
  JTENTRY(MONSTER_GIANTSLUG,             2,     range(27,9))
  JTENTRY(MONSTER_CENTAUR,               2,     range(28,9))
  JTENTRY(MONSTER_YETI,                  2,     range(30,10))
  JTENTRY(MONSTER_GRIFFIN,               2,     range(35,12))
  JTENTRY(MONSTER_JABBERWOCK,            2,     range(45,14))
  JTENTRY(MONSTER_VAMPIRE,               2,     range(55,14))
  JTENTRY(MONSTER_DRAGON,                2,     range(255,16))
END_JUMPTAB()
//}}}
//{{{
BEGIN_JUMPTAB(MONSTERTABLE_OUTOFDEPTH, jt_avglevel)
  JTENTRY(MONSTER_RATTLESNAKE,           3,     range(3,1))
  JTENTRY(MONSTER_MIMIC,                 3,     range(4,1))
  JTENTRY(MONSTER_ORC,                   3,     range(4,2))
  JTENTRY(MONSTER_GIANTSPIDER,           1,     range(5,2))
  JTENTRY(MONSTER_ZOMBIE,                3,     range(6,3))
  JTENTRY(MONSTER_DARK_WIZARD,           4,     range(8,3))
  JTENTRY(MONSTER_VORTEX,                2,     range(8,3))
  JTENTRY(MONSTER_LEPRECHAUN,            2,     range(8,3))
  JTENTRY(MONSTER_NYMPH,                 3,     range(9,4))
  JTENTRY(MONSTER_AQUATOR,               3,     range(10,4))
  JTENTRY(MONSTER_HOBGOBLIN,             3,     range(10,4))
  JTENTRY(MONSTER_ICEMONSTER,            3,     range(10,4))
  JTENTRY(MONSTER_GRUE,                  3,     range(11,5))
  JTENTRY(MONSTER_KILLERBEE,             3,     range(12,5))
  JTENTRY(MONSTER_FIRE_MAGE,             3,     range(12,5))
  JTENTRY(MONSTER_WIND_MAGE,             1,     range(12,5))
  JTENTRY(MONSTER_PHANTOM,               3,     range(13,6))
  JTENTRY(MONSTER_TROLL,                 2,     range(15,6))
  JTENTRY(MONSTER_WRAITH,                2,     range(20,7))
  JTENTRY(MONSTER_GIANTSLUG,             2,     range(21,7))
  JTENTRY(MONSTER_CENTAUR,               2,     range(22,7))
  JTENTRY(MONSTER_YETI,                  2,     range(25,8))
  JTENTRY(MONSTER_GRIFFIN,               2,     range(28,10))
  JTENTRY(MONSTER_JABBERWOCK,            2,     range(45,11))
  JTENTRY(MONSTER_VAMPIRE,               2,     range(55,12))
  JTENTRY(MONSTER_DRAGON,                2,     range(255,14))
END_JUMPTAB()
//}}}
//{{{
BEGIN_JUMPTAB(MONSTERTABLE_WAYOUTOFDEPTH, jt_avglevel)
  JTENTRY(MONSTER_ZOMBIE,                3,     range(4,1))
  JTENTRY(MONSTER_DARK_WIZARD,           3,     range(4,1))
  JTENTRY(MONSTER_VORTEX,                2,     range(4,1))
  JTENTRY(MONSTER_LEPRECHAUN,            2,     range(4,1))
  JTENTRY(MONSTER_NYMPH,                 1,     range(5,2))
  JTENTRY(MONSTER_AQUATOR,               1,     range(5,2))
  JTENTRY(MONSTER_HOBGOBLIN,             3,     range(5,2))
  JTENTRY(MONSTER_GRUE,                  3,     range(6,3))
  JTENTRY(MONSTER_ICEMONSTER,            3,     range(6,3))
  JTENTRY(MONSTER_KILLERBEE,             3,     range(6,3))
  JTENTRY(MONSTER_FIRE_MAGE,             3,     range(7,4))
  JTENTRY(MONSTER_WIND_MAGE,             1,     range(7,4))
  JTENTRY(MONSTER_PHANTOM,               3,     range(7,4))
  JTENTRY(MONSTER_TROLL,                 2,     range(7,4))
  JTENTRY(MONSTER_WRAITH,                2,     range(8,5))
  JTENTRY(MONSTER_GIANTSLUG,             2,     range(8,5))
  JTENTRY(MONSTER_CENTAUR,               2,     range(8,5))
  JTENTRY(MONSTER_YETI,                  2,     range(9,6))
  JTENTRY(MONSTER_GRIFFIN,               2,     range(12,8))
  JTENTRY(MONSTER_JABBERWOCK,            2,     range(16,10))
  JTENTRY(MONSTER_VAMPIRE,               2,     range(19,10))
  JTENTRY(MONSTER_DRAGON,                2,     range(255,12))
END_JUMPTAB()
//}}}

//{{{
BEGIN_JUMPTAB(MONSTERTABLE_DRAGONCAVE, jt_avglevel)
  JTENTRY(MONSTER_GIANTSPIDER,           1,     range(255,1))
  JTENTRY(MONSTER_VORTEX,                2,     range(255,1))
  JTENTRY(MONSTER_HOBGOBLIN,             3,     range(255,1))
  JTENTRY(MONSTER_GRUE,                  1,     range(255,1))
  JTENTRY(MONSTER_PHANTOM,               3,     range(255,1))
  JTENTRY(MONSTER_TROLL,                 2,     range(255,1))
  JTENTRY(MONSTER_WRAITH,                2,     range(255,1))
  JTENTRY(MONSTER_FIREELEMENTAL,         2,     range(255,1))
  JTENTRY(MONSTER_GIANTSLUG,             2,     range(255,1))
  JTENTRY(MONSTER_CENTAUR,               2,     range(255,1))
END_JUMPTAB()
//}}}
//{{{
BEGIN_JUMPTAB(MONSTERTABLE_WIZARDSTOWER, jt_avglevel)
  JTENTRY(MONSTER_GIANTSPIDER,           1,     range(255,1))
  JTENTRY(MONSTER_VORTEX,                2,     range(255,1))
  JTENTRY(MONSTER_GRUE,                  1,     range(255,1))
  JTENTRY(MONSTER_PHANTOM,               2,     range(255,1))
  JTENTRY(MONSTER_WRAITH,                2,     range(255,1))
  JTENTRY(MONSTER_FIREELEMENTAL,         2,     range(255,1))
  JTENTRY(MONSTER_DARK_WIZARD,           4,     range(255,1))
  JTENTRY(MONSTER_FIRE_MAGE,             4,     range(255,1))
  JTENTRY(MONSTER_WIND_MAGE,             4,     range(255,1))
  JTENTRY(MONSTER_GIANTSLUG,             1,     range(255,1))
END_JUMPTAB()
//}}}

////////////////////////////////////////////////////////////////////////////////
//                    Name
//       Char  Color   Level DV  PV  HPs  Spd
//       AI             Death func         Chat func               Pw  XP
//       AI Active      AI Idle            AI Anger
//       Flags
//       Attacks
////////////////////////////////////////////////////////////////////////////////

// Special monsters (not-randomly generated)
//{{{
MONSTER( SHOPKEEPER,  gettext("Shopkeeper"),
         '@',  WHITE,   18,  25, 3,  60,  13,
         AI_SHOPKEEP,   NULL,              NULL,                   0,  200,
         NULL,          NULL,              shk_anger,
         MONSTFLAG_HASHANDS,
         {@ATT(6,13)@} )
//}}}
//{{{
MONSTER( STABLE_SALESMAN, gettext("Salesman"),
         '@',  WHITE,   18,  25, 3,  60,  13,
         AI_NPC_SIT,    NULL,              stable_shopkeep_chat,   0,  200,
         npc_chat,      NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(6,13)@} )
//}}}
//{{{
MONSTER( SMITHY,      gettext("Blacksmith"),
         '@',  WHITE,   18,  25, 4,  45,  10,
         AI_NPC_SIT,    NULL,              smithy_chat,            0,  200,
         npc_chat,      NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(10,16)@} )
//}}}
//{{{
MONSTER( ORACLE,      gettext("Oracle"),
         '@',  LBLUE,   18,  30, 3,  60,  10,
         AI_NPC_SIT,    NULL,              oracle_chat,            0,  200,
         npc_chat,      NULL,              NULL,
         MONSTFLAG_HASHANDS|MONSTFLAG_FEARLESS,
         {@ATT(6,13)@} )
//}}}
//{{{
MONSTER( ELDER,       gettext("Village elder"),
         '@',  WHITE,   18,  30, 3,  75,  13,
         AI_NPC_SIT,    NULL,              elder_chat,             0,  200,
         npc_chat,      NULL,              NULL,
         MONSTFLAG_HASHANDS|MONSTFLAG_FEARLESS,
         {@ATT(10,16)@} )
//}}}
//{{{
MONSTER( MAYOR,       gettext("City Mayor"),
         '@',  WHITE,   18,  35, 4,  85,  14,
         AI_NPC_SIT,    NULL,              mayor_chat,             0,  200,
         npc_chat,      NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(16,25)@} )
//}}}
//{{{
MONSTER( THUNRARR,    gettext("Dwarf named Thunrarr"),
         'h', YELLOW,   18,  30, 3,  75,  13,
         AI_NPC_SIT,    NULL,              thunrarr_chat,          0,  200, 
         npc_chat,      NULL,              NULL,
         MONSTFLAG_HASHANDS|MONSTFLAG_FEARLESS,
         {@ATT(10,16)@} )
//}}}
//{{{
MONSTER( BRIDGE_TROLL, gettext("Bridge troll"),
         'T',  YELLOW,  9,   19, 2,  35,  10,
         AI_NPC_SIT,    bridge_troll_die,  bridge_troll_chat,      0,  225,
         npc_chat,      NULL,              NULL,
         MONSTFLAG_REGENERATE|MONSTFLAG_HASHANDS,
         {@ATT(10,15)@} )
//}}}
//{{{
MONSTER( LICH,        gettext("Lich"),
         'L',  LRED,    16,  25, 0,  100, 13,
         AI_HOSTILE,    lich_die,          NULL,                   10, 1000, 
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS,
         {@ATTACK(mspell_lich_melee, 8, 14, 0)
           RANGEATTACK(mspell_lich_range, 14, 20, 0)
           SEEATTACK(mspell_lich_see, 0, 0, 0)
         @})
//}}}

// Summonlings
//{{{
MONSTER( SKELETON,      gettext("Skeleton"),
         'S',  LWHITE,  3,   6,  0,  12,  10,
         AI_HOSTILE,    NULL,              NULL,                  0,  20,
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS,
         {@ATT(3,5,0)@} )
//}}}
//{{{
MONSTER( SUMMON_SKELETON, gettext("Skeleton"),
         'S',  LWHITE,  3,   6,  0,  12,  10,
         AI_PET,        minion_skeleton_die,NULL,                  0,  0,
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS,
         {@ATT(3,5,0)@} )
//}}}
//{{{
MONSTER( SUMMON_ZOMBIE,  gettext("Zombie"),
         'Z',  WHITE,   7,   13, 2,  25,  6, 
         AI_PET,        minion_zombie_die, NULL,                   0,  0,
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS,
         {@ATTACK(att_claw, 4, 10, 0)
           ATTACK(att_claw, 4, 10, 0)
         @} )
//}}}
//{{{
MONSTER( SUMMON_MUMMY,   gettext("Mummy"),
         'M',  LWHITE,  9,   16, 1,  40,  10,
         AI_PET,        minion_mummy_die,  NULL,                   0,  0,
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS,
         {@ATT(9,14,0)@} )
//}}}
//{{{
MONSTER( SUMMON_WRAITH,  gettext("Wraith"),
         'W',  LBLACK,  11,  22, 0,  50,  10,
         AI_PET,        minion_wraith_die, NULL,                   0,  0,
         NULL,          NULL,              NULL,
         MONSTFLAG_PASSWALL|MONSTFLAG_FEARLESS,
         {@ATT(11,15)@} )
//}}}
//{{{
MONSTER( SUMMON_ANGEL,   gettext("Angel"),
         'A',  LYELLOW, 12,  15, 0,  50,  10,
         AI_PET,        minion_angel_die,  NULL,                   0,  0,
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS,
         {@ATT(7,11)@} )
//}}}
//{{{
MONSTER( PET_HORSE,   gettext("Horse"),
         'u',  YELLOW,  9,   15, 0,  35,  15,
         AI_PET,        minion_horse_die,  NULL,                   0,  0,
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_kick, 6, 9, 0)@} )
//}}}

// Misc.
//{{{
MONSTER( HORSE,       gettext("Horse"),
         'u',  YELLOW,  9,   15, 0,  35,  15,
         AI_DONTCARE,   NULL,              NULL,                   0,  0,
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_kick, 6, 9, 0)@} )
//}}}
//{{{
MONSTER( WATERELEMENTAL, gettext("Water elemental"),
         'E',  LBLUE,   10,  7,  0,  20,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  70,  
         NULL,          NULL,              NULL,
         0,
         {@ATT(7, 13)@} )
//}}}

// Townfolk
//{{{
MONSTER( FISHERMAN,   gettext("Fisherman"),
         'h',  LBLUE,   3,   5,  0,  10,  10,
         AI_NPC_SIT,    NULL,              NULL,                   0,  0,
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(1,3)@} )
//}}}
//{{{
MONSTER( COMMONER,    gettext("Commoner"),
         'h',  YELLOW,  3,   5,  0,  10,  10,
         AI_PEACEFUL,   NULL,              NULL,                   0,  0,   
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(1,3)@} )
//}}}
//{{{
MONSTER( DWARF,       gettext("Dwarf"),
         'h',  YELLOW,  3,   5,  0,  10,  10,
         AI_PEACEFUL,   NULL,              NULL,                   0,  0,   
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(1,3)@} )
//}}}

// Regular monsters
//{{{
MONSTER( BAT,         gettext("Bat"),
         'B',  YELLOW,  1,   3,  0,  4,   15,
         AI_DONTCARE,   NULL,              NULL,                   0,  2,   
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_claw, 1, 2, 0)@} )
//}}}
//{{{
MONSTER( EMU,         gettext("Emu"),
         'E',  LBLUE,   1,   4,  0,  8,   10,
         AI_HOSTILE,    NULL,              NULL,                   0,  8,   
         NULL,          NULL,              NULL,
         0,
         {@ATT(1,3)@} )
//}}}
//{{{
MONSTER( GIANTRAT,    gettext("Giant rat"),
         'r',  YELLOW,  1,   5,  0,  4,   10,
         AI_HOSTILE,    NULL,              NULL,                   0,  9,   
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_disease_bite, 2, 3, 0)@} )
//}}}
//{{{
MONSTER( SNAKE,       gettext("Snake"),
         's',  LYELLOW, 1,   5,  1,  5,   10,
         AI_HOSTILE,    NULL,              NULL,                   0,  11,  
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_bite, 2, 3, 0)@} )
//}}}
//{{{
MONSTER( JACKAL,      gettext("Jackal"),
         'j',  YELLOW,  1,   4,  0,  4,   12,
         AI_HOSTILE,    NULL,              NULL,                   0,  5,   
         NULL,          NULL,              NULL,
         MONSTFLAG_GROUP,
         {@ATTACK(att_bite, 1, 2, 0)@} )
//}}}
//{{{
MONSTER( KOBOLD,      gettext("Kobold"),
         'K',  LGREEN,  2,   6,  0,  10,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  15,  
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(2,4)@} )
//}}}
//{{{
MONSTER( GIANTANT,    gettext("Giant ant"),
         'a',  YELLOW,  2,   4,  2,  7,   10,
         AI_HOSTILE,    NULL,              NULL,                   0,  20,  
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_bite, 3, 6, 0)@} )
//}}}
//{{{
MONSTER( GOBLIN,      gettext("Goblin"),
         'g',  LBLUE,   3,   6,  0,  15,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  25,  
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(3,8)@} )
//}}}
//{{{
MONSTER( RATTLESNAKE, gettext("Rattlesnake"),
         'R',  LRED,    4,   6,  2,  16,  8,
         AI_HOSTILE,    rattlesnake_die,   NULL,                   0,  30,  
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_poison_bite, 2, 6, 0)@} )
//}}}
//{{{
MONSTER( MIMIC,       gettext("Mimic"),
         '$',  LYELLOW, 4,   8,  2,  15,  10,
         AI_MIMIC,      NULL,              NULL,                   0,  40,  
         NULL,          mimic_idle,        NULL,
         MONSTFLAG_FEARLESS,
         {@ATT(9,9)@} )
//}}}
//{{{
MONSTER( ORC,         gettext("Orc"),
         'O',  WHITE,   3,   7,  1,  20,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  50,  
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(3,9)@} )
//}}}
//{{{
MONSTER( GIANTSPIDER, gettext("Giant spider"),
         'S',  LCYAN,   6,   9,  1,  16,  10,
         AI_WEBSPINNER,      NULL,         NULL,                   0,  50,  
         spider_active, spider_idle,       NULL,
         0,
         {@ATTACK(att_poison_bite, 3, 5, 0)@} )
//}}}
//{{{
MONSTER( ZOMBIE,      gettext("Zombie"),
         'Z',  WHITE,   7,   13, 2,  25,  6,
         AI_HOSTILE,    NULL,              NULL,                   0,  60,  
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS,
         {@ATTACK(att_claw, 4, 10, 0)
           ATTACK(att_claw, 4, 10, 0)@} )
//}}}
//{{{
MONSTER( DARK_WIZARD, gettext("Dark wizard"),
         'W',  LBLUE,   10,  10, 0,  20,  10,
         AI_HOSTILE,    NULL,              NULL,                   30, 60,
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(3,8)
           SEEATTACK(mspell_summon_skeleton, 0, 0, 0)
           RANGEATTACK(mspell_magic_missile, 8, 14, 0) @} )
//}}}
//{{{
MONSTER( LEPRECHAUN,  gettext("Leprechaun"),
         'L',  LGREEN,  6,   14, 0,  15,  13,
         AI_HOSTILE,    leprechaun_die,    NULL,                   0,  60,  
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATTACK(att_stealgold, 3, 7, 0)@} )
//}}}
//{{{
MONSTER( NYMPH,       gettext("Nymph"),
         'N',  LGREEN,  7,   14, 0,  17,  13,
         AI_HOSTILE,    NULL,              NULL,                   0,  70,  
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATTACK(att_stealitem, 1, 4, 0)@} )
//}}}
//{{{
MONSTER( AQUATOR,     gettext("Aquator"),
         'A',  YELLOW,  6,   15, 2,  25,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  70,  
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_rust, 0, 0, 0)@} )
//}}}
//{{{
MONSTER( VORTEX,      gettext("Vortex"),
         'v',  LCYAN,   10,  12, 0,  20,  10,
         (MONST_WANDER_WHEN_IDLE|MONST_CUST_WHEN_ACTIVE),
                        NULL,              NULL,                   0,  50,  
         vortex_active, NULL,              NULL,
         MONSTFLAG_FEARLESS,
         {@ATTACK(att_vortex_debris, 6, 11, 0)@} )
//}}}
//{{{
MONSTER( GRUE,        gettext("Grue"),
         'G',  LBLACK,  8,   5,  0,  25,  10,
         (MONST_CUST_WHEN_IDLE|MONST_CUST_WHEN_ACTIVE),
                        NULL,              NULL,                   30, 140, 
         grue_active,   grue_idle,         NULL,
         MONSTFLAG_HASHANDS,
         {@PREATTACK(att_walk_into_grue, 14, 21, 0)
           ATTACK(att_bite, 7, 10, 0) @} )
//}}}
//{{{
MONSTER( ICEMONSTER,  gettext("Ice Monster"),
         'I',  LCYAN,   6,   15, 1,  15,  2,
         AI_HOSTILE,    NULL,              NULL,                   0,  30,  
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_paral_only, 3, 5, 5)
           DEFATTACK(att_paral_only, 13, 20, 15)@} )
//}}}
//{{{
MONSTER( KILLERBEE,   gettext("Killer bee"),
         'b',  LYELLOW, 7,   16, 0,  9,   12,
         AI_HOSTILE,    NULL,              NULL,                   0,  40,  
         NULL,          NULL,              NULL,
         MONSTFLAG_GROUP,
         {@ATTACK(att_poison_sting, 4, 6, 0)@} )
//}}}
//{{{
MONSTER( HOBGOBLIN,   gettext("Hobgoblin"),
         'H',  YELLOW,  8,   15, 1,  15,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  60,  
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(8,12)@} )
//}}}
//{{{
MONSTER( FIREELEMENTAL, gettext("Fire elemental"),
         'E',  LRED,    10,  7,  0,  20,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  70,  
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_burn, 7, 13, 0)@} )
//}}}
//{{{
MONSTER( FIRE_MAGE,   gettext("Fire mage"),
         'W',  LRED,    10,  10, 0,  20,  10,
         AI_HOSTILE,    NULL,              NULL,                   45, 120,
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(3,8)
           SEEATTACK(mspell_summon_fire_elemental, 0, 0, 0)
           RANGEATTACK(mspell_fire_mage_fireball, 12, 18, 0) @} )
//}}}
//{{{
MONSTER( WIND_MAGE,   gettext("Wind mage"),
         'W',  LWHITE,  10,  10, 0,  20,  10,
         AI_HOSTILE,    NULL,              NULL,                   65, 120,
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATTACK(mspell_wind_mage_windblast, 7, 12, 0)
           SEEATTACK(mspell_summon_vortex, 0, 0, 0)
         @} )
//}}}
//{{{
MONSTER( PHANTOM,     gettext("Phantom"),
         'P',  WHITE,   9,   15, 0,  15,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  80,  
         NULL,          NULL,              NULL,
         MONSTFLAG_INVISIBLE|MONSTFLAG_HASHANDS,
         {@ATT(8,12)@} )
//}}}
//{{{
MONSTER( TROLL,       gettext("Troll"),
         'T',  YELLOW,  9,   19, 2,  35,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  120, 
         NULL,          NULL,              NULL,
         MONSTFLAG_REGENERATE|MONSTFLAG_HASHANDS,
         {@ATT(10,15)@} )
//}}}
//{{{
MONSTER( WRAITH,      gettext("Wraith"),
         'W',  LBLACK,  9,   22, 0,  30,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  100, 
         NULL,          NULL,              NULL,
         MONSTFLAG_PASSWALL|MONSTFLAG_FEARLESS,
         {@ATT(6,12)@} )
//}}}
//{{{
MONSTER( GIANTSLUG,   gettext("Giant slug"),
         'S',  YELLOW,  9,   16, 3,  30,  10,
         AI_HOSTILE,    NULL,              NULL,                   15, 100, 
         NULL,          NULL,              NULL,
         0,
         {@ATTACK(att_bite, 6, 12, 0)
		   RANGEATTACK(att_acid_spit, 7, 15, 0)@} )
//}}}
//{{{
MONSTER( CENTAUR,     gettext("Centaur"),
         'C',  YELLOW,  10,  21, 2,  35,  15,
         AI_HOSTILE,    NULL,              NULL,                   0,  120, 
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATTACK(att_kick, 8, 16, 0)@} )
//}}}
//{{{
MONSTER( YETI,        gettext("Yeti"),
         'Y',  YELLOW,  11,  23, 2,  45,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  140, 
         NULL,          NULL,              NULL,
         MONSTFLAG_HASHANDS,
         {@ATT(9,15)@} )
//}}}
//{{{
MONSTER( GRIFFIN,     gettext("Griffin"),
         'G',  LWHITE,  13,  30, 0,  33,  20,
         AI_HOSTILE,    NULL,              NULL,                   0,  150, 
         NULL,          NULL,              NULL,
         0,
         {@ATT(8,14)@} )
//}}}
//{{{
MONSTER( JABBERWOCK,  gettext("Jabberwock"),
         'J',  LRED,    15,  30, 3,  50,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  200, 
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS,
         {@ATT(10,25)@} )
//}}}
//{{{
MONSTER( VAMPIRE,     gettext("Vampire"),
         'V',  LBLUE,   16,  25, 0,  30,  10,
         AI_HOSTILE,    NULL,              NULL,                   0,  250, 
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS|MONSTFLAG_HASHANDS|MONSTFLAG_VAMPIRIC,
         {@ATTACK(att_bite_vampiric, 6, 12, 0)@} )
//}}}
//{{{
MONSTER( DRAGON,      gettext("Dragon"),
         'D',  LRED,    20,  25, 3,  65,  12,
         AI_HOSTILE,    dragon_die,        NULL,                   60, 500, 
         NULL,          NULL,              NULL,
         MONSTFLAG_FEARLESS,
         {@ATT(8,14)
           ATT(8,14)
           RANGEATTACK(att_dragon_breath, 20, 35, 0)@} )
//}}}

//{{{
void monst_drop_item(int monstid, int item_type, int qty)
{
	char buf[64]; //HACKHACK - workaround for inability to put structs on the
	              // stack directly
	
	struct item *itm = buf;
	struct monster *m = &(get_w()->m[monstid]);
	
	itm->type = item_type; itm->next = 0; itm->stacksize = qty;
	itm->flags = 0; itm->plus = 0; itm->hotkey = 0; itm->rustiness = 0;
	
	place_item(itm, m->x, m->y);
}
//}}}

//{{{
void rattlesnake_die(int monstid)
{
	monst_drop_item(monstid, ITEM_RATTLESNAKE_TOOTH, 2);
}
//}}}
//{{{
void leprechaun_die(int monstid)
{
	if(random(3,1) == 1)
		monst_drop_item(monstid, ITEM_GOLD_PIECE, random(50, 25));
}
//}}}
//{{{
void dragon_die(int monstid)
{
	if(GFLAG(QUEST_DRAGON_STATUS)==1)
		GFLAG(QUEST_DRAGON_STATUS) = 2;
}
//}}}

//{{{
void oracle_chat(int monstid)
{
	if( get_w()->game_flags[HAVE_SPOKEN_TO_ORACLE] == 0 )
	{
		get_w()->game_flags[HAVE_SPOKEN_TO_ORACLE] = 1;
		message(gettext("The Oracle speaks..."));
		UI_MF_wait();
		UI_Dialog_Default(
gettext("That which you seek, the Amulet of Yendor, is long gone from this place, \
though here it once was. Though many seek it, the Amulet has as yet evaded \
all. But though it is hidden, it is not lost. Seek it between the mountains \
in a land to the south, and you may find it, but beware the creatures that \
guard it, and know that the Amulet is believed to possess a will of its own.")
			);
	} else {
	}
}
//}}}
//{{{
void stable_shopkeep_chat(int monstid)
{
	int create_pet;
	int d[1];
	if( get_w()->game_flags[REFUSED_HORSE] )
	{
		get_w()->game_flags[REFUSED_HORSE] -= 1;
	}
	else if( !(get_w()->game_flags[HAVE_PET_HORSE]) )
	{
		if(prompt(gettext("The salesman says \"fine horse, only 700 gold!\" Buy one?")))
		{
			if( player_gold() >= 700)
			{
				create_pet = 1;
				debit_gold(700);
				if(get_plr()->satiation <= 600)
				if(prompt(gettext("You're so hungry, you could eat a horse! Do so?")))
					// TRANSLATORS: This is a pun on an English-language figure
					// of speech. It probably doesn't make much sense in other
					// languages.
				{
					message(gettext("You feel sick in more ways than one."));
					satiate(20000);
					plr_mod_stat(STAT_TOUGHNESS, -2);
					message(gettext("The salesman is disgusted."));
					create_pet = 0;
				}
				if(create_pet)
					create_companion(LINK_PET_HORSE);
			} else
				message(gettext("You can't afford it."));
		}
		else
		{
			get_w()->game_flags[REFUSED_HORSE] = 5;
		}
	}
}
//}}}
//{{{
void smithy_chat(int monstid)
{
	int ret;
	int repetition = 0;
	if(GFLAG(REFUSED_SMITH) > 0)
	{
		GFLAG(REFUSED_SMITH) -= 1;
	}
	else if(prompt(gettext("The smith asks \"need anything fixed?\"")))
	{
		do
		{
			ret = fix_rust();
			if(ret == 1) message(gettext("\"You don't have anything that needs fixing.\""));
			else if(ret == 2) message(gettext("\"Come back later.\""));
			else if(ret == 3) message(gettext("\"Come back later.\""));
		}
		while(ret == 0);
		GFLAG(REFUSED_SMITH) = 5;
	} else {
		GFLAG(REFUSED_SMITH) = 5;
	}
}
//}}}
//{{{
void elder_chat(int monstid)
{
	if(GFLAG(QUEST_TROLL) == QUEST_TROLL_BEGIN)
	{
		message(
gettext("The village elder says \"in the forest to the east, a troll has \
taken over the bridge. If you would slay it, I will reward you.\"") );
		GFLAG(QUEST_TROLL) = QUEST_TROLL_GIVEN;
	} else if( GFLAG(QUEST_TROLL) == QUEST_TROLL_KILLED )
	{
		message( gettext("\"Thank you. Here is 2000 gold, as promised.\"") );
		give_item_type(ITEM_GOLD_PIECE, 2000, 0);
		GFLAG(QUEST_TROLL) = QUEST_TROLL_DONE;
	}
}
//}}}
//{{{
void mayor_chat(int monstid)
{
	if(GFLAG(QUEST_DRAGON_STATUS) == 0 && get_w()->plr.class == CLASS_FIGHTER)
	{
		GFLAG(QUEST_DRAGON_STATUS) = 1;
		message(
gettext("The mayor says \"Prove your worth by killing a dragon and you, too, \
can have a worthless title of nobility.\"") );
	} else if( GFLAG(QUEST_DRAGON_STATUS) == 2)
	{
		message(
gettext("The mayor says \"I hear you have slain a dragon. That would make you \
a knight. Here's your shining armor.\"") );
		give_item_type(ITEM_ARMR_SHINING, 1, 0);
		GFLAG(QUEST_DRAGON_STATUS) = 3;
	}
}
//}}}
//{{{
void thunrarr_chat(int monstid)
{
	if(GFLAG(QUEST_ILLUMINYTE) == QUEST_ILLUMINYTE_BEGIN)
	{
		message(
gettext("Thunrarr, the dwarf before you looks old, worn and unhappy. \"Used to\
be, we'd get illuminyte from the mines nearby. But no one dares go in there\
anymore. If you could bring back six pieces, I'm sure I could find something\
to make it worth your while."));
		GFLAG(QUEST_ILLUMINYTE) = QUEST_ILLUMINYTE_PENDING;
	}
	else if(GFLAG(QUEST_ILLUMINYTE) == QUEST_ILLUMINYTE_PENDING)
	{
		if(have_component(ITEM_ILLUMINYTE, 6)) {
			if(prompt(
gettext("I'd recognize that glow anywhere! Will you give me some illuminyte?")
                     ))
			{
				deplete_component(ITEM_ILLUMINYTE, 6);
				message(gettext("Thank you. Once, I was a fierce warrior, but now I have no use for this armor. Please, take it."));
				GFLAG(QUEST_ILLUMINYTE) = QUEST_ILLUMINYTE_DONE;
				give_item_type(ITEM_ARMR_PLATE, 1, 3);
			} else {
				message(gettext("Well, please come back when you have some to spare."));
			}
		} else {
			message(gettext("Thunrarr asks \"Have you some illuminyte?\""));
		}
	}
}
//}}}
//{{{
void bridge_troll_chat(int monstid)
{
	if(!GFLAG(TROLL_PAID))
	{
		if(prompt(gettext("The troll demands a toll of twenty gold. Pay?"))) {
			if(player_gold() >= 20) {
				debit_gold(20);
				GFLAG(TROLL_PAID) = 1;
				message(gettext("The troll mumbles something."));
			}
			else
			{
				message(gettext("You don't have enough gold. The troll gets angry!"));
				get_w()->m[monstid].flags &= ~(MONST_FRIENDLY|MONST_PEACEFUL|
				         MONST_CUST_WHEN_ACTIVE);
				get_w()->m[monstid].flags |=
				    (MONST_ACTIVE|MONST_WANDER_WHEN_IDLE);
			}
		}
		else
		{
			message(gettext("The troll attacks!"));
			get_w()->m[monstid].flags &= ~(MONST_FRIENDLY|MONST_PEACEFUL|
			         MONST_CUST_WHEN_ACTIVE);
			get_w()->m[monstid].flags |=
			    (MONST_ACTIVE|MONST_WANDER_WHEN_IDLE);
		}
	}
}
//}}}
//{{{
void bridge_troll_die(int monstid)
{
	GFLAG(QUEST_TROLL) = QUEST_TROLL_KILLED;
}
//}}}

//{{{
void minion_horse_die(int monstid)
{
	get_w()->game_flags[HAVE_PET_HORSE] = 0;
}
//}}}

//{{{
int shk_anger(int monstid)
{
	int ii;
	
	get_w()->m[monstid].flags &= ~MONST_CUST_ANGER;
	monst_anger(monstid);
	
	// Anger all other shopkeepers on the level
	for(ii=0; ii<MONSTERS_MAX; ii++)
	{
		if(get_w()->m[ii].flags & MONST_SHOPKEEP)
			monst_anger(ii);
	}
	
	clear_shops();
	
	return 1;
}
//}}}
//{{{
void clear_shops(void)
{
	int ii;
	int jj;
	
	for(ii=0; ii<get_w()->items.alloced; ii++)
		get_w()->items.items[ii].flags &= ~ITEMFLAG_UNPAID;
	for(ii=0; ii<MAPSIZE_Y; ii++)
	for(jj=0; jj<MAPSIZE_X; jj++)
	{
		if(get_w()->t[ii][jj].type == TILE_SHOPFLOOR)
			get_w()->t[ii][jj].type = TILE_FLOOR;
	}
}
//}}}
//{{{
int spider_active(int monstid)
{
	// There's a player here, so cower in the web
	
	if(!monst_detect_player(monstid))
		get_w()->m[monstid].flags &= ~MONST_ACTIVE;
	if(monst_battle_pet(monstid))
		return 1;
	else if(monst_can_attack_player(monstid))
		monstmovetowardsplayer(monstid);
	else
		webspinner_cower(monstid, TILE_SPIDERWEB, TILE_WALL);
	
	return 1;
}
//}}}
//{{{
int spider_idle(int monstid)
{
	// The player's away, so build a web
	if(monst_detect_player(monstid))
		get_w()->m[monstid].flags |= MONST_ACTIVE;
	if(monst_battle_pet(monstid))
		return 1;
	else
		webspinner_build(monstid, TILE_SPIDERWEB, TILE_FLOOR);
	
	return 1;
}
//}}}
//{{{
int mimic_idle(int monstid)
{
	return 1;
}
//}}}
//{{{
int npc_chat(int monstid)
{
	if(!monst_detect_player(monstid))
		get_w()->m[monstid].flags &= ~MONST_ACTIVE;
	monst_chat(monstid);
	return 1;
}
//}}}

//{{{
void hit_rust(void)
{
	int i;
	for(i=0; i<PLRINVSIZE; i++)
	{
		if(!get_plr()->inventory[i].type ||
		   !(get_plr()->inventory[i].flags & ITEMFLAG_EQUIPPED))
			continue;
		if(random(5,1)!=1)
			continue;
		
		rust_inventory(i);
	}
}
//}}}
//{{{
void monst_summon(int monst, int type)
{
	int d[1]; // HACKHACK: Can't put a proper struct on the stack yet, but
	          // this is the same size so it works the same
	int x = get_w()->m[monst].x;
	int y = get_w()->m[monst].y;
	
	if(x > get_plr()->x) x--;
	else if(x < get_plr()->x) x++;
	if(y > get_plr()->y) y--;
	else if(y < get_plr()->y) y++;
	
	get_misc_link(type, d);
	addmonster(d, x, y);
}
//}}}
//{{{
void midpoint_summon(int monst, int type)
{
	int d[1]; // HACKHACK: Can't put a proper struct on the stack yet, but
	          // this is the same size so it works the same
	int x = (get_w()->m[monst].x + get_plr()->x) / 2;
	int y = (get_w()->m[monst].y + get_plr()->y) / 2;
	
	get_misc_link(type, d);
	addmonster(d, x, y);
}
//}}}
//{{{
int monster_ray(int monster, int target, int damage, int dist, char *event,
    char *hit, char *kill, int passthrough)
{
	int dx; int dy;
	int x = get_w()->m[monster].x;
	int y = get_w()->m[monster].y;
	int target_x; int target_y;
	int effect;
	
	if(target==-1) {
		target_x = get_plr()->x;
		target_y = get_plr()->y;
	} else {
		target_x = get_w()->m[target].x;
		target_y = get_w()->m[target].y;
	}

	if(x < target_x)           dx = 1;
	else if(x == target_x)     dx = 0;
	else                       dx = -1;
	
	if(y < target_y)           dy = 1;
	else if(y == target_y)     dy = 0;
	else                       dy = -1;
	
	if( ((target_x-x)*(target_x-x) + (target_y-y)*(target_y-y)) > dist*dist)
		return 0;
	
	effect = boltchar(dx, dy);
	
	message(event, monstname(monster));
	
	while(1)
	{
		x += dx;
		y += dy;
		
		if(attack_tile(x, y, hit, kill,
				damage))
		{
			UI_TF_DrawEffect(x, y, '*');
			if(!passthrough) {
				delay();
				break;
			}
		}
		else
			UI_TF_DrawEffect(x, y, effect);
		
		if(!tile_is_transparent(x, y))
			break;
		delay();
		dist--;
		if(dist<=0) break;
	}
	UI_TF_ClearEffects();
	
	return 1;
}
//}}}
//{{{
int have_clear_path(int monster, int target)
{
	int dx; int dy;
	int x = get_w()->m[monster].x;
	int y = get_w()->m[monster].y;
	int target_x; int target_y;
	int effect;
	
	if(target==-1) {
		target_x = get_plr()->x;
		target_y = get_plr()->y;
	} else {
		target_x = get_w()->m[target].x;
		target_y = get_w()->m[target].y;
	}

	if(x < target_x)           dx = 1;
	else if(x == target_x)     dx = 0;
	else                       dx = -1;
	
	if(y < target_y)           dy = 1;
	else if(y == target_y)     dy = 0;
	else                       dy = -1;
	
	while(1)
	{
		x += dx;
		y += dy;
		if(x == target_x && y == target_y)
			return 1;
		if(!tile_is_transparent(x, y))
			break;
		if(monstbytile(x, y) != -1)
			break;
	}
	return 0;
}
//}}}
//{{{
void poison_player(int strength)
{
	if(get_plr()->extrinsic[STAT_FLAGS] & STAT_FLAG_RESIST_POISON) {
		message(gettext("The poison doesn't seem to affect you."));
	} else if(random(strength, 1)>get_plr()->extrinsic[STAT_TOUGHNESS]
	          && random(1,0))
	{
		plr_mod_stat(STAT_STRENGTH, -random(2,1));
	}
}
//}}}
//{{{
void deal_monst_damage(int damage, int monster)
{
	plr_takedamage(damage,
	    retprintf(gettext("Killed by %s %s"),
	       indefinite_article(monstname(monster)),
	       monstname(monster)));
}
//}}}
//{{{
int do_attack(char *desc, int monst, int damage, int target)
{
	char *extstr = "";
	
	if(target==-1) {
		if(monst_facing(monst) == FACING_BEHIND)
			extstr = gettext(" attacks from behind and");
		message(gettext("The %s%s %s you!"), monstname(monst), extstr, desc);
		deal_monst_damage(damage, monst);
	} else {
		if(player_can_see(monst) && player_can_see(target))
			message(gettext("The %s %s the %s!"), monstname(monst),
			                             desc, monstname(target));
		else if(player_can_see(monst))
			message(gettext("The %s %s something."), monstname(monst), desc);
		else if(player_can_see(target))
			message(gettext("Something %s the %s"), desc, monstname(monst));
		else
			message(gettext("You hear the sound of combat."));
		
		monst_takedamage(target, damage, 0);
	}
	return 1;
}
//}}}

//{{{
int att_normal(int monst, int damage, int target)
{
	return do_attack(gettext("hits"), monst, damage, target);
}
//}}}
//{{{
int att_claw(int monst, int damage, int target)
{
	return do_attack(gettext("claws"), monst, damage, target);
}
//}}}
//{{{
int att_kick(int monst, int damage, int target)
{
	return do_attack(gettext("kicks"), monst, damage, target);
}
//}}}
//{{{
int att_disease_bite(int monst, int damage, int target)
{
	do_attack(gettext("bites"), monst, damage, target);
	
	if(target==-1)
	{
		if(random(15,1)==1) {
			message(gettext("Its bite was diseased."));
			plr_mod_stat(STAT_TOUGHNESS, -1);
		}
	}
	return 1;
}
//}}}
//{{{
int att_bite(int monst, int damage, int target)
{
	return do_attack(gettext("bites"), monst, damage, target);
}
//}}}
//{{{
int att_burn(int monst, int damage, int target)
{
	return do_attack(gettext("burns"), monst, damage, target);
}
//}}}
//{{{
int att_poison_bite(int monst, int damage, int target)
{
	do_attack(gettext("bites"), monst, damage, target);
	
	if(target==-1)
		poison_player(24);
	
	return 1;
}
//}}}
//{{{
int att_stealgold(int monst, int damage, int target)
{
	if(target != -1)
		att_normal(monst, damage, target);
	else if( !player_gold() )
		att_normal(monst, damage, target);
	else
	{
		do_attack(gettext("hits"), monst, damage, target);
		damage = random(75,25) + random(player_gold()/3, player_gold()/8);
		if(damage > player_gold())
			damage = player_gold();
		message(gettext("%li coins were stolen! The %s disappears!"), damage,
		    monstname(monst));
		debit_gold(damage);
		monst_remove(monst);
	}
	
	return 1;
}
//}}}
//{{{
int att_stealitem(int monst, int damage, int target)
{
	int whichitem;
	int retrycount = 0;
	
	if(target != -1) {
		att_normal(monst, damage, target);
	} else {
		do
		{
			whichitem = random(PLRINVSIZE-1, 0);
		} while(get_plr()->inventory[whichitem].type==0 && retrycount < 500);
		
		if(retrycount >= 500)
		{
			att_normal(monst, damage, target);
		}
		else
		{
			message(gettext("The %s steals your %s. The %s disappears!"),
				monstname(monst),
				n_itemname(whichitem),
				monstname(monst));
			
			get_plr()->inventory[whichitem].type = 0;
			update_player();
			
			monst_remove(monst);
		}
	}
	return 1;
}
//}}}
//{{{
int att_rust(int monst, int damage, int target)
{
	if(target != -1)
	{
		att_normal(monst, damage, target);
	}
	else
	{
		message(gettext("The %s hits!"), monstname(monst));
		hit_rust();
	}
	return 1;
}
//}}}
//{{{
int att_paral_only(int monst, int damage, int target)
{
	if(target == -1) {
		message(gettext("The %s freezes you!"), monstname(monst));
		paralyze(damage);
	} else {
		message(gettext("The %s is frozen!"), monstname(target));
		get_w()->m[target].flags |= MONST_PARALYZED;
	}
	return 1;
}
//}}}
//{{{
int att_poison_sting(int monst, int damage, int target)
{
	do_attack(gettext("stings"), monst, damage, target);
	
	if(target==-1)
		poison_player(24);
	
	return 1;
}
//}}}
//{{{
int att_bite_vampiric(int monst, int damage, int target)
{
	do_attack(gettext("bites"), monst, damage, target);
	
	if(target==-1 && !random(2,0))
	{
		message(gettext("You feel your life force draining away."));
		get_plr()->hps_max -= damage/3;
		get_plr()->hps_max_mod -= damage/3;
	}
	monst_heal(monst, damage);
	
	return 1;
}
//}}}

//{{{
int mspell_summon_skeleton(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 10 )
		return 0;
	get_w()->m[monster].power -= 10;
	
	message(gettext("The %s summons a skeleton!"), monstname(monster));
	monst_summon(monster, LINK_SKELETON);
	
	return 1;
}
//}}}
//{{{
int mspell_summon_fire_elemental(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 30 )
		return 0;
	get_w()->m[monster].power -= 30;
	
	message(gettext("The %s summons a fire elemental!"), monstname(monster));
	monst_summon(monster, LINK_FIRE_ELEMENTAL);
	
	return 1;
}
//}}}
//{{{
int mspell_magic_missile(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 6 )
		return 0;
	if( !have_clear_path(monster, target) )
		return 0;
	get_w()->m[monster].power -= 6;
	
	return monster_ray(monster, target, damage, 10,
		gettext("The %s casts magic missile!"),
	    gettext("The missile hit %s!"), gettext("Killed by a magic missile"), 0);
}
//}}}
//{{{
int mspell_fireball(int monster, int damage, int target)
{
	int dx; int dy;
	int x = get_w()->m[monster].x;
	int y = get_w()->m[monster].y;
	int target_x; int target_y;
	int effect;
	int xi; int yi;
	int dist= 10;
	
	if( !have_clear_path(monster, target) )
		return 0;
	
	if(target==-1) {
		target_x = get_plr()->x;
		target_y = get_plr()->y;
	} else {
		target_x = get_w()->m[target].x;
		target_y = get_w()->m[target].y;
	}

	if(x < target_x)           dx = 1;
	else if(x == target_x)     dx = 0;
	else                       dx = -1;
	
	if(y < target_y)           dy = 1;
	else if(y == target_y)     dy = 0;
	else                       dy = -1;
	
	if( ((target_x-x)*(target_x-x) + (target_y-y)*(target_y-y)) > dist*dist)
		return 0;
	
	effect = boltchar(dx, dy);
	
	message(gettext("The %s casts fireball!"), monstname(monster));
	
	while(1)
	{
		x += dx;
		y += dy;
		
		if(monstbytile(x,y) != -1)
			break;
		else if(get_plr()->x == x && get_plr()->y == y)
			break;
		else if(!tile_is_transparent(x, y))
			break;
		UI_TF_DrawEffect(x, y, effect);
		delay();
		dist--;
		if(dist<=0) break;
	}
	
	for(yi=y-1; yi<=y+1; yi++)
	for(xi=x-1; xi<=x+1; xi++)
		UI_TF_DrawEffect(xi, yi, '*');
	
	for(yi=y-1; yi<=y+1; yi++)
	for(xi=x-1; xi<=x+1; xi++)
		attack_tile(xi, yi, gettext("The flames burn %s!"), gettext("Killed by a fireball"), damage);
	
	delay();
	delay();
	UI_TF_ClearEffects();
	return 1;
}
//}}}
//{{{
int mspell_fire_mage_fireball(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 15 )
		return 0;
	get_w()->m[monster].power -= 15;
	
	mspell_fireball(monster, damage, target);
}
//}}}
//{{{
int att_dragon_breath(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 25 )
		return 0;
	get_w()->m[monster].power -= 25;
	
	return monster_ray(monster, target, damage, 10, gettext("The %s breathes fire!"),
	    gettext("The flames hit %s!"), gettext("Killed by a dragon's flame"), 1);
	
	return 1;

/*	int dx; int dy;
	int x = get_w()->m[monster].x;
	int y = get_w()->m[monster].y;
	int target_x; int target_y;
	int effect;
	int dist = 10;
	
	if(target==-1) {
		target_x = get_plr()->x;
		target_y = get_plr()->y;
	} else {
		target_x = get_w()->m[target].x;
		target_y = get_w()->m[target].y;
	}

	if(x < target_x)           dx = 1;
	else if(x == target_x)     dx = 0;
	else                                           dx = -1;
	
	if(y < target_y)           dy = 1;
	else if(y == target_y)     dy = 0;
	else                                           dy = -1;
	
	if( ((target_x-x)*(target_x-x) + (target_y-y)*(target_y-y)) > dist*dist)
		return 0;
	if( get_w()->m[monster].power < 25 )
		return 0;
	get_w()->m[monster].power -= 25;
	
	effect = boltchar(dx, dy);
	
	message(gettext("The %s breathes flame!"), monstname(monster));
	
	while(1)
	{
		x += dx;
		y += dy;
		
		if(attack_tile(x, y, gettext("The flames hit %s!"), gettext("Killed by dragon's flame"),
				damage))
			UI_TF_DrawEffect(x, y, '*');
		else
			UI_TF_DrawEffect(x, y, effect);
		
		if(!tile_is_transparent(x, y))
			break;
		delay();
		dist--;
		if(dist<=0) break;
	}
	UI_TF_ClearEffects();
	
	return 1;*/
}
//}}}
//{{{
int att_acid_spit(int monster, int damage, int target)
{
	int ret;
	
	if( get_w()->m[monster].power < 10 )
		return 0;
	get_w()->m[monster].power -= 10;
	
	ret = monster_ray(monster, target, damage, 10, gettext("The %s spits acid!"),
	    gettext("The acid hits %s!"), gettext("Killed by acid"), 0);
	if(ret) {
		if(target==-1) // Hit player
			hit_rust();
	}
	return ret;
}
//}}}

//{{{
int att_walk_into_grue(int monster, int damage, int target)
{
	struct monster *m = &get_w()->m[monster];
	
	if(get_w()->t[m->y][m->x].flags & TFLAG_LIT)
		return 0;
	if( m->power < 30 )
		return 0;
	m->power -= 30;
	
	message(gettext("Oh, no! You walked into the slavering fangs of a lurking grue!"));
		// TRANSLATORS: This is a quotation from Infocom
	plr_takedamage(damage,
	    retprintf(gettext("Eaten by %s %s"),
	       indefinite_article(monstname(monster)),
	       monstname(monster)));
	return 1;
}
//}}}
//{{{
int grue_active(int monster)
{
	int best_val = 5000;
	int best_x = get_w()->m[monster].x;
	int best_y = get_w()->m[monster].y;
	int xi; int yi;
	struct monster *m = &get_w()->m[monster];
	
	if(!monst_detect_player(monster))
		m->flags &= ~MONST_ACTIVE;
	if(monst_battle_pet(monster))
		return 1;
		
	if(monstcanmove(monster, get_plr()->x, get_plr()->y))
	{
		monstmovetowardsplayer(monster);
		return 1;
	}
	
	for(yi = m->y-1; yi <= m->y+1; yi++)
	for(xi = m->x-1; xi <= m->x+1; xi++)
	{
		if( monstcanmove( monster, xi, yi ) && // Legal move
			!(get_w()->t[yi][xi].flags & TFLAG_INTRINSIC_LIGHT) && // Dark
			distancesquare(xi, yi, get_plr()->x, get_plr()->y) < best_val )
		{
			best_val = distancesquare(xi, yi, get_plr()->x, get_plr()->y);
			best_x = xi;
			best_y = yi;
		}
	}
	
	monstmoveto(monster, best_x, best_y);
	return 1;
}
//}}}
//{{{
int grue_idle(int monster, int damage, int target)
{
	int x; int y;
	int mx = get_w()->m[monster].x;
	int my = get_w()->m[monster].y;
	int is_in_dark;
	
	if(get_w()->t[my][mx].flags & TFLAG_LIT) {
		if(get_plr()->extrinsic[STAT_LIGHTRADIUS] > 20)
			message(gettext("You are engulfed in darkness."));
		else
			message(gettext("You are engulfed in impenetrable darkness."));
		engulf_in_darkness(20);
		get_w()->m[monster].flags |= MONST_ACTIVE;
		return grue_active(monster);
	}
	if(get_w()->t[my][mx].flags & TFLAG_INTRINSIC_LIGHT) {
		is_in_dark = 0;
	} else {
		is_in_dark = 1;
	}
	if(monst_battle_pet(monster))
		return 1;
	
	do
	{
		x = mx + random(2, 0) - 1;
		y = my + random(2, 0) - 1;
	} while( !monstcanmove(monster, x, y) );
	
	if(get_w()->t[y][x].flags & TFLAG_INTRINSIC_LIGHT && is_in_dark)
		return 1;
	monstmoveto(monster, x, y);
	return 1;
}
//}}}

//{{{
int vortex_throw(int monstid, int target)
{
	int dx; int dy;
	int x; int y; int m; int tiletype;
	int target_x; int target_y;
	int damage;
	
	if(target==-1) {
		target_x = get_plr()->x;
		target_y = get_plr()->y;
	} else {
		target_x = get_w()->m[target].x;
		target_y = get_w()->m[target].y;
	}
	x = get_w()->m[monstid].x;
	y = get_w()->m[monstid].y;
	if(x < target_x)           dx = 1;
	else if(x == target_x)     dx = 0;
	else                       dx = -1;
	if(y < target_y)           dy = 1;
	else if(y == target_y)     dy = 0;
	else                       dy = -1;
	
	x = target_x + dx;
	y = target_y + dy;
	m = monstbytile(x, y);
	
	if(m != -1) {
		if(target==-1)
			message(gettext("A strong wind throws you into the %s!"), monstname(m));
		else // Monsters don't get thrown into eachother
			return 0;
	}
	else if(tile_is_passable(x, y)) {
		if(target==-1) {
			message(gettext("You are thrown back by a strong wind."));
			plr_moveto(x, y, -1);
		} else if(random(2,1)==1) {
			monstmoveto(target, x, y);
		}
	}
	else {
		if(target == -1)
		{
			tiletype = get_w()->t[y][x].type;
			damage = random(20,10);
			if(tiletype == TILE_CDOOR || tiletype==TILE_LDOOR) {
				message(gettext("You are thrown into the door by a strong wind."));
				plr_takedamage(damage, gettext("Crashed into a door."));
			} else if(tiletype==TILE_HORIZ_FENCE || tiletype==TILE_VERT_FENCE) {
				message(gettext("You are thrown into the fence by a strong wind."));
				plr_takedamage(damage, gettext("Impaled on a fence."));
			} else if(tiletype==TILE_TREE) {
				message(gettext("You are thrown into the tree by a strong wind."));
				plr_takedamage(damage, gettext("Fell onto a tree."));
			} else {
				message(gettext("You are thrown into the wall by a strong wind."));
				plr_takedamage(damage, gettext("Hit a wall."));
			}
		}
		else
		{ // Monsters don't get thrown into walls
			return 0;
		}
	}
	
	return 1;
}
//}}}
//{{{
int vortex_active(int monstid)
{
	int xi; int yi;
	int x; int y;
	
	if(!monst_detect_player(monstid))
		get_w()->m[monstid].flags &= ~MONST_ACTIVE;
	
	x = get_w()->m[monstid].x;
	y = get_w()->m[monstid].y;
	for(yi=y-1; yi<=y+1; yi++)
	for(xi=x-1; xi<=x+1; xi++)
	{
		if(xi==x && yi==y)
			continue;
		if(monstbytile(xi, yi) >= 0)
			vortex_throw(monstid, monstbytile(xi, yi));
		if(xi==get_plr()->x && yi==get_plr()->y)
		{
			if((get_plr()->extrinsic[STAT_FLAGS] & STAT_FLAG_SLIPPERY) ||
				get_plr()->extrinsic[STAT_STRENGTH]
				+ get_plr()->extrinsic[STAT_DEXTERITY]
				+ get_plr()->extrinsic[STAT_WILLPOWER] < random(10, 60)
			  )
				vortex_throw(monstid, -1);
			else
				message(gettext("You struggle to retain your balance in the wind."));
		}
	}
	
	if(monst_battle_pet(monstid))
		return 1;
	
	monstmovetowardsplayer(monstid);
	
	return 1;
}
//}}}
//{{{
int att_vortex_debris(int monst, int damage, int target)
{
	if(target==-1) {
		message(gettext("You are hit by flying debris!"));
		deal_monst_damage(damage, monst);
	} else {
		if(player_can_see(target))
			message(gettext("The %s is hit by flying debris!"), monstname(target));
		monst_takedamage(target, damage, 0);
	}
	return 1;
}
//}}}

//{{{
int mspell_summon_vortex(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 30 )
		return 0;
	get_w()->m[monster].power -= 30;
	
	message(gettext("The %s summons a vortex!"), monstname(monster));
	monst_summon(monster, LINK_VORTEX);
	
	return 1;
}
//}}}
//{{{
int mspell_windblast(int caster, int damage, int target)
{
	int x; int y; int target_x; int target_y; int dx; int dy;
	int tiletype; int m;
	int dist = random(8,4);
	
	if(caster==-1) {
		x = get_plr()->x;
		y = get_plr()->y;
	} else {
		x = get_w()->m[caster].x;
		y = get_w()->m[caster].y;
	}
	if(target==-1) {
		target_x = get_plr()->x;
		target_y = get_plr()->y;
	} else {
		target_x = get_w()->m[target].x;
		target_y = get_w()->m[target].y;
	}
	if(x < target_x)           dx = 1;
	else if(x == target_x)     dx = 0;
	else                       dx = -1;
	if(y < target_y)           dy = 1;
	else if(y == target_y)     dy = 0;
	else                       dy = -1;
	
	if(target == -1)
		message(gettext("You are sent flying by a powerful blast of wind!"));
	else if(player_can_see(target))
		message(gettext("The %s is sent flying by a powerful blast of wind!"),
			monstname(target));
	
	do
	{
		if(target==-1)
			UI_TF_DrawEffect(target_x, target_y, '*');
		target_x += dx;
		target_y += dy;
		if(target==-1) {
			UI_TF_DrawEffect(target_x, target_y, '@');
			delay();
		}
		dist--;
		tiletype = get_w()->t[target_y][target_x].type;
		m = monstbytile(target_x, target_y);
		if(m != -1) {
			if(target==-1) {
				message(gettext("You crash into the %s!"), monstname(m));
				plr_takedamage(random(14, 8), retprintf(gettext("Crashed into %s %s"),
					indefinite_article(monstname(m)), monstname(m)));
				monst_takedamage(m, random(8, 4), 1);
			} else {
				monst_takedamage(target, random(14, 8), 0);
				monst_takedamage(m, random(8, 4), 0);
			}
			break;
		}
		else if(!tile_is_passable(target_x, target_y))
		{
			if(target==-1)
			{
				if(tiletype == TILE_TREE) {
					if(random(2,1)==1)
						message(gettext("You land in a tree! You climb down."));
					else {
						message(gettext("You hit a tree! You fall out."));
						plr_takedamage(random(8, 6), gettext("Fell out of a tree"));
					}
				} else if( get_w()->tiledescs[
					get_w()->t[target_y][target_x].type].is_connection )
				{
				} else {
					message(gettext("You hit a wall!"));
					plr_takedamage(random(14, 8), gettext("Hit a wall"));
				}
			} else {
				if(tiletype == TILE_AIRFALL) {
					message(gettext("The %s falls."), monstname(target));
					monst_takedamage(target, 150, 0);
				} else {
					monst_takedamage(target, random(10, 6), 0);
				}
			}
			break;
		}
		else if(tiletype == TILE_SPIDERWEB)
		{
			if(target==-1)
				message(gettext("You land in a spider web!"));
			target_x += dx;
			target_y += dy;
			break;
		}
		if(dist <= 0)
		{
			if(target==-1) {
				if(random(20,1) > get_plr()->extrinsic[STAT_DEXTERITY]) {
					message(gettext("You land badly!"));
					plr_takedamage(random(14, 8), gettext("Broke his neck"));
				}
			} else {
				monst_takedamage(target, random(8, 4), 0);
			}
			break;
		}
	} while(1);
	
	if(target==-1) {
		UI_TF_ClearEffects();
		plr_moveto(target_x-dx, target_y-dy, -1);
	} else
		monstmoveto(target, target_x-dx, target_y-dy);
	
	if(target==-1) {
		plr_step(target_x, target_y);
	}
	
	return 1;
}
//}}}
//{{{
int mspell_wind_mage_windblast(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 10 )
		return 0;
	get_w()->m[monster].power -= 10;
	
	return mspell_windblast(monster, damage, target);
}
//}}}

//{{{
int mspell_lich_melee(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 3 )
		return 0;
	get_w()->m[monster].power -= 3;
	
	return mspell_windblast(monster, random(7,12), target);
}
//}}}
//{{{
int mspell_lich_range(int monster, int damage, int target)
{
	if( get_w()->m[monster].power < 4 )
		return 0;
	get_w()->m[monster].power -= 4;
	
	return mspell_fireball(monster, damage, target);
}
//}}}
//{{{
int mspell_lich_see(int monster, int damage, int target)
{
	int ii;
	
	if( get_w()->m[monster].power < 5 )
		return 0;
	get_w()->m[monster].power -= 5;
	
	message("The lich summons zombies!");
	for(ii=0; ii<3; ii++)
		midpoint_summon(monster, LINK_ZOMBIE);
	return 1;
}
//}}}
//{{{
void lich_die(int monstid)
{
	monst_drop_item(monstid, ITEM_LIBRARY_KEY, 1);
}
//}}}

