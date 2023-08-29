//{{{
/*
 * NOTE
 *    This file uses folding extensively, and is *extremely* awkward to edit
 * without it. You should set your editor so that {{{ and }}} mark the beginning
 * and end of a fold, and a fold is shown as the first non-comment line inside.
 *
 * Also, tab size is assumed to be four spaces, and line wrapping off. Other
 * tab sizes should work, though.
 *
 * If you are using ViM, add the following lines to your vimrc to get folding
 * as specified above:
 *
	" Folding
	function GetFirstLineWithChars()
		let line_num = 0
		let charline = matchstr(getline(v:foldstart), '[^/]*')
		while strlen(charline) == 0
			let line_num = line_num + 1
			let charline = matchstr(getline(v:foldstart + line_num), '[^/]*')
		endw
		return substitute(substitute(charline,'	','    ','g'),'    ','   ','')
	endfunction
	set foldtext='+'.GetFirstLineWithChars()
	set fillchars=fold:\ 
	set foldmethod=marker
	set foldopen=block,quickfix,search
 */
//}}}

#include "items.m4h"

//{{{ GENERATEITEM
BEGIN_JUMPTAB(GENERATEITEM, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_GOLD_PIECE,         180,  range(255,1))
  JTENTRY(GENERATE_ARMOR,           130,  range(255,1))
  JTENTRY(GENERATE_WEAPON,          100,  range(255,1))
  JTENTRY(GENERATE_POTION,          120,  range(255,1))
  JTENTRY(GENERATE_SCROLL,          100,  range(255,1))
  JTENTRY(GENERATE_FOOD,             70,  range(255,1))
  JTENTRY(GENERATE_AMMO,             60,  range(255,1))
  JTENTRY(GENERATE_BOOK,             40,  range(255,1))
  JTENTRY(GENERATE_WAND,             60,  range(255,1))
  JTENTRY(GENERATE_VALUABLE_GEM,     30,  range(255,1))
  JTENTRY(GENERATE_WORTHLESS_GEM,    20,  range(255,1))
  JTENTRY(GENERATE_RING,             45,  range(255,1))
  JTENTRY(GENERATE_AMULET,           10,  range(255,1))
  JTENTRY(GENERATE_TOOL,             35,  range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_WAND
BEGIN_JUMPTAB(GENERATE_WAND, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_WAND_NOTHING,       1,    range(255,1))
  JTENTRY(ITYPE_WAND_LIGHT,         2,    range(255,1))
  JTENTRY(ITYPE_WAND_DETECT,        2,    range(255,1))
  JTENTRY(ITYPE_WAND_DIGGING,       2,    range(255,1))
  JTENTRY(ITYPE_WAND_STRIKING,      3,    range(255,1))
  JTENTRY(ITYPE_WAND_LIGHTNING,     2,    range(255,1))
  JTENTRY(ITYPE_WAND_FIRE,          2,    range(255,1))
  JTENTRY(ITYPE_WAND_TELEPORTATION, 1,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_POTION
BEGIN_JUMPTAB(GENERATE_POTION, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_POTION_HEAL,        7,    range(255,1))
  JTENTRY(ITYPE_POTION_EXTRAHEAL,   4,    range(255,1))
  JTENTRY(ITYPE_POTION_FULLHEAL,    3,    range(255,1))
  JTENTRY(ITYPE_POTION_SICKNESS,    3,    range(255,1))
  JTENTRY(ITYPE_POTION_HALLU,       3,    range(255,1))
  JTENTRY(ITYPE_POTION_CONF,        3,    range(255,1))
  JTENTRY(ITYPE_POTION_OBJDETECT,   4,    range(255,1))
  JTENTRY(ITYPE_POTION_NUMBNESS,    2,    range(255,1))
  JTENTRY(ITYPE_POTION_GAINST,      1,    range(255,1))
  JTENTRY(ITYPE_POTION_GAINDX,      1,    range(255,1))
  JTENTRY(ITYPE_POTION_GAINTO,      1,    range(255,1))
  JTENTRY(ITYPE_POTION_GAINMN,      1,    range(255,1))
  JTENTRY(ITYPE_POTION_GAINWI,      1,    range(255,1))
  JTENTRY(ITYPE_POTION_RESTORE,     5,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_SCROLL
BEGIN_JUMPTAB(GENERATE_SCROLL, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_SCROLL_BLANK,       1,    range(255,1))
  JTENTRY(ITYPE_SCROLL_MAGICMAP,    2,    range(255,1))
  JTENTRY(ITYPE_SCROLL_TELEPORT,    4,    range(255,1))
  JTENTRY(ITYPE_SCROLL_IDENTIFY,    5,    range(255,1))
  JTENTRY(ITYPE_SCROLL_UNCURSE,     4,    range(255,1))
  JTENTRY(ITYPE_SCROLL_CREATEMONST, 2,    range(255,1))
  JTENTRY(ITYPE_SCROLL_ENCHANTING,  3,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_FOOD
BEGIN_JUMPTAB(GENERATE_FOOD, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_FOOD_RATION,        1,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_VALUABLE_GEM
BEGIN_JUMPTAB(GENERATE_VALUABLE_GEM, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_GEM_DIAMOND,        1,    range(255,19))
  JTENTRY(ITYPE_GEM_RUBY,           1,    range(255,18))
  JTENTRY(ITYPE_GEM_JACINTH,        1,    range(255,17))
  JTENTRY(ITYPE_GEM_SAPPHIRE,       1,    range(255,16))
  JTENTRY(ITYPE_GEM_BLACKOPAL,      1,    range(255,15))
  JTENTRY(ITYPE_GEM_EMERALD,        1,    range(255,14))
  JTENTRY(ITYPE_GEM_TURQUOISE,      1,    range(255,13))
  JTENTRY(ITYPE_GEM_AQUAMARINE,     1,    range(255,12))
  JTENTRY(ITYPE_GEM_CITRINE,        1,    range(255,11))
  JTENTRY(ITYPE_GEM_AMBER,          1,    range(255,10))
  JTENTRY(ITYPE_GEM_TOPAZ,          1,    range(255,9))
  JTENTRY(ITYPE_GEM_JET,            1,    range(255,8))
  JTENTRY(ITYPE_GEM_OPAL,           1,    range(255,7))
  JTENTRY(ITYPE_GEM_CHRYSOBERYL,    1,    range(255,6))
  JTENTRY(ITYPE_GEM_GARNET,         1,    range(255,5))
  JTENTRY(ITYPE_GEM_AMETHYST,       1,    range(255,4))
  JTENTRY(ITYPE_GEM_JASPER,         1,    range(255,3))
  JTENTRY(ITYPE_GEM_FLUORITE,       1,    range(255,2))
  JTENTRY(ITYPE_GEM_JADE,           1,    range(255,1))
  JTENTRY(ITYPE_GEM_AGATE,          1,    range(255,1))
  JTENTRY(ITYPE_GEM_OBSIDIAN,       1,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_WORTHLESS_GEM
BEGIN_JUMPTAB(GENERATE_WORTHLESS_GEM, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_GEM_WHITEGLASS,     1,    range(255,1))
  JTENTRY(ITYPE_GEM_REDGLASS,       1,    range(255,1))
  JTENTRY(ITYPE_GEM_ORANGEGLASS,    1,    range(255,1))
  JTENTRY(ITYPE_GEM_BLUEGLASS,      1,    range(255,1))
  JTENTRY(ITYPE_GEM_BLACKGLASS,     1,    range(255,1))
  JTENTRY(ITYPE_GEM_GREENGLASS,     1,    range(255,1))
  JTENTRY(ITYPE_GEM_YELLOWGLASS,    1,    range(255,1))
  JTENTRY(ITYPE_GEM_VIOLETGLASS,    1,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_WEAPON
BEGIN_JUMPTAB(GENERATE_WEAPON, jt_dungeonlevel)
//        Item                         Freq  Level range
  JTENTRY(ITYPE_WEAPON_BOW,            4,    range(255,1))
  JTENTRY(ITYPE_WEAPON_CROSSBOW,       3,    range(255,1))
  JTENTRY(ITYPE_WEAPON_CLUB,           2,    range(255,1))
  JTENTRY(ITYPE_WEAPON_DAGGER,         2,    range(255,1))
  JTENTRY(ITYPE_WEAPON_STAFF,          3,    range(255,1))
  JTENTRY(ITYPE_WEAPON_MACE,           3,    range(255,1))
  JTENTRY(ITYPE_WEAPON_AXE,            2,    range(255,1))
  JTENTRY(ITYPE_WEAPON_SWORD,          2,    range(255,1))

  JTENTRY(ITYPE_WEAPON_BOW_ACCURACY,   4,    range(255,5))
  JTENTRY(ITYPE_WEAPON_CROSSBOW_FORCE, 4,    range(255,5))
  JTENTRY(ITYPE_WEAPON_CRYSTAL_DAGGER, 3,    range(255,5))
  JTENTRY(ITYPE_WEAPON_SILVERDAGGER,   4,    range(255,5))
  JTENTRY(ITYPE_WEAPON_SILVERSTAFF,    4,    range(255,5))
  JTENTRY(ITYPE_WEAPON_SILVERMACE,     4,    range(255,5))
  JTENTRY(ITYPE_WEAPON_SILVERAXE,      4,    range(255,6))
  JTENTRY(ITYPE_WEAPON_SILVERSWORD,    4,    range(255,6))

END_JUMPTAB()
//}}}
//{{{ GENERATE_AMMO
BEGIN_JUMPTAB(GENERATE_AMMO, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_AMMO_ARROW,         3,    range(255,1))
  JTENTRY(ITYPE_AMMO_BOLT,          2,    range(255,1))
  JTENTRY(ITYPE_AMMO_SILVERARROW,   8,    range(255,5))
  JTENTRY(ITYPE_AMMO_SILVERBOLT,    6,    range(255,5))
END_JUMPTAB()
//}}}
//{{{ GENERATE_ARMOR
BEGIN_JUMPTAB(GENERATE_ARMOR, jt_dungeonlevel)
//        Item                        Freq  Level range
  JTENTRY(ITYPE_ARMR_LEATHER,         24,   range(255,1))
  JTENTRY(ITYPE_ARMR_CHAIN,           12,   range(255,1))
  JTENTRY(ITYPE_ARMR_RING,            12,   range(255,2))
  JTENTRY(ITYPE_ARMR_PLATE,           6,    range(255,3))
  JTENTRY(ITYPE_ARMR_CLOAK,           15,   range(255,1))
  JTENTRY(ITYPE_ARMR_CAP,             15,   range(255,1))
  JTENTRY(ITYPE_ARMR_IRONHELM,        9,    range(255,1))
  JTENTRY(ITYPE_ARMR_SMSHIELD,        18,   range(255,1))
  JTENTRY(ITYPE_ARMR_MDSHIELD,        12,   range(255,1))
  JTENTRY(ITYPE_ARMR_LGSHIELD,        6,    range(255,1))
  JTENTRY(ITYPE_ARMR_GLOVES,          15,   range(255,1))
  JTENTRY(ITYPE_ARMR_GAUNTLETS,       6,    range(255,1))
  JTENTRY(ITYPE_ARMR_BOOTS,           15,   range(255,1))
  JTENTRY(ITYPE_ARMR_SPEEDBOOTS,      2,    range(255,5))
  JTENTRY(ITYPE_ARMR_BOOTS_ICE,       3,    range(255,1))
  JTENTRY(ITYPE_ARMR_GAUNTLETS_POWER, 6,    range(255,6))
  JTENTRY(ITYPE_ARMR_HELM_SEEING,     2,    range(255,1))
  JTENTRY(ITYPE_ARMR_HELM_DELUSION,   2,    range(255,1))
  JTENTRY(ITYPE_ARMR_CLOAK_INVULN,    3,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_RING
BEGIN_JUMPTAB(GENERATE_RING, jt_dungeonlevel)
//        Item                      Freq  Level range
  JTENTRY(ITYPE_RING_PLAIN,         2,    range(255,1))
  JTENTRY(ITYPE_RING_STRENGTH,      1,    range(255,1))
  JTENTRY(ITYPE_RING_DEXTERITY,     1,    range(255,1))
  JTENTRY(ITYPE_RING_TOUGHNESS,     1,    range(255,1))
  JTENTRY(ITYPE_RING_WILLPOWER,     1,    range(255,1))
  JTENTRY(ITYPE_RING_MANA,          1,    range(255,1))
  JTENTRY(ITYPE_RING_PROTECTION,    1,    range(255,1))
  JTENTRY(ITYPE_RING_ILLUMINATION,  2,    range(255,1))
  JTENTRY(ITYPE_RING_DAMAGE,        1,    range(255,1))
  JTENTRY(ITYPE_RING_DETECTINVIS,   1,    range(255,1))
  JTENTRY(ITYPE_RING_RESIST_POISON, 1,    range(255,1))
  JTENTRY(ITYPE_RING_HUNGER,        1,    range(255,1))
  JTENTRY(ITYPE_RING_TELEPORTATION, 1,    range(255,1))
  JTENTRY(ITYPE_RING_TIMEDILATION,  1,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_AMULET
BEGIN_JUMPTAB(GENERATE_AMULET, jt_dungeonlevel)
  JTENTRY(ITYPE_AMULET_SLOWDIGESTION, 1,    range(255,1))
  JTENTRY(ITYPE_AMULET_BRILLIANCE,    1,    range(255,1))
  JTENTRY(ITYPE_AMULET_SPEED,         1,    range(255,1))
  JTENTRY(ITYPE_AMULET_REGENERATION,  1,    range(255,1))
  JTENTRY(ITYPE_AMULET_TELEKINESIS,   1,    range(255,1))
END_JUMPTAB()
//}}}
//{{{ GENERATE_TOOL
BEGIN_JUMPTAB(GENERATE_TOOL, jt_dungeonlevel)
  JTENTRY(ITYPE_TOOL_TORCH,           30,   range(255,1))
  JTENTRY(ITYPE_TOOL_LANTERN,         10,   range(255,1))
  JTENTRY(ITYPE_RATTLESNAKE_TOOTH,    2,    range(255,1))
  JTENTRY(ITYPE_TOOL_HOLYSYMBOL,      1,    range(255,1))
END_JUMPTAB()
//}}}

m4_define(numItems, 0)
m4_divert(SEQUENCE_ITEMS)
even;
export ITEMSTABLE;

//{{{ WORKAROUND
BEGIN_SHUFFLETAB(WORKAROUND)
	// First entry in the table looks like NULL. Workaround until it's fixed.
  STENTRYSTRING("")
END_SHUFFLETAB()
//}}}
//{{{ WANDNAMES
BEGIN_SHUFFLETAB(WANDNAMES)
  STENTRYITEM(WHITE,    gettext("short wand"))
  STENTRYITEM(WHITE,    gettext("long wand"))
  STENTRYITEM(WHITE,    gettext("metal wand"))
  STENTRYITEM(LWHITE,   gettext("glass wand"))
  STENTRYITEM(YELLOW,   gettext("copper wand"))
  STENTRYITEM(LCYAN,    gettext("crystal wand"))
  STENTRYITEM(LWHITE,   gettext("silver wand"))
  STENTRYITEM(YELLOW,   gettext("curved wand"))
  STENTRYITEM(WHITE,    gettext("iron wand"))
  STENTRYITEM(YELLOW,   gettext("maple wand"))
END_SHUFFLETAB()
//}}}
//{{{ POTIONNAMES
BEGIN_SHUFFLETAB(POTIONNAMES)
  STENTRYITEM(LGREEN,   gettext("green potion"))
  STENTRYITEM(LWHITE,   gettext("white potion"))
  STENTRYITEM(LYELLOW,  gettext("glowing potion"))
  STENTRYITEM(YELLOW,   gettext("brown potion"))
  STENTRYITEM(LYELLOW,  gettext("yellow potion"))
  STENTRYITEM(WHITE,    gettext("smoky potion"))
  STENTRYITEM(WHITE,    gettext("cloudy potion"))
  STENTRYITEM(WHITE,    gettext("thick potion"))
  STENTRYITEM(WHITE,    gettext("swirly potion"))
  STENTRYITEM(LBLACK,   gettext("black potion"))
  STENTRYITEM(LBLUE,    gettext("blue potion"))
  STENTRYITEM(LRED,     gettext("orange potion"))
  STENTRYITEM(WHITE,    gettext("gray potion"))
  STENTRYITEM(GREEN,    gettext("murky potion"))
END_SHUFFLETAB()
//}}}
//{{{ SCROLLNAMES
BEGIN_SHUFFLETAB(SCROLLNAMES)
  STENTRYITEM(LWHITE,   gettext("crumpled scroll"))
  STENTRYITEM(LWHITE,   gettext("scribbled scroll"))
  STENTRYITEM(LWHITE,   gettext("shimmering scroll"))
  STENTRYITEM(LWHITE,   gettext("stained scroll"))
  STENTRYITEM(LWHITE,   gettext("glowing scroll"))
  STENTRYITEM(LWHITE,   gettext("yellowed scroll"))
END_SHUFFLETAB()
//}}}
//{{{ RINGNAMES
BEGIN_SHUFFLETAB(RINGNAMES)
  STENTRYITEM(WHITE,    gettext("stone ring"))
  STENTRYITEM(WHITE,    gettext("iron ring"))
  STENTRYITEM(YELLOW,   gettext("wooden ring"))
  STENTRYITEM(LRED,     gettext("ruby ring"))
  STENTRYITEM(LBLUE,    gettext("sapphire ring"))
  STENTRYITEM(LWHITE,   gettext("silver ring"))
  STENTRYITEM(LYELLOW,  gettext("gold ring"))
  STENTRYITEM(LWHITE,   gettext("platinum ring"))
  STENTRYITEM(LWHITE,   gettext("diamond ring"))
  STENTRYITEM(WHITE,    gettext("steel ring"))
  STENTRYITEM(LWHITE,   gettext("glass ring"))
  STENTRYITEM(LGREEN,   gettext("emerald ring"))
  STENTRYITEM(BLUE,     gettext("jet ring"))
END_SHUFFLETAB()
//}}}
//{{{ AMULETNAMES
BEGIN_SHUFFLETAB(AMULETNAMES)
  STENTRYITEM(LWHITE,   gettext("shiny amulet"))
  STENTRYITEM(LWHITE,   gettext("dull amulet"))
  STENTRYITEM(LWHITE,   gettext("square amulet"))
  STENTRYITEM(LWHITE,   gettext("spherical amulet"))
  STENTRYITEM(LWHITE,   gettext("triangular amulet"))
END_SHUFFLETAB()
//}}}

//////////////////////////////////////////////////////////////////////
//      C   Identifier               Color                          //
//    Name                                                          //
//    UnID Name                                                     //
//    Flags                 Stack  Weight Value   Category    Slot  //
//{{{
ITEM( '0',  NONE0,                   LYELLOW,
      NULL,
      NULL,
      1,                    2,     1,     0,      0,          -1,  
	0,
	{@
	@})
//}}}
//{{{
ITEM( '$',  GOLD_PIECE,              LYELLOW,
      {@String(gettext("gold piece"))@},
      NULL,
      FLAGS_GOLD,           100,   0,     1,      CAT_MONEY,  -1,
	1,
	{@SCORE(4)
	@})
//}}}
//{{{
ITEM( ']',  LIBRARY_KEY,             LYELLOW,
      {@String(gettext("gold key"))@},
      NULL,
      FLAGS_KEY,            100,   0,     1,      CAT_TOOL,   -1,
	1,
	{@USEEFFECT(use_key)
	@})
//}}}
//{{{
ITEM( '\"', AMULET_YENDOR,          LYELLOW,
      {@String(gettext("Amulet of Yendor"))@},
      NULL,
      FLAGS_AMULET,         1,     20,    50000,  CAT_AMULET, -1,
	3,
	{@CARRIED_STAT_OR(STAT_FLAGS, STAT_FLAG_DRAIN)
	  SCORE(5)
	  CARRIED_STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_AM_YENDOR)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '\'', RATTLESNAKE_TOOTH,       0,
      {@String(gettext("rattlesnake tooth"))@},
      NULL,
      FLAGS_TOOTH,          1,     4,     2,      CAT_TOOL,   -1,
	1,
	{@CARRIED_STAT_OR(STAT_COMPONENTS,STAT_COMPONENT_SNAKETOOTH)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '/',  WAND_NOTHING,            0,
      {@String(gettext("wand of nothing"))@},
      WANDNAMES_1,
      FLAGS_WAND,           0,     4,     30,     CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_nothing)
	@})
//}}}
//{{{
ITEM( '/',  WAND_STRIKING,           0,
      {@String(gettext("wand of striking"))@},
      WANDNAMES_2,
      FLAGS_WAND,           15,    4,     75,     CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_striking)
	@})
//}}}
//{{{
ITEM( '/',  WAND_DIGGING,            0,
      {@String(gettext("wand of digging"))@},
      WANDNAMES_3,
      FLAGS_WAND,           15,    4,     150,    CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_digging)
	@})
//}}}
//{{{
ITEM( '/',  WAND_LIGHT,              0,
      {@String(gettext("wand of light"))@},
      WANDNAMES_4,
      FLAGS_WAND,           40,    4,     75,     CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_light)
	@})
//}}}
//{{{
ITEM( '/',  WAND_DETECT,             0,
      {@String(gettext("wand of detection"))@},
      WANDNAMES_5,
      FLAGS_WAND,           20,    4,     100,    CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_detect)
	@})
