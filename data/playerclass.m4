m4_define(numPlayerClasses, -1) // Hack: One less to hide the tutorial class

m4_define(CLASS,
 {@m4_divert(SEQUENCE_STRINGS)
  export CLASSNAME_{@@}$1;
  string: $2;
  m4_divert(SEQUENCE_TABLES)
  link: CLASSNAME_{@@}$1;
  // Base stats
  uint: $3;  // St
  uint: $4;  // Dx
  uint: $5;  // To
  uint: $6;  // Ma
  uint: $7;  // Wi
  // Max stats
  uint: $8;  // St
  uint: $9;  // Dx
  uint: $10; // To
  uint: $11; // Ma
  uint: $12; // Wi
  
  uint: $13; // Free points
  uint: $14; // Spellcasting (arcane)
  uint: $15; // Spellcasting (divine)
  uint: $16; // Spellcasting (necromancy)
  uint: $17; // Weapon skill advancement factor (higher is slower)
  uint: $18; // Weapon starting skill
  m4_define({@numPlayerClasses@}, m4_eval(numPlayerClasses+1))
  m4_define(CLASS_{@@}$1, numPlayerClasses)
 @})

m4_divert(SEQUENCE_TABLES)
splitpoint; export PLAYERCLASSES;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                             Base                  Max                                                     //
//                 Name                    St  Dx  To  Ma  Wi    St  Dx  To  Ma  Wi   Free   Spell  Prayer Necro Weap Skill  //
CLASS(FIGHTER,     gettext("Fighter"),     16, 9,  12, 4,  8,    18, 13, 18, 9,  12,  13,    0,     6,     0,    15,  2       )
CLASS(WIZARD,      gettext("Wizard"),      9,  9,  9,  15, 9,    13, 15, 12, 18, 16,  9,     20,    0,     0,    30,  0       )
CLASS(ARCHER,      gettext("Archer"),      12, 14, 9,  6,  10,   15, 18, 13, 10, 14,  10,    6,     0,     0,    20,  0       )
CLASS(PRIEST,      gettext("Priest"),      10, 7,  9,  11, 14,   14, 15, 13, 15, 18,  11,    0,     20,    0,    20,  0       )
CLASS(NECROMANCER, gettext("Necromancer"), 9,  9,  9,  15, 9,    13, 15, 12, 18, 16,  9,     0,     0,     20,   30,  0       )
CLASS(TUTORIAL,    gettext("Student"),     16, 16, 16, 16, 16,   16, 16, 16, 16, 16,  0,     100,   100,   100,  9,   2       )
CLASS(KNIGHT,      gettext("Knight"),      16, 9,  12, 4,  8,    18, 13, 18, 9,  12,  13,    0,     10,    0,    15,  2       )
CLASS(LICH,        gettext("Lich"),        9,  9,  9,  19, 9,    13, 15, 12, 22, 16,  9,     0,     0,     20,   30,  0       )

