m4_changequote({@, @})

m4_syscmd({@echo "/* Generated file - Do not edit. */" >"auto/automatic.h"@})

#include "c_functions.m4"
#include "locals.m4"
#include "util.m4"
#include "playerclass.m4"
#include "tiles.m4"
#include "items.m4"
#include "maps.m4"
#include "spells.m4"
#include "inventory.m4"
#include "monsters.m4"
#include "titlescreen.dat"
#include "shops.m4"
#include "data_export.m4"
#include "player.m4"
#define DLL_EXPORT(a,b) export a (PTR_DLLCALL, b);
#include "data_import.m4h"

m4_divert(SEQUENCE_PRIMARY)
export NULL;
link: FUNCTIONSTABLE;
link: TILETABLE;
link: ITEMSTABLE;
link: GENERATEITEM;
link: ITYPE_GOLD_PIECE;
link: PLAYER_STARTING_INVENTORY;
link: SPELLSTABLE;
link: PLAYERCLASSES;
link: STSIZES;
link: STDATA;
link: SHOPDESCS;
link: TITLESCREEN_LIGHT_PLANE;
link: TITLESCREEN_DARK_PLANE;

uint: numItems;
uint: numSpells;
uint: numPlayerClasses;
uint: CLASS_TUTORIAL;
uint: numSTabs;
uint: sTabPos;
uint: numShops;
uint: 0;

link: MAP_START_DLVL1;
link: MAP_TUTORIAL;

link: MISC_LINKS;

splitpoint;