//}}}
//{{{
ITEM( '/',  WAND_LIGHTNING,          0,
      {@String(gettext("wand of lightning"))@},
      WANDNAMES_6,
      FLAGS_WAND,           15,    4,     150,    CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_lightning)
	@})
//}}}
//{{{
ITEM( '/',  WAND_FIRE,               0,
      {@String(gettext("wand of fire"))@},
      WANDNAMES_7,
      FLAGS_WAND,           12,    4,     200,    CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_fire)
	@})
//}}}
//{{{
ITEM( '/',  WAND_TELEPORTATION,      0,
      {@String(gettext("wand of teleportation"))@},
      WANDNAMES_8,
      FLAGS_WAND,           10,    4,     200,    CAT_WAND,   -1,
	1,
	{@USEEFFECT(wand_teleportation)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '!',  POTION_BOTTLE,           0,
      {@String(gettext("empty bottle"))@},
      NULL,
      FLAGS_POTION,         1,     2,     3,      CAT_POTN,   -1,  
	1,
	{@USEEFFECT(potion_empty)
	@})
//}}}
//{{{
ITEM( '!',  POTION_WATER,            0,
      {@String(gettext("bottle of water"))@},
      NULL,
      FLAGS_POTION,         1,     2,     3,      CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_water)
	@})
//}}}
//{{{
ITEM( '!',  POTION_WATER_HEAL,       0,
      {@String(gettext("bottle of water"))@},
      NULL,
      FLAGS_POTION,         1,     2,     3,      CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_heal)
	@})
//}}}
//{{{
ITEM( '!',  POTION_WATER_MANA,       0,
      {@String(gettext("bottle of water"))@},
      NULL,
      FLAGS_POTION,         1,     2,     3,      CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_water_mana)
	@})
//}}}
//{{{
ITEM( '!',  POTION_WATER_POISON,     0,
      {@String(gettext("bottle of water"))@},
      NULL,
      FLAGS_POTION,         1,     2,     3,      CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_water_poison)
	@})
//}}}
//{{{
ITEM( '!',  POTION_WATER_HALLUCINOGEN, 0,
      {@String(gettext("bottle of water"))@},
      NULL,
      FLAGS_POTION,         1,     2,     3,      CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_water_hallucinogen)
	@})
//}}}
//{{{
ITEM( '!',  POTION_WATER_RESTORE,    0,
      {@String(gettext("bottle of water"))@},
      NULL,
      FLAGS_POTION,         1,     2,     3,      CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_water_restore)
	@})
//}}}
//{{{
ITEM( '!',  POTION_HEAL,             0,
      {@String(gettext("potion of healing"))@},
      POTIONNAMES_1,
      FLAGS_POTION,         1,     6,     75,     CAT_POTN,   -1,
	2,
	{@USEEFFECT(potion_heal)
	  THROWHITEFFECT(potion_hit_heal)
	@})
//}}}
//{{{
ITEM( '!',  POTION_EXTRAHEAL,        0,
      {@String(gettext("potion of extra healing"))@},
      POTIONNAMES_2,
      FLAGS_POTION,         1,     6,     150,    CAT_POTN,   -1,
	2,
	{@USEEFFECT(potion_extra_heal)
	  THROWHITEFFECT(potion_hit_extra_heal)
	@})
//}}}
//{{{
ITEM( '!',  POTION_FULLHEAL,         0,
      {@String(gettext("potion of full healing"))@},
      POTIONNAMES_3,
      FLAGS_POTION,         1,     6,     250,    CAT_POTN,   -1,
	2,
	{@USEEFFECT(potion_full_heal)
	  THROWHITEFFECT(potion_hit_full_heal)
	@})
//}}}
//{{{
ITEM( '!',  POTION_SICKNESS,         0,
      {@String(gettext("potion of sickness"))@},
      POTIONNAMES_4,
      FLAGS_POTION,         1,     6,     150,    CAT_POTN,   -1,
	2,
	{@USEEFFECT(potion_sickness)
	  THROWHITEFFECT(potion_hit_sickness)
	@})
//}}}
//{{{
ITEM( '!',  POTION_HALLU,            0,
      {@String(gettext("potion of hallucination"))@},
      POTIONNAMES_5,
      FLAGS_POTION,         1,     6,     75,     CAT_POTN,   -1,
	2,
	{@USEEFFECT(potion_hallucination)
	  THROWHITEFFECT(potion_hit_confuse)
	@})
//}}}
//{{{
ITEM( '!',  POTION_CONF,             0,
      {@String(gettext("potion of confusion"))@},
      POTIONNAMES_6,
      FLAGS_POTION,         1,     6,     75,     CAT_POTN,   -1,
	2,
	{@USEEFFECT(potion_confuse)
	  THROWHITEFFECT(potion_hit_confuse)
	@})
//}}}
//{{{
ITEM( '!',  POTION_OBJDETECT,        0,
      {@String(gettext("potion of object detection"))@},
      POTIONNAMES_7,
      FLAGS_POTION,         1,     6,     150,    CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_detect_objects)
	@})
//}}}
//{{{
ITEM( '!',  POTION_NUMBNESS,         0,
      {@String(gettext("potion of numbness"))@},
      POTIONNAMES_8,
      FLAGS_POTION,         1,     6,     75,     CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_numbness)
	@})
//}}}
//{{{
ITEM( '!',  POTION_GAINST,           0,
      {@String(gettext("potion of gain strength"))@},
      POTIONNAMES_9,
      FLAGS_POTION,         1,     6,     350,    CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_gain_strength)
	@})
//}}}
//{{{
ITEM( '!',  POTION_GAINDX,           0,
      {@String(gettext("potion of gain dexterity"))@},
      POTIONNAMES_10,
      FLAGS_POTION,         1,     6,     350,    CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_gain_dexterity)
	@})
//}}}
//{{{
ITEM( '!',  POTION_GAINTO,           0,
      {@String(gettext("potion of gain toughness"))@},        
      POTIONNAMES_11,                            
      FLAGS_POTION,         1,     6,     350,    CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_gain_toughness)
	@})
//}}}
//{{{
ITEM( '!',  POTION_GAINMN,           0,
      {@String(gettext("potion of gain mana"))@},             
      POTIONNAMES_12,                            
      FLAGS_POTION,         1,     6,     350,    CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_gain_mana)
	@})
//}}}
//{{{
ITEM( '!',  POTION_GAINWI,           0,
      {@String(gettext("potion of gain willpower"))@},        
      POTIONNAMES_13,                            
      FLAGS_POTION,         1,     6,     350,    CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_gain_willpower)
	@})
//}}}
//{{{
ITEM( '!',  POTION_RESTORE,          0,
      {@String(gettext("potion of restore ability"))@},       
      POTIONNAMES_14,                            
      FLAGS_POTION,         1,     6,     250,    CAT_POTN,   -1,
	1,
	{@USEEFFECT(potion_restore_ability)
	@})
//}}}
//-------------------------------------------------------------------//
//{{{
ITEM( '?',  SCROLL_BLANK,            LWHITE,
      {@String(gettext("scroll of blank paper"))@},
      {@Itemstring(gettext("unlabelled scroll"))@},
      FLAGS_SCROLL,         8,     4,     10,     CAT_SCRL,   -1,
	2,
	{@USEEFFECT(scroll_blank)
	  CARRIED_STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_BLANKSCROLL)
	@})
//}}}
//{{{
ITEM( '?',  SCROLL_MAGICMAP,         0,
      {@String(gettext("scroll of magic mapping"))@},
      SCROLLNAMES_1,
      FLAGS_SCROLL,         1,     4,     150,    CAT_SCRL,   -1,
	1,
	{@USEEFFECT(scroll_magic_map)
	@})
//}}}
//{{{
ITEM( '?',  SCROLL_TELEPORT,         0,
      {@String(gettext("scroll of teleportation"))@},
      SCROLLNAMES_2,
      FLAGS_SCROLL,         1,     4,     100,    CAT_SCRL,   -1,
	1,
	{@USEEFFECT(scroll_teleport)
	@})
//}}}
//{{{
ITEM( '?',  SCROLL_IDENTIFY,         0,
      {@String(gettext("scroll of identify"))@},
      SCROLLNAMES_3,
      FLAGS_SCROLL,         1,     4,     100,    CAT_SCRL,   -1,
	1,
	{@USEEFFECT(scroll_identify)
	@})
//}}}
//{{{
ITEM( '?',  SCROLL_UNCURSE,          0,
      {@String(gettext("scroll of remove curse"))@},
      SCROLLNAMES_4,
      FLAGS_SCROLL,         1,     4,     150,    CAT_SCRL,   -1,
	1,
	{@USEEFFECT(scroll_uncurse)
	@})
//}}}
//{{{
ITEM( '?',  SCROLL_CREATEMONST,      0,
      {@String(gettext("scroll of create monsters"))@},
      SCROLLNAMES_5,
      FLAGS_SCROLL,         1,     4,     150,    CAT_SCRL,   -1,
	1,
	{@USEEFFECT(scroll_createmonsters)
	@})
//}}}
//{{{
ITEM( '?',  SCROLL_ENCHANTING,       0,
      {@String(gettext("scroll of enchanting"))@},
      SCROLLNAMES_6,
      FLAGS_SCROLL,         1,     4,     300,    CAT_SCRL,   -1,
	1,
	{@USEEFFECT(scroll_enchanting)
	@})
//}}}
//-------------------------------------------------------------------//
//{{{
ITEM( ']',  TOOL_HOLYSYMBOL,         LWHITE,
      {@String(gettext("cross"))@},
      NULL,
      FLAGS_TOOL,           1,     6,     60,     CAT_TOOL,   -1,
	1,
	{@USEEFFECT(tool_holysymbol)
	@})
//}}}
//{{{
ITEM( ']',  TOOL_PICKAXE,            WHITE,
      {@String(gettext("pick-axe"))@},
      NULL,
      FLAGS_TOOL,           1,     30,     100,     CAT_TOOL,   -1,
	1,
	{@USEEFFECT(tool_pickaxe)
	@})
//}}}
//-------------------------------------------------------------------//
//{{{
ITEM( '%',  FOOD_RATION,             YELLOW,
      {@String(gettext("food ration"))@},
      NULL,
      FLAGS_FOOD,           1,     15,    40,     CAT_FOOD,   -1,
	1,
	{@USEEFFECT(food_ration)
	@})
//}}}
//-------------------------------------------------------------------//
//{{{
ITEM( '*',  GEM_DIAMOND,             LWHITE,
      {@String(gettext("diamond"))@},
      {@Itemstring(gettext("white gem"))@},
      FLAGS_GEM,            1,     5,     1000,   CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_RUBY,                LRED,
      {@String(gettext("ruby"))@},
      {@Itemstring(gettext("red gem"))@},
      FLAGS_GEM,            1,     5,     1000,   CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_JACINTH,             YELLOW,
      {@String(gettext("jacinth stone"))@},
      {@Itemstring(gettext("orange gem"))@},
      FLAGS_GEM,            1,     5,     650,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_SAPPHIRE,            LBLUE,
      {@String(gettext("sapphire"))@},
      {@Itemstring(gettext("blue gem"))@},
      FLAGS_GEM,            1,     5,     650,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_BLACKOPAL,           LBLACK,
      {@String(gettext("black opal"))@},
      {@Itemstring(gettext("black gem"))@},
      FLAGS_GEM,            1,     5,     550,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_EMERALD,             LGREEN,
      {@String(gettext("emerald"))@},
      {@Itemstring(gettext("green gem"))@},
      FLAGS_GEM,            1,     5,     500,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_TURQUOISE,           LBLUE,
      {@String(gettext("turquoise stone"))@},
      {@Itemstring(gettext("blue gem"))@},
      FLAGS_GEM,            1,     5,     500,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_AQUAMARINE,          LBLUE,
      {@String(gettext("aquamarine stone"))@},
      {@Itemstring(gettext("blue gem"))@},
      FLAGS_GEM,            1,     5,     500,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_CITRINE,             YELLOW,
      {@String(gettext("citrine stone"))@},
      {@Itemstring(gettext("yellow gem"))@},
      FLAGS_GEM,            1,     5,     500,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_AMBER,               YELLOW,
      {@String(gettext("amber stone"))@},
      {@Itemstring(gettext("yellowish brown gem"))@},
      FLAGS_GEM,            1,     5,     500,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_TOPAZ,               YELLOW,
      {@String(gettext("topaz stone"))@},
      {@Itemstring(gettext("yellowish brown gem"))@},
      FLAGS_GEM,            1,     5,     450,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_JET,                 LBLACK,
      {@String(gettext("jet stone"))@},
      {@Itemstring(gettext("black gem"))@},
      FLAGS_GEM,            1,     5,     450,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_OPAL,                LWHITE,
      {@String(gettext("opal"))@},
      {@Itemstring(gettext("white gem"))@},
      FLAGS_GEM,            1,     5,     450,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_CHRYSOBERYL,         LYELLOW,
      {@String(gettext("chrysoberyl stone"))@},
      {@Itemstring(gettext("yellow gem"))@},
      FLAGS_GEM,            1,     5,     350,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_GARNET,              LRED,
      {@String(gettext("garnet stone"))@},
      {@Itemstring(gettext("red gem"))@},
      FLAGS_GEM,            1,     5,     350,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_AMETHYST,            MAGENTA,
      {@String(gettext("amethyst stone"))@},
      {@Itemstring(gettext("violet gem"))@},
      FLAGS_GEM,            1,     5,     350,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_JASPER,              LRED,
      {@String(gettext("jasper stone"))@},
      {@Itemstring(gettext("red gem"))@},
      FLAGS_GEM,            1,     5,     300,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_FLUORITE,            GREEN,
      {@String(gettext("fluorite stone"))@},
      {@Itemstring(gettext("green gem"))@},
      FLAGS_GEM,            1,     5,     250,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_JADE,                GREEN,
      {@String(gettext("jade stone"))@},
      {@Itemstring(gettext("green gem"))@},
      FLAGS_GEM,            1,     5,     200,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_AGATE,               YELLOW,
      {@String(gettext("agate stone"))@},
      {@Itemstring(gettext("orange gem"))@},
      FLAGS_GEM,            1,     5,     200,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_OBSIDIAN,            LBLACK,
      {@String(gettext("obsidian stone"))@},
      {@Itemstring(gettext("black gem"))@},
      FLAGS_GEM,            1,     5,     100,    CAT_GEM,    -1,
	1,
	{@SCORE(2)
	@})
//}}}
//{{{
ITEM( '*',  GEM_WHITEGLASS,          LWHITE,
      {@String(gettext("worthless piece of white glass"))@},
      {@Itemstring(gettext("white gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  GEM_REDGLASS,            LRED,
      {@String(gettext("worthless piece of red glass"))@},
      {@Itemstring(gettext("red gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  GEM_ORANGEGLASS,         YELLOW,
      {@String(gettext("worthless piece of orange glass"))@},
      {@Itemstring(gettext("orange gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  GEM_BLUEGLASS,           LBLUE,
      {@String(gettext("worthless piece of blue glass"))@},
      {@Itemstring(gettext("blue gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  GEM_BLACKGLASS,          LBLACK,
      {@String(gettext("worthless piece of black glass"))@},
      {@Itemstring(gettext("black gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  GEM_GREENGLASS,          LGREEN,
      {@String(gettext("worthless piece of green glass"))@},
      {@Itemstring(gettext("green gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  GEM_YELLOWGLASS,         LYELLOW,
      {@String(gettext("worthless piece of yellow glass"))@},
      {@Itemstring(gettext("yellow gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  GEM_VIOLETGLASS,         MAGENTA,
      {@String(gettext("worthless piece of violet glass"))@},
      {@Itemstring(gettext("violet gem"))@},
      FLAGS_GEM,            1,     5,     5,      CAT_GEM,    -1,
	0,
	{@@})
//}}}
//{{{
ITEM( '*',  ILLUMINYTE,              LYELLOW,
      {@String(gettext("piece of illuminyte"))@},
      {@Itemstring(gettext("glowing rock"))@},
      FLAGS_GEM,            1,     5,     100,    CAT_GEM,    -1,
	1,
	{@CARRIED_STAT_ADD(STAT_LIGHTRADIUS, 1)@})
//}}}
//////////////////////////////////////////////////////////////////////
// Ammo                                                             //
//////////////////////////////////////////////////////////////////////
//      C   Identifier               Color                          //
//    Name                                                          //
//    UnID Name                                                     //
//    Flags                 Stack  Weight Value   Category    Slot  //
//{{{
ITEM( '/',  AMMO_ARROW,              YELLOW,
      {@String(gettext("arrow"))@},
      NULL,
      FLAGS_AMMO,           15,    1,     6,      CAT_AMMO,   1,
	5,
	{@WEAREFFECT(ready_ammo)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MAX, 6)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MIN, 1)
	  FIRED_STAT_ADDP(STAT_MISSILE_TOHIT, 0)
	  LAUNCHFROM(1)
	@})
//}}}
//{{{
ITEM( '/',  AMMO_BOLT,               YELLOW,
      {@String(gettext("bolt"))@},
      NULL,
      FLAGS_AMMO,           15,    1,     8,      CAT_AMMO,   1,
	5,
	{@WEAREFFECT(ready_ammo)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MAX, 8)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MIN, 2)
	  FIRED_STAT_ADDP(STAT_MISSILE_TOHIT, 0)
	  LAUNCHFROM(2)
	@})
//}}}
//{{{
ITEM( '/',  AMMO_SILVERARROW,        LWHITE,
      {@String(gettext("silver arrow"))@},
      NULL,
      FLAGS_AMMO,           11,    1,     15,     CAT_AMMO,   1,
	5,
	{@WEAREFFECT(ready_ammo)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MAX, 7)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MIN, 2)
	  FIRED_STAT_ADDP(STAT_MISSILE_TOHIT, 0)
	  LAUNCHFROM(1)
	@})
//}}}
//{{{
ITEM( '/',  AMMO_SILVERBOLT,         LWHITE,
      {@String(gettext("silver bolt"))@},
      NULL,
      FLAGS_AMMO,           11,    1,     25,     CAT_AMMO,   1,
	5,
	{@WEAREFFECT(ready_ammo)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MAX, 10)
	  FIRED_STAT_ADDP(STAT_MISSILEDAM_MIN, 3)
	  FIRED_STAT_ADDP(STAT_MISSILE_TOHIT, 0)
	  LAUNCHFROM(2)
	@})
//}}}
//////////////////////////////////////////////////////////////////////
// Equipment                                                        //
//////////////////////////////////////////////////////////////////////
//      C   Identifier               Color                          //
//    Name                                                          //
//    UnID Name                                                     //
//    Flags                 Stack  Weight Value   Category    Slot  //
//{{{
ITEM( '|',  WEAPON_CLUB,             YELLOW,
      {@String(gettext("club"))@},
      NULL,
      FLAGS_WEAPON,         1,     10,    5,      CAT_WEAP,   0,
	5,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 4)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_TOHIT, -1)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_CLUB)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_DAGGER,           WHITE,
      {@String(gettext("dagger"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     4,     10,     CAT_WEAP,   0,
	8,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 5)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_TOHIT, 2)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_DAGGER)
	  STAT_ADDP(STAT_MISSILEDAM_MIN, 1)
	  STAT_ADDP(STAT_MISSILEDAM_MAX, 5)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_DAGGER)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_STAFF,            YELLOW,
      {@String(gettext("quarterstaff"))@},
      NULL,
      FLAGS_WEAPON,         1,     10,    15,     CAT_WEAP,   0,
	6,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 5)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_TOHIT, 1)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_STAFF)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_STAFF)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_MACE,             WHITE,
      {@String(gettext("mace"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     15,    25,     CAT_WEAP,   0,
	5,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 6)
	  STAT_ADDP(STAT_DAMAGE_MIN, 2)
	  STAT_ADDP(STAT_TOHIT, 1)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_MACE)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_SWORD,            WHITE,
      {@String(gettext("sword"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     15,    35,     CAT_WEAP,   0,
	5,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 9)
	  STAT_ADDP(STAT_DAMAGE_MIN, 2)
	  STAT_ADDP(STAT_TOHIT, 1)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_SWORD)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_AXE,              WHITE,
      {@String(gettext("axe"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     20,    35,     CAT_WEAP,   0,
	5,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 10)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_TOHIT, 0)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_AXE)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '|',  WEAPON_CRYSTAL_DAGGER,   LCYAN,
      {@String(gettext("crystal dagger"))@},
      NULL,
      FLAGS_WEAPON,         1,     6,     60,     CAT_WEAP,   0,
	8,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 5)
	  STAT_ADDP(STAT_DAMAGE_MIN, 2)
	  STAT_ADDP(STAT_TOHIT, 2)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_DAGGER)
	  STAT_ADDP(STAT_MISSILEDAM_MIN, 2)
	  STAT_ADDP(STAT_MISSILEDAM_MAX, 5)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_DAGGER)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_SILVERDAGGER,     LWHITE,
      {@String(gettext("silver dagger"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     8,     30,     CAT_WEAP,   0,
	8,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 6)
	  STAT_ADDP(STAT_DAMAGE_MIN, 2)
	  STAT_ADDP(STAT_TOHIT, 2)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_DAGGER)
	  STAT_ADDP(STAT_MISSILEDAM_MIN, 3)
	  STAT_ADDP(STAT_MISSILEDAM_MAX, 7)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_DAGGER)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_SILVERSTAFF,      YELLOW,
      {@String(gettext("silver-shod quarterstaff"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     14,    50,     CAT_WEAP,   0,
	6,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 6)
	  STAT_ADDP(STAT_DAMAGE_MIN, 2)
	  STAT_ADDP(STAT_TOHIT, 1)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_STAFF)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_STAFF)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_SILVERMACE,       LWHITE,
      {@String(gettext("silver mace"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     19,    75,     CAT_WEAP,   0,
	5,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 7)
	  STAT_ADDP(STAT_DAMAGE_MIN, 3)
	  STAT_ADDP(STAT_TOHIT, 1)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_MACE)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_SILVERSWORD,      LWHITE,
      {@String(gettext("silver longsword"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     19,    100,    CAT_WEAP,   0,
	5,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 10)
	  STAT_ADDP(STAT_DAMAGE_MIN, 3)
	  STAT_ADDP(STAT_TOHIT, 1)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_SWORD)
	@})
//}}}
//{{{
ITEM( '|',  WEAPON_SILVERAXE,        LWHITE,
      {@String(gettext("silver axe"))@},
      NULL,
      FLAGS_METALWEAPON,    1,     24,    100,    CAT_WEAP,   0,
	5,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 11)
	  STAT_ADDP(STAT_DAMAGE_MIN, 2)
	  STAT_ADDP(STAT_TOHIT, 0)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_AXE)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '}',  WEAPON_BOW,              YELLOW,
      {@String(gettext("bow"))@},
      NULL,
      FLAGS_LAUNCHER,       1,     13,    30,     CAT_WEAP,   0,
	8,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 1)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_MISSILE_TOHIT, 2)
	  STAT_OR(STAT_MISSILES, 1)
	  STAT_ADDP(STAT_MISSILEDAM_MAX, 0)
	  STAT_ADDP(STAT_MISSILEDAM_MIN, 0)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_BOW)
	@})
//}}}
//{{{
ITEM( '}',  WEAPON_CROSSBOW,         YELLOW,
      {@String(gettext("crossbow"))@},
      NULL,
      FLAGS_LAUNCHER,       1,     1,     50,     CAT_WEAP,   0,
	8,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 1)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_MISSILE_TOHIT, 3)
	  STAT_OR(STAT_MISSILES, 2)
	  STAT_ADDP(STAT_MISSILEDAM_MAX, 0)
	  STAT_ADDP(STAT_MISSILEDAM_MIN, 0)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_CROSSBOW)
	@})
//}}}
//{{{
ITEM( '}',  WEAPON_BOW_ACCURACY,     YELLOW,
      {@String(gettext("bow of accuracy"))@},
      {@Itemstring(gettext("bow"))@},
      FLAGS_MAGICLAUNCHER,  1,     13,    300,    CAT_WEAP,   0,
	8,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 1)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_MISSILE_TOHIT, 8)
	  STAT_OR(STAT_MISSILES, 1)
	  STAT_ADDP(STAT_MISSILEDAM_MAX, 0)
	  STAT_ADDP(STAT_MISSILEDAM_MIN, 0)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_BOW)
	@})
//}}}
//{{{
ITEM( '}',  WEAPON_CROSSBOW_FORCE,   YELLOW,
      {@String(gettext("crossbow of force"))@},
      {@Itemstring(gettext("crossbow"))@},
      FLAGS_MAGICLAUNCHER,  1,     1,     400,    CAT_WEAP,   0,
	8,
	{@WEAREFFECT(ready_weapon)
	  STAT_ADDP(STAT_DAMAGE_MAX, 1)
	  STAT_ADDP(STAT_DAMAGE_MIN, 1)
	  STAT_ADDP(STAT_MISSILE_TOHIT, 3)
	  STAT_OR(STAT_MISSILES, 2)
	  STAT_ADDP(STAT_MISSILEDAM_MAX, 5)
	  STAT_ADDP(STAT_MISSILEDAM_MIN, 3)
	  STAT_SET(STAT_WEAPON_TYPE, WEAPONTYPE_CROSSBOW)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '[',  ARMR_LEATHER,            YELLOW,
      {@String(gettext("leather armor"))@},
      NULL,
      FLAGS_ARMOR,          1,     20,    20,     CAT_ARMR,   2,
	3,
	{@WEAREFFECT(ready_armor)
	  STAT_ADDP(STAT_DV, 2)
	  STAT_ADDP(STAT_PV, 1)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_CHAIN,              WHITE,
      {@String(gettext("chain armor"))@},
      NULL,
      FLAGS_METALARMOR,     1,     20,    30,     CAT_ARMR,   2,
	4,
	{@WEAREFFECT(ready_armor)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_ADDP(STAT_PV, 3)
	  STAT_ADD(STAT_DEXTERITY,-1)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_RING,               WHITE,
      {@String(gettext("ring armor"))@},
      NULL,
      FLAGS_METALARMOR,     1,     20,    40,     CAT_ARMR,   2,
	4,
	{@WEAREFFECT(ready_armor)
	  STAT_ADDP(STAT_DV, 0)
	  STAT_ADDP(STAT_PV, 4)
	  STAT_ADD(STAT_DEXTERITY,-1)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_PLATE,              WHITE,
      {@String(gettext("plate armor"))@},
      NULL,
      FLAGS_METALARMOR,     1,     20,    80,     CAT_ARMR,   2,
	4,
	{@WEAREFFECT(ready_armor)
	  STAT_ADDP(STAT_DV, 0)
	  STAT_ADDP(STAT_PV, 5)
	  STAT_ADD(STAT_DEXTERITY,-2)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_SHINING,            WHITE,
      {@String(gettext("shining armor"))@},
      NULL,
      FLAGS_METALARMOR,     1,     20,    80,     CAT_ARMR,   2,
	4,
	{@WEAREFFECT(ready_shining_armor)
	  STAT_ADDP(STAT_DV, 4)
	  STAT_ADDP(STAT_PV, 7)
	  STAT_ADD(STAT_LIGHTRADIUS, 1)
	  STAT_ADD(STAT_DEXTERITY,-2)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_DWARFISH,           LWHITE,
      {@String(gettext("dwarfish mithril armor"))@},
      NULL,
      FLAGS_METALARMOR,     1,     20,    3000,   CAT_ARMR,   2,
	4,
	{@WEAREFFECT(ready_dwarfish_mithril)
	  STAT_ADDP(STAT_DV, 6)
	  STAT_ADDP(STAT_PV, 8)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '[',  ARMR_CLOAK,              LBLUE,
      {@String(gettext("cloak"))@},
      NULL,
      FLAGS_ARMOR,          1,     5,     5,      CAT_ARMR,   3,
	2,
	{@WEAREFFECT(ready_armor)
	  STAT_ADDP(STAT_DV, 1)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_CLOAK_INVULN,       LBLUE,
      {@String(gettext("cloak of invulnerability"))@},
      {@Itemstring(gettext("cloak"))@},
      FLAGS_RING_FUELED,    70,    5,     200,    CAT_ARMR,   3,
	5,
	{@BURN(burn_cloak_invuln)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_TIMER)
	  WEAREFFECT(ready_cloak_invuln)
	  STAT_ADD(STAT_DV, 25)
	  STAT_ADD(STAT_PV, 15)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '[',  ARMR_CAP,                YELLOW,
      {@String(gettext("leather cap"))@},
      NULL,
      FLAGS_ARMOR,          1,     3,     5,      CAT_ARMR,   4,
	2,
	{@WEAREFFECT(ready_helmet)
	  STAT_ADDP(STAT_DV, 1)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_IRONHELM,           WHITE,
      {@String(gettext("iron helmet"))@},
      NULL,
      FLAGS_METALARMOR,     1,     10,    15,     CAT_ARMR,   4,
	4,
	{@WEAREFFECT(ready_helmet)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_ADDP(STAT_PV, 1)
	  STAT_ADD(STAT_DEXTERITY,-1)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_HELM_SEEING,        WHITE,
      {@String(gettext("helm of seeing"))@},
      {@Itemstring(gettext("iron helmet"))@},
      FLAGS_MAGICMETALARMOR,1,     10,    15,     CAT_ARMR,   4,
	5,
	{@WEAREFFECT(ready_helmet)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_ADDP(STAT_PV, 1)
	  STAT_ADD(STAT_DEXTERITY,-1)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_SEEINVIS)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_HELM_DELUSION,      WHITE,
      {@String(gettext("helm of delusion"))@},
      {@Itemstring(gettext("iron helmet"))@},
      FLAGS_CURSED_ARMOR,   1,     10,    15,     CAT_ARMR,   4,
	5,
	{@WEAREFFECT(ready_helmet)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_ADDP(STAT_PV, 1)
	  STAT_ADD(STAT_DEXTERITY,-1)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_HALLUCINATING)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( ']',  TOOL_LANTERN,            LYELLOW,
      {@String(gettext("brass lantern"))@},
      NULL,
      FLAGS_TOOL_WORN,      1,     10,    10,     CAT_TOOL,   5,
	2,
	{@WEAREFFECT(ready_lantern)
	  STAT_ADDP(STAT_LIGHTRADIUS, 2)
	@})
//}}}
//{{{
ITEM( ']',  TOOL_TORCH,              LYELLOW,
      {@String(gettext("torch"))@},
      NULL,
      FLAGS_TORCH,          1300,  15,    8,      CAT_TOOL,   5,
	5,
	{@WEAREFFECT(ready_torch)
	  STAT_ADDP(STAT_LIGHTRADIUS, 3)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_TIMER)
	  BURN(burn_torch)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_FLAME)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_SMSHIELD,           WHITE,
      {@String(gettext("small shield"))@},
      NULL,
      FLAGS_METALARMOR,     1,     10,    15,     CAT_ARMR,   5,
	3,
	{@WEAREFFECT(ready_shield)
	  STAT_ADDP(STAT_DV, 2)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_SHIELD)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_MDSHIELD,           WHITE,
      {@String(gettext("medium shield"))@},
      NULL,
      FLAGS_METALARMOR,     1,     14,    20,     CAT_ARMR,   5,
	3,
	{@WEAREFFECT(ready_shield)
	  STAT_ADDP(STAT_DV, 3)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_SHIELD)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_LGSHIELD,           WHITE,
      {@String(gettext("large shield"))@},
      NULL,
      FLAGS_METALARMOR,     1,     20,    30,     CAT_ARMR,   5,
	4,
	{@WEAREFFECT(ready_shield)
	  STAT_ADDP(STAT_DV, 5)
	  STAT_ADD(STAT_DEXTERITY,-1)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_SHIELD)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '[',  ARMR_GLOVES,             YELLOW,
      {@String(gettext("pair of gloves"))@},
      NULL,
      FLAGS_ARMOR,          1,     2,     5,      CAT_ARMR,   6,
	3,
	{@WEAREFFECT(ready_gloves)
	  STAT_ADDP(STAT_DV, 0)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_GLOVES)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_GAUNTLETS,          WHITE,
      {@String(gettext("pair of gauntlets"))@},
      NULL,
      FLAGS_METALARMOR,     1,     3,     15,     CAT_ARMR,   6,
	3,
	{@WEAREFFECT(ready_gloves)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_GLOVES)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_GAUNTLETS_POWER,    WHITE,
      {@String(gettext("gauntlets of power"))@},
      {@Itemstring(gettext("pair of gauntlets"))@},
      FLAGS_MAGICMETALARMOR,1,     3,     300,    CAT_ARMR,   6,
	4,
	{@WEAREFFECT(ready_gloves)
      STAT_ADDP(STAT_DV, 1)
	  STAT_ADD(STAT_STRENGTH, 4)
	  STAT_OR(STAT_COMPONENTS, STAT_COMPONENT_GLOVES)
	@})
//}}}
//------------------------------------------------------------------//
//{{{
ITEM( '[',  ARMR_BOOTS,              YELLOW,
      {@String(gettext("boots"))@},
      NULL,
      FLAGS_ARMOR,          1,     4,     20,     CAT_ARMR,   7,
	3,
	{@WEAREFFECT(ready_boots)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_ADD(STAT_DEXTERITY,2)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_SPEEDBOOTS,         YELLOW,
      {@String(gettext("speed boots"))@},
      {@Itemstring(gettext("boots"))@},
      FLAGS_MAGICARMOR,     1,     4,     450,    CAT_ARMR,   7,
	4,
	{@WEAREFFECT(ready_boots)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_ADD(STAT_SPEED,2)
	  STAT_ADD(STAT_DEXTERITY,2)
	@})
//}}}
//{{{
ITEM( '[',  ARMR_BOOTS_ICE,          YELLOW,
      {@String(gettext("boots of ice"))@},
      {@Itemstring(gettext("boots"))@},
      FLAGS_CURSED_ARMOR,   1,     4,     20,     CAT_ARMR,   7,
	3,
	{@WEAREFFECT(ready_boots_ice)
	  STAT_ADDP(STAT_DV, 1)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_SLIPPERY)
	@})
//}}}
//////////////////////////////////////////////////////////////////////
//{{{
ITEM( '=',  RING_PLAIN,              0,
      {@String(gettext("plain ring"))@},
      NULL,
      FLAGS_RING,           1,     2,     20,     CAT_RING,   8,
	1,
	{@WEAREFFECT(ready_ring)
	@})
//}}}
//{{{
ITEM( '=',  RING_STRENGTH,           0,
      {@String(gettext("ring of strength"))@},
      RINGNAMES_1,
      FLAGS_RING,           1,     2,     200,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring)
	  STAT_ADDP(STAT_STRENGTH,4)
	@})
//}}}
//{{{
ITEM( '=',  RING_DEXTERITY,          0,
      {@String(gettext("ring of dexterity"))@},
      RINGNAMES_2,
      FLAGS_RING,           1,     2,     200,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring)
	  STAT_ADDP(STAT_DEXTERITY,3)
	@})
//}}}
//{{{
ITEM( '=',  RING_TOUGHNESS,          0,
      {@String(gettext("ring of toughness"))@},
      RINGNAMES_3,
      FLAGS_RING,           1,     2,     200,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring)
	  STAT_ADDP(STAT_TOUGHNESS,4)
	@})
//}}}
//{{{
ITEM( '=',  RING_WILLPOWER,          0,
      {@String(gettext("ring of willpower"))@},
      RINGNAMES_4,
      FLAGS_RING,           1,     2,     100,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring)
	  STAT_ADDP(STAT_WILLPOWER,4)
	@})
//}}}
//{{{
ITEM( '=',  RING_MANA,               0,
      {@String(gettext("ring of mana"))@},
      RINGNAMES_5,
      FLAGS_RING,           1,     2,     100,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring)
	  STAT_ADDP(STAT_MANA,5)
	@})
//}}}
//{{{
ITEM( '=',  RING_PROTECTION,         0,
      {@String(gettext("ring of protection"))@},
      RINGNAMES_6,
      FLAGS_RING,           1,     2,     200,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring_protection)
	  STAT_ADDP(STAT_PV, 2)
	@})
//}}}
//{{{
ITEM( '=',  RING_ILLUMINATION,       0,
      {@String(gettext("ring of illumination"))@},
      RINGNAMES_7,
      FLAGS_RING,           1,     2,     200,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring_illumination)
	  STAT_ADD(STAT_LIGHTRADIUS, 2)
	@})
//}}}
//{{{
ITEM( '=',  RING_DAMAGE,             0,
      {@String(gettext("ring of damage"))@},
      RINGNAMES_8,
      FLAGS_RING,           1,     2,     300,    CAT_RING,   8,
	3,
	{@WEAREFFECT(ready_ring)
	  STAT_ADDP(STAT_DAMAGE_MIN, 3)
	  STAT_ADDP(STAT_DAMAGE_MAX, 3)
	@})
//}}}
//{{{
ITEM( '=',  RING_DETECTINVIS,        0,
      {@String(gettext("ring of detect invisibility"))@},
      RINGNAMES_9,
      FLAGS_RING,           1,     2,     100,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring_detectinvis)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_SEEINVIS)
	@})
//}}}
//{{{
ITEM( '=',  RING_RESIST_POISON,      0,
      {@String(gettext("ring of poison resistance"))@},
      RINGNAMES_10,
      FLAGS_RING,           1,     2,     100,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_RESIST_POISON)
	@})
//}}}
//{{{
ITEM( '=',  RING_HUNGER,             0,
      {@String(gettext("ring of hunger"))@},
      RINGNAMES_11,
      FLAGS_CURSED_RING,    1,     2,     100,    CAT_RING,   8,
	2,
	{@WEAREFFECT(ready_ring_hunger)
	  STAT_ADD(STAT_DIGESTION, 12)
	@})
//}}}
//{{{
ITEM( '=',  RING_TELEPORTATION,      0,
      {@String(gettext("ring of teleportation"))@},
      RINGNAMES_12,
      FLAGS_RING_CHARGED,   10,    2,     200,    CAT_RING,   8,
	1,
	{@WEAREFFECT(ready_ring_teleportation)
	@})
//}}}
//{{{
ITEM( '=',  RING_TIMEDILATION,       0,
      {@String(gettext("ring of time dilation"))@},
      RINGNAMES_13,
      FLAGS_RING_FUELED,    45,    2,     200,    CAT_RING,   8,
	5,
	{@BURN(burn_ring_timedilation)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_TIMER)
	  STAT_OR(STAT_FLAGS, STAT_FLAG_SLIPPERY)
	  WEAREFFECT(ready_ring_timedilation)
	  STAT_ADDP(STAT_SPEED, 15)
	@})
//}}}
//{{{
ITEM( '\"',  AMULET_SLOWDIGESTION,   0,
      {@String(gettext("amulet of slow digestion"))@},
      AMULETNAMES_1,
      FLAGS_AMULET,         1,     2,     400,    CAT_AMULET, 9,
	2,
	{@WEAREFFECT(ready_amulet_slow_digestion)
	  STAT_ADD(STAT_DIGESTION, -8)
	@})
//}}}
//{{{
ITEM( '\"',  AMULET_BRILLIANCE,      0,
      {@String(gettext("amulet of brilliance"))@},
      AMULETNAMES_2,
      FLAGS_AMULET,         1,     2,     400,    CAT_AMULET, 9,
	2,
	{@WEAREFFECT(ready_amulet_brilliance)
	  STAT_ADD(STAT_LIGHTRADIUS, 4)
	@})
//}}}
//{{{
ITEM( '\"',  AMULET_SPEED,           0,
      {@String(gettext("amulet of speed"))@},
      AMULETNAMES_3,
      FLAGS_AMULET,         1,     2,     400,    CAT_AMULET, 9,
	3,
	{@WEAREFFECT(ready_amulet_speed)
	  STAT_ADD(STAT_SPEED, 2)
	  STAT_ADDP(STAT_DEXTERITY, 0)
	@})
//}}}
//{{{
ITEM( '\"',  AMULET_REGENERATION,    0,
      {@String(gettext("amulet of regeneration"))@},
      AMULETNAMES_4,
      FLAGS_AMULET,         1,     2,     400,    CAT_AMULET, 9,
	3,
	{@WEAREFFECT(ready_amulet_regeneration)
	  STAT_ADD(STAT_REGEN, 1)
	  STAT_ADD(STAT_DIGESTION, 12)
	@})
//}}}
//{{{
ITEM( '\"',  AMULET_TELEKINESIS,     0,
      {@String(gettext("amulet of telekinesis"))@},
      AMULETNAMES_5,
      FLAGS_AMULET,         1,     2,     400,    CAT_AMULET, 9,
	2,
	{@WEAREFFECT(ready_amulet_telekinesis)
	  STAT_OR(STAT_MISSILES, 255)
	@})
//}}}
//////////////////////////////////////////////////////////////////////

//{{{
void ready_item(int which, int force_plural, char *ready_string, char *where)
{
	int plural = 0;
	
	if(force_plural || get_plr()->inventory[which].stacksize > 1)
		plural = 1;
	
	message(ready_string, n_itemname(which));
	get_plr()->inventory[which].flags |= ITEMFLAG_EQUIPPED;
	
	if(get_plr()->inventory[which].flags & ITEMFLAG_CURSED)
	{
		if(plural)
			message(gettext("They weld themselves to your %s!"), where);
		else
			message(gettext("It welds itself to your %s!"), where);
	}
}
//}}}
//{{{
void ready_ammo(int which)
{
	ready_item(which, 0, "You ready the %s.", gettext("quiver"));
}
//}}}
//{{{
void ready_weapon(int which)
{
	ready_item(which, 0, "You wield the %s.", gettext("hand"));
}
//}}}
//{{{
void ready_armor(int which)
{
	ready_item(which, 0, "You put on the %s.", gettext("body"));
}
//}}}
//{{{
void ready_helmet(int which)
{
	ready_item(which, 0, "You put on the %s.", gettext("head"));
}
//}}}
//{{{
void ready_lantern(int which)
{
	ready_item(which, 0, "You light the %s.", gettext("hand"));
}
//}}}
//{{{
void ready_torch(int which)
{
	ready_item(which, 0, "You light the %s.", gettext("hand"));
}
//}}}
//{{{
void ready_shield(int which)
{
	ready_item(which, 0, "You ready the %s.", gettext("hand"));
}
//}}}
//{{{
void ready_gloves(int which)
{
	ready_item(which, 1, "You put on the %s.", gettext("hands"));
}
//}}}
//{{{
void ready_boots(int which)
{
	ready_item(which, 1, "You put on the %s.", gettext("feet"));
}
//}}}
//{{{
void ready_ring(int which)
{
	ready_item(which, 0, "You put on the %s.", gettext("finger"));
}
//}}}
//{{{
void ready_amulet(int which)
{
	ready_item(which, 0, "You put on the %s.", gettext("neck"));
}
//}}}

//{{{
void ready_dwarfish_mithril(int which)
{
	struct tile *t;
#ifdef ALLOWDEBUG
	if(get_w()->debug_mode)
	{
		ready_armor(which);
	} else {
#endif
		message(gettext("It's too small."));
		t = &get_w()->t[get_plr()->y][get_plr()->x];
		if(t->type == TILE_SHOPFLOOR && t->special == 7)
			message(gettext("The shopkeeper says \"sorry, no returns\"."));
#ifdef ALLOWDEBUG
	}
#endif
}
//}}}
//{{{
void ready_shining_armor(int which)
{
	ready_armor(which);
	if(get_w()->plr.class == CLASS_FIGHTER)
	{
		message("You are a knight in shining armor.");
		become_knight();
	}
}
//}}}
//{{{
void ready_boots_ice(int which)
{
	ready_boots(which);
	message(gettext("These boots are quite slippery."));
}
//}}}
//{{{
void ready_cloak_invuln(int which)
{
	ready_armor(which);
	message(gettext("You feel well protected."));
}
//}}}
//{{{
void ready_ring_protection(int which)
{
	ready_ring(which);
	message(gettext("You are surrounded by a shimmering haze."));
}
//}}}
//{{{
void ready_ring_illumination(int which)
{
	ready_ring(which);
	message(gettext("It starts to glow brightly."));
}
//}}}
//{{{
void ready_ring_detectinvis(int which)
{
	ready_ring(which);
	message(gettext("Your eyes tingle."));
}
//}}}
//{{{
void ready_ring_hunger(int which)
{
	ready_ring(which);
	message(gettext("Your feel your metabolism speed up."));
}
//}}}
//{{{
void ready_ring_teleportation(int which)
{
	get_plr()->inventory[which].stacksize -= 1;
	spell_teleport();
	if(get_plr()->inventory[which].stacksize == 0)
	{
		message(gettext("The ring's magic fades away."));
		get_plr()->inventory[which].type = ITEM_RING_PLAIN;
	}
}
//}}}
//{{{
void ready_ring_timedilation(int which)
{
	ready_ring(which);
	message(gettext("Everything around you moves in slow motion."));
}
//}}}
//{{{
void ready_amulet_slow_digestion(int which)
{
	ready_amulet(which);
	message(gettext("You feel your metabolism slow down."));
}
//}}}
//{{{
void ready_amulet_brilliance(int which)
{
	ready_amulet(which);
	message(gettext("It starts to glow brightly."));
}
//}}}
//{{{
void ready_amulet_speed(int which)
{
	ready_amulet(which);
	message(gettext("Time slows down around you."));
}
//}}}
//{{{
void ready_amulet_regeneration(int which)
{
	ready_amulet(which);
	message(gettext("You feel your metabolism speed up."));
}
//}}}
//{{{
void ready_amulet_telekinesis(int which)
{
	ready_amulet(which);
	message(gettext("You feel can move projectiles with your mind."));
}
//}}}

//{{{
int burn_cloak_invuln(int which)
{
	int remaining;
	
	if(!(get_plr()->inventory[which].flags & ITEMFLAG_EQUIPPED))
		return 0;
	
	get_plr()->inventory[which].stacksize -= 1;
	remaining = get_plr()->inventory[which].stacksize;
	
	if(remaining == 10)
		message(gettext("The power of your cloak is almost gone."));
	else if(remaining <= 0) {
		message(gettext("Your feel vulnerable."));
		get_plr()->inventory[which].type = ITEM_ARMR_CLOAK;
		update_player();
	}
	else if((remaining % 10) == 0)
		message(gettext("The power of your cloak is fading."));
	
	return 0;
}
//}}}
//{{{
int burn_ring_timedilation(int which)
{
	int remaining;
	
	if(!(get_plr()->inventory[which].flags & ITEMFLAG_EQUIPPED))
		return 0;
	
	get_plr()->inventory[which].stacksize -= 1;
	remaining = get_plr()->inventory[which].stacksize;
	
	if(remaining == 5)
		message(gettext("The power of your ring is almost gone."));
	else if(remaining <= 0) {
		message(gettext("Your surroundings seem to speed up."));
		get_plr()->inventory[which].type = ITEM_RING_PLAIN;
		update_player();
	}
	else if((remaining % 5) == 0)
		message(gettext("The power of your ring is fading."));
	
	return 0;
}
//}}}
//{{{
int burn_torch(int which)
{
	int remaining;
	
	if(!(get_plr()->inventory[which].flags & ITEMFLAG_EQUIPPED))
		return 0;
	
	get_plr()->inventory[which].stacksize -= 1;
	remaining = get_plr()->inventory[which].stacksize;
	
	if(remaining == 450)
	{
		message(gettext("Your torch is running low."));
	}
	else if(remaining == 25)
	{
		message(gettext("Your torch seems about to go out."));
	}
	else if(remaining <= 0)
	{
		message(gettext("Your torch burns out."));
		get_plr()->inventory[which].type = 0;
		update_player();
	}
	
	return 0;
}
//}}}

//{{{
int item_marked(int which)
{
	if(get_plr()->inventory[which].flags & ITEMFLAG_DEPLETE)
		return 1;
	else
		return 0;
}
//}}}
//{{{
void mark_item(int which)
{
	if(!item_marked(which))
		get_plr()->inventory[which].flags |= ITEMFLAG_DEPLETE;
}
//}}}
//{{{
void unmark_item(int which)
{
	get_plr()->inventory[which].flags ^= ITEMFLAG_DEPLETE;
}
//}}}
//{{{
void give_item_type(int type, int qty, int plus)
{
	char buf[64]; //HACKHACK - workaround for inability to put structs on the
	              // stack directly
	
	struct item *itm = buf;
	
	itm->type = type; itm->next = 0; itm->stacksize = qty;
	itm->flags = 0; itm->plus = plus; itm->hotkey = 0; itm->rustiness = 0;
	
	if( give_item(itm, 1) == 0 )
		place_item(itm, get_w()->plr.x, get_w()->plr.y);
}
//}}}
//{{{
void drain_item(int which)
{
	if(item_marked(which))
		unmark_item(which);
	
	get_plr()->inventory[which].stacksize -= 1;
	if(get_plr()->inventory[which].stacksize == 0)
		get_plr()->inventory[which].type = 0;
}
//}}}
//{{{
void destroy_item(int which)
{
	if(item_marked(which))
		unmark_item(which);
	get_plr()->inventory[which].type = 0;
}
//}}}
//{{{
int player_confused(void)
{
	if(get_plr()->extrinsic[STAT_FLAGS] & STAT_FLAG_CONFUSED)
		return 1;
	else
		return 0;
}
//}}}

//{{{
int potion_use(int which)
{
	mark_item(which);
	return 1;
}
//}}}
//{{{
int potion_done(int which)
{
	if(item_marked(which)) {
		drain_item(which);
		give_item_type(ITEM_POTION_BOTTLE, 1, 0);
		timepass(1);
		return 1;
	} else {
		timepass(1);
		return 0;
	}
}
//}}}
//{{{
int wand_zap(int which)
{
	if(get_plr()->inventory[which].stacksize == 0) {
		message(gettext("Nothing happens."));
		return 0;
	}
	mark_item(which);
	return 1;
}
//}}}
//{{{
int wand_done(int which)
{
	if(item_marked(which))
	{
		unmark_item(which);
		get_plr()->inventory[which].stacksize -= 1;
		timepass(1);
		return 1;
	} else {
		return 0;
	}
}
//}}}
//{{{
void wand_aim(char *dir)
{
	if(player_confused()) {
		message(gettext("Whoops..."));
		dir[0] = random(2, 0) - 1;
		dir[1] = random(2, 0) - 1;
	} else {
		prompt_dir(gettext("In what direction?"), dir);
	}
}
//}}}
//{{{
int scroll_use(int which)
{
	if(player_confused()) {
		message(gettext("You are too dazed to read."));
		return 0;
	} else {
		mark_item(which);
		return 1;
	}
}
//}}}
//{{{
int scroll_done(int which)
{
	if(item_marked(which)) {
		message(gettext("The scroll disappears."));
		drain_item(which);
		timepass(1);
		return 1;
	} else {
		return 0;
	}
}
//}}}

//{{{
int potion_empty(int which)
{
	struct tile *current_tile = &get_w()->t[get_w()->plr.y][get_w()->plr.x];
	int give_type = ITEM_POTION_BOTTLE;
	int fountain_type = current_tile->special >> 4;
	int fountain_charge = current_tile->special & 15;
	
	if( current_tile->type == TILE_FOUNTAIN )
	{
		if( prompt(gettext("Fill it from the fountain?")) )
		{
			if(fountain_charge == 0)
				give_type = ITEM_POTION_WATER;
			else if(fountain_type == FOUNTAIN_HEALING)
				give_type = ITEM_POTION_WATER_HEAL;
			else if(fountain_type == FOUNTAIN_MANA)
				give_type = ITEM_POTION_WATER_MANA;
			else if(fountain_type == FOUNTAIN_POISON)
				give_type = ITEM_POTION_WATER_POISON;
			else if(fountain_type == FOUNTAIN_HALLUCINOGEN)
				give_type = ITEM_POTION_WATER_HALLUCINOGEN;
			else if(fountain_type == FOUNTAIN_RESTORE)
				give_type = ITEM_POTION_WATER_RESTORE;
			else if(fountain_type == FOUNTAIN_NUMB)
				give_type = ITEM_POTION_NUMBNESS;
			else if(fountain_type == FOUNTAIN_ELEMENTAL) {
				message(gettext("The water suddenly comes to life!"));
				create_companion(LINK_WATER_ELEMENTAL);
				dry_fountain(get_plr()->x, get_plr()->y);
				return 1;
			}
			message(gettext("You fill a bottle with water from the fountain."));
			drain_fountain(get_w()->plr.x, get_w()->plr.y);
			drain_item(which);
			give_item_type(give_type, 1, 0);
			timepass(1);
		}
	} else {
		message(gettext("It's empty, and you can't refill it here."));
	}
	
	return 1;
}
//}}}
//{{{
int potion_water(int which)
{
	if(potion_use(which)) {
		message(gettext("The water is tasteless."));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_water_mana(int which)
{
	if(potion_use(which)) {
		message(gettext("The water recharges you."));
		get_plr()->pps += random(15, 10);
		if(get_plr()->pps > get_plr()->pps_max)
			get_plr()->pps = get_plr()->pps_max;
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_water_poison(int which)
{
	if(potion_use(which))
	{
		if(get_plr()->extrinsic[STAT_FLAGS] & STAT_FLAG_RESIST_POISON)
		{
			message(gettext("The water is dirty."));
		} else {
			message(gettext("Yurgh! The water is vile!"));
			plr_takedamage(random(10, 6), gettext("Drank poison."));
		}
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_water_hallucinogen(int which)
{
	if(potion_use(which)) {
		message(gettext("Oh wow! Everything looks cosmic now!"));
		hallucinate(random(75,50));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_water_restore(int which)
{
	int i;
	int ret=0;
	
	if(potion_use(which)) {
		for(i=0; i<NUM_BASE_STATS; i++)
			if(plr_restore_stat(i, 1))
				ret=1;
		if(!ret)
			message(gettext("The water is cold."));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_heal(int which)
{
	if(potion_use(which)) {
		message(gettext("You feel better."));
		plr_heal(random(20,10));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_extra_heal(int which)
{
	if(potion_use(which)) {
		message(gettext("You feel much better."));
		plr_heal(random(70,35));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_full_heal(int which)
{
	if(potion_use(which)) {
		message(gettext("You feel much better."));
		plr_heal(10000);
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_gain_strength(int which)
{
	if(potion_use(which)) {
		plr_restore_stat(STAT_STRENGTH, 20);
		plr_mod_stat(STAT_STRENGTH, random(2,1));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_gain_dexterity(int which)
{
	if(potion_use(which)) {
		plr_restore_stat(STAT_DEXTERITY, 20);
		plr_mod_stat(STAT_DEXTERITY, random(2,1));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_gain_toughness(int which)
{
	if(potion_use(which)) {
		plr_restore_stat(STAT_TOUGHNESS, 20);
		plr_mod_stat(STAT_TOUGHNESS, random(2,1));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_gain_mana(int which)
{
	if(potion_use(which)) {
		plr_restore_stat(STAT_MANA, 20);
		plr_mod_stat(STAT_MANA, random(2,1));
		get_plr()->pps = get_plr()->pps_max;
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_gain_willpower(int which)
{
	if(potion_use(which)) {
		plr_restore_stat(STAT_WILLPOWER, 20);
		plr_mod_stat(STAT_WILLPOWER, random(2,1));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_restore_ability(int which)
{
	int i;
	int ret=0;
	
	if(potion_use(which))
	{
		for(i=0; i<NUM_BASE_STATS; i++)
			if(plr_restore_stat(i, 4))
				ret=1;
		if(!ret)
		{
			message(gettext("Nothing happens."));
			potion_done(which);
			return 0;
		}
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_detect_objects(int which)
{
	int i;
	int ii;
	
	if(potion_use(which)) {
		for(i=0; i<MAPSIZE_Y; i++)
			for(ii=0; ii<MAPSIZE_X; ii++)
				if( get_w()->t[i][ii].flags & TFLAG_ITEM ) {
					get_w()->t[i][ii].flags |= TFLAG_EXPLORED;
					draw_tile(ii, i);
				}
		
		message(gettext("You sense the presence of objects."));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_sickness(int which)
{
	if(potion_use(which)) {
		message(gettext("This stuff tastes like poison."));
		if(get_plr()->extrinsic[STAT_FLAGS] & STAT_FLAG_RESIST_POISON)
			message(gettext("It doesn't seem to affect you."));
		else
			plr_mod_stat(0, -random(5,1));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_confuse(int which)
{
	if(potion_use(which)) {
		message(gettext("You are confused!"));
		confuse(random(40,15));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_hallucination(int which)
{
	if(potion_use(which)) {
		message(gettext("Oh wow! Everything looks cosmic now!"));
		hallucinate(random(150,100));
	}
	return potion_done(which);
}
//}}}
//{{{
int potion_numbness(int which)
{
	if(potion_use(which)) {
		if(get_plr()->hps*4 < get_plr()->hps_max)
			message(gettext("You lose all feeling and the pain disappears."));
		else
			message(gettext("You lose all feeling in your body."));
		numb(120);
	}
	return potion_done(which);
}
//}}}

//{{{
void potion_hit_heal(int monst)
{
	message(gettext("The %s looks better."), monstname(monst));
	monst_heal(monst, random(20,10));
}
//}}}
//{{{
void potion_hit_extra_heal(int monst)
{
	message(gettext("The %s looks much better."), monstname(monst));
	monst_heal(monst, random(70,35));
}
//}}}
//{{{
void potion_hit_full_heal(int monst)
{
	message(gettext("The %s looks completely healed."), monstname(monst));
	monst_heal(monst, 1000);
}
//}}}
//{{{
void potion_hit_sickness(int monst)
{
	message(gettext("The %s looks weaker."), monstname(monst));
	monst_takedamage(monst, 25, 10);
}
//}}}
//{{{
void potion_hit_confuse(int monst)
{
	confuse_monster(monst);
}
//}}}

//{{{
int scroll_blank(int which)
{
	if(scroll_use(which)) {
		message(gettext("This scroll is completely blank."));
	}
	timepass(1);
	return 1;
}
//}}}
//{{{
int scroll_teleport(int which)
{
	if(scroll_use(which)) {
		spell_teleport();
	}
	return scroll_done(which);
}
//}}}
//{{{
int scroll_identify(int which)
{
	int i;
	int n;
	
	if(scroll_use(which)) {
		n = random(5, 3);
		message(gettext("This is a scroll of identify."));
		UI_Menu_Set_Persist(1);
		for(i=0; i<n; i++)
			if(!identify())
				break;
		UI_Menu_Set_Persist(0);
	}
	return scroll_done(which);
}
//}}}
//{{{
int scroll_magic_map(int which)
{
	int ii;
	int jj;
	
	if(scroll_use(which)) {
		for(ii=0; ii<MAPSIZE_Y; ii++)
			for(jj=0; jj<MAPSIZE_X; jj++) {
				get_w()->t[ii][jj].flags |= TFLAG_EXPLORED;
				draw_tile(jj, ii);
			}
		
		message(gettext("A map forms in your mind."));
	}
	return scroll_done(which);
}
//}}}
//{{{
int scroll_createmonsters(int which)
{
	int i;
	
	if(scroll_use(which)) {
		message(gettext("Monsters appear out of nowhere!"));
		for(i=0; i<random(8,6); i++)
		{
			addmonster(&(get_w()->current_map->monstertab),
					   get_plr()->x, get_plr()->y);
		}
	}
	return scroll_done(which);
}
//}}}
//{{{
int scroll_uncurse(int which)
{
	if(scroll_use(which)) {
		message(gettext("You feel like someone is helping you."));
		removecurses();
	}
	return scroll_done(which);
}
//}}}
//{{{
int scroll_enchanting(int which)
{
	if(scroll_use(which)) {
		enchant_item();
	}
	return scroll_done(which);
}
//}}}

//{{{
int get_player_x(void)
{
	return get_plr()->x;
}
//}}}
//{{{
int get_player_y(void)
{
	return get_plr()->y;
}
//}}}

//{{{
void satiate(int amt)
{
	get_plr()->satiation += amt;
}
//}}}
//{{{
void plr_heal(int amt)
{
	get_plr()->hps += amt;
	if(get_plr()->hps > get_plr()->hps_max)
		get_plr()->hps = get_plr()->hps_max;
}
//}}}

//{{{
int food_ration(int which)
{
	if(get_plr()->satiation >= 2400) {
		message(gettext("You aren't hungry."));
	}
	else
	{
		if(random(1,0)) {
			message(gettext("Tastes good."));
			satiate(8500);
		} else {
			message(gettext("Blech! Rotten food!"));
			satiate(8000);
		}
		drain_item(which);
		timepass(1);
	}
	return 1;
}
//}}}
//{{{
int tool_pickaxe(int which)
{
	char dir[2];
	int x1; int y1; int x2; int y2;
	int target_type;
	int easy_dig = 0;
	int t;
	prompt_dir(gettext("In what direction?"), dir);
	x1 = get_plr()->x + dir[0];
	y1 = get_plr()->y + dir[1];
	x2 = x1 + dir[0];
	y2 = y1 + dir[1];
	
	if(get_w()->current_map->flags & MAPFLAG_EASYDIGGING)
		easy_dig = 1;
	
	target_type = get_w()->t[y1][x1].type;
	if(target_type == TILE_CDOOR || target_type == TILE_SDOOR)
	{
		message(gettext("You tear down the door."));
		get_w()->t[y1][x1].type = TILE_FLOOR;
		draw_tile(x1, y1);
		calc_light();
	}
	else if(target_type == TILE_WALL)
	{
		target_type = get_w()->t[y2][x2].type;
		if(easy_dig || target_type == TILE_FLOOR || target_type == TILE_SMOKE ||
			target_type == TILE_SPIDERWEB)
		{
			message(gettext("You start digging."));
			for(t=0; t<7; t++)
			{
				get_w()->interrupt = 0;
				if(get_w()->interrupt) {
					message(gettext("You are interrupted."));
					return 1;
				}
			}
			message(gettext("You knock down the wall."));
			get_w()->t[y1][x1].type = TILE_FLOOR;
			draw_tile(x1, y1);
			calc_light();
		}
		else
		{
			message(gettext("The wall is too hard to dig in."));
		}
	}
	else if(target_type == TILE_WALL_UNDIGGABLE || target_type == TILE_LDOOR)
	{
		message(gettext("The wall is too hard to dig in."));
	}
	else
	{
		message(gettext("You swing at empty air."));
	}
	return 1;
}
//}}}

//{{{
//
// (Significance of these return values is set in tiles.c)
//
char boltchar(int dx, int dy)
{
	if(dy==0)
		return 11;
	else if(dx==0)
		return 12;
	else if(dx==dy)
		return 13;
	else
		return 14;
}
//}}}
//{{{
void trace_path(int x, int y, int dir_x, int dir_y, int distance, int *ret)
{
	while(distance > 0)
	{
		x += dir_x;
		y += dir_y;
		if( tile_is_occupied(x, y) || !tile_is_passable(x, y) )
			break;
		distance--;
	}
	ret[0] = x;
	ret[1] = y;
}
//}}}

void bolt(int x, int y, int dir_x, int dir_y, int distance);
void chain_lightning(int x, int y, int dir_x, int dir_y, int arcs);
void fireball(int x, int y, int dir_x, int dir_y, int distance);
void dig_ray(int x, int y, int dir_x, int dir_y, int distance);
int secretdoordetect(void);

//{{{
int wand_nothing(int which)
{
	if(wand_zap(which)) {
		message(gettext("Nothing happens."));
	}
	return wand_done(which);
}
//}}}
//{{{
int wand_striking(int which)
{
	char dir[2];
	if(wand_zap(which)) {
		wand_aim(dir);
		bolt(get_player_x(), get_player_y(), dir[0], dir[1], 7);
	}
	return wand_done(which);
}
//}}}
//{{{
int wand_lightning(int which)
{
	char dir[2];
	if(wand_zap(which)) {
		wand_aim(dir);
		chain_lightning(get_player_x(), get_player_y(), dir[0], dir[1], 3);
	}
	return wand_done(which);
}
//}}}
//{{{
int wand_fire(int which)
{
	char dir[2];
	if(wand_zap(which)) {
		wand_aim(dir);
		fireball(get_player_x(), get_player_y(), dir[0], dir[1], 10);
	}
	return wand_done(which);
}
//}}}
//{{{
int wand_light(int which)
{
	if(wand_zap(which)) {
		message(gettext("There is a sudden flash of light!"));
		illuminate(get_player_x(), get_player_y(), 36);
		calc_light();
	}
	return wand_done(which);
}
//}}}
//{{{
int wand_digging(int which)
{
	char dir[2];
	if(wand_zap(which)) {
		wand_aim(dir);
		dig_ray(get_player_x(), get_player_y(), dir[0], dir[1], 10);
	}
	return wand_done(which);
}
//}}}
//{{{
int wand_detect(int which)
{
	if(wand_zap(which)) {
		message(gettext("Your eyes tingle."));
		detect_invisible(30);
		secretdoordetect();
	}
	return wand_done(which);
}
//}}}
//{{{
int wand_teleportation(int which)
{
	char dir[2];
	int target_coords[2];
	int monst;
	int ret = 0;
	int x; int y;
	
	if(wand_zap(which)) {
		wand_aim(dir);
		if(dir[0] == 0 && dir[1] == 0) {
			spell_teleport();
			ret = 1;
		} else
		{
			trace_path(
				get_plr()->x, get_plr()->y,
				dir[0], dir[1],
				8, target_coords);
			monst = monstbytile(target_coords[0], target_coords[1]);
			if(monst >= 0)
			{
				do
				{
					x = random(MAPSIZE_X-2, 1);
					y = random(MAPSIZE_Y-2, 1);
				} while( !(get_w()->tiledescs[get_w()->t[y][x].type].passable)
					|| get_w()->t[y][x].flags & TFLAG_OCCUPIED );
				message(gettext("The %s disappears!"), monstname(monst));
				monstmoveto(monst, x, y);
				ret = 1;
			}
		}
	}
	wand_done(which);
	return ret;
}
//}}}

//{{{
void bolt(int x, int y, int dir_x, int dir_y, int distance)
{
	char rayTile;
	
	rayTile = boltchar(dir_x, dir_y);
	
	for(; distance>0; distance--)
	{
		x += dir_x;
		y += dir_y;
		if(attack_tile(x, y, gettext("The bolt hits %s!"), gettext("Killed by a bolt"), random(14, 7)))
		{
			UI_TF_DrawEffect(x, y, '*');
			delay();
			break;
		}
		if( !tile_is_transparent(x, y) && !tile_is_passable(x, y) )
			break;
		UI_TF_DrawEffect(x, y, rayTile);
		delay();
	}
	UI_TF_ClearEffects();
}
//}}}
//{{{
void chain_lightning(int x, int y, int dir_x, int dir_y, int arcs)
{
	char rayTile;
	int xi;
	int yi;
	int num_paths=0;
	int path_x;
	int path_y;
	int target_coords[2];
	
	rayTile = boltchar(dir_x, dir_y);
	
	while(1)
	{
		x += dir_x;
		y += dir_y;
		if(attack_tile(x, y, gettext("The lightning bolt hits %s!"),
		      gettext("Killed by a bolt of a lightning"), random(18, 12)) )
		{
			UI_TF_DrawEffect(x, y, '*');
			delay();
			if(arcs>0)
			{
				for(yi=-1; yi<=1; yi++)
					for(xi=-1; xi<=1; xi++)
					{
						if(xi==0 && yi==0)
							continue;
						if(xi==-dir_x && yi==-dir_y)
							continue;
						trace_path(x, y, xi, yi, 6, target_coords);
						if(monstbytile(target_coords[0], target_coords[1])!=-1)
						{
							if(num_paths==0 || random(num_paths,0)==0) {
								path_x = xi;
								path_y = yi;
							}
							num_paths++;
						}
					}
				if(num_paths > 0)
				{
					message(gettext("The lightning arcs!"));
					chain_lightning(x, y, path_x, path_y, arcs-1);
					break;
				}
			}
			UI_TF_ClearEffects();
			break;
		}
		else if( !tile_is_transparent(x, y) && !tile_is_passable(x, y) )
		{
			UI_TF_ClearEffects();
			break;
		}
		else
		{
			UI_TF_DrawEffect(x, y, rayTile);
			delay();
		}
	}
}
//}}}
//{{{
void fireball(int x, int y, int dir_x, int dir_y, int distance)
{
	char rayTile;
	int xi;
	int yi;
	
	rayTile = boltchar(dir_x, dir_y);
	
	for(; distance>0; distance--)
	{
		x += dir_x;
		y += dir_y;
		if( !tile_is_transparent(x, y) && !tile_is_passable(x, y) )
		{
			x -= dir_x;
			y -= dir_y;
			break;
		}
		if( tile_is_occupied(x, y) )
			break;
		UI_TF_DrawEffect(x, y, rayTile);
		delay();
	}
	
	for(yi=y-1; yi<=y+1; yi++)
	for(xi=x-1; xi<=x+1; xi++)
	{
		if( !tile_is_passable(x, y) )
			continue;
		
		attack_tile(xi, yi, gettext("This fireball hits %s!"), gettext("Killed by a fireball"), random(31, 22));
		UI_TF_DrawEffect(xi, yi, '*');
	}
	delay();
	delay();
	
	UI_TF_ClearEffects();
}
//}}}
//{{{
void dig_ray(int x, int y, int dir_x, int dir_y, int distance)
{
	int tt;
	
	while(distance)
	{
		x += dir_x;
		y += dir_y;
		
		tt = get_w()->t[y][x].type;
		
		if(tt == TILE_WALL_UNDIGGABLE) {
			break;
		} else if(tt == TILE_CDOOR || tt == TILE_LDOOR) {
			message(gettext("The door is razed!"));
			get_w()->t[y][x].type = TILE_FLOOR;
			draw_tile(x, y);
		} else if(tt == TILE_WALL || tt == TILE_SDOOR || tt == TILE_SPIDERWEB) {
			get_w()->t[y][x].type = TILE_FLOOR;
			draw_tile(x, y);
		}
		
		distance--;
	}
	
	calc_light();
}
//}}}
//{{{
int secretdoordetect(void)
{
	int x;
	int y;
	int ret=0;
	
	for(y=0; y<MAPSIZE_Y; y++)
		for(x=0; x<MAPSIZE_X; x++)
		{
			if(!(get_w()->t[y][x].flags & TFLAG_LIT))
				continue;

			if(get_w()->t[y][x].type == TILE_SDOOR)
			{
				message(gettext("You spot a hidden door!"));
				get_w()->t[y][x].type = TILE_CDOOR;
				draw_tile(x, y);
				ret=1;
			}
			if(get_w()->t[y][x].flags & TFLAG_HIDETRAP)
			{
				message(gettext("You notice a trap!"));
				get_w()->t[y][x].flags &= ~TFLAG_HIDETRAP;
				draw_tile(x, y);
				ret=1;
			}
		}
	
	return ret;
}
//}}}

//{{{
int use_key(int which)
{
	int xi; int yi; int ii;
	struct itemdesc *correct_key;
	int fits = 0;
	struct spec_descriptor *specs = &(get_w()->current_map->ext);
	
	// Check whether the key matches the level
	for(ii=0; ii<get_w()->current_map->numspecial; ii++)
	{
		if(specs[ii].type == MAPSPEC_KEY) {
			correct_key = deref_file_ptr(specs[ii].ext.spec_item);
			if(correct_key->num == get_plr()->inventory[which].type)
				fits = 1;
		}
	}
	
	for(yi=get_plr()->y-1; yi<=get_plr()->y+1; yi++)
	for(xi=get_plr()->x-1; xi<=get_plr()->x+1; xi++)
	{
		if(get_w()->t[yi][xi].type == TILE_LDOOR)
		{
			if(fits) {
				message("The key fits and the door opens.");
				get_w()->t[yi][xi].type = TILE_ODOOR;
				draw_tile(xi, yi);
				calc_light();
			} else {
				message("Your key doesn't fit.");
			}
		}
	}
	
	timepass(1);
	return 1;
}
//}}}

