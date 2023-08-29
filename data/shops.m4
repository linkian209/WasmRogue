m4_define(numShops, 0)
//{{{
m4_define(SHOP_TYPE,
 {@m4_divert(SEQUENCE_TABLES)
  m4_define({@numShops@}, m4_eval(numShops+1))
  link: $1;  // Name
  link: $2;  // Shopkeeper
  link: $3;  // Items
 @})
//}}}
//{{{
m4_define(SHOP_NOGEN,
 {@m4_divert(SEQUENCE_TABLES)
  link: $1;  // Name
  link: $2;  // Shopkeeper
  link: $3;  // Items
 @})
//}}}

m4_divert(SEQUENCE_TABLES)
export SHOPDESCS;
SHOP_TYPE({@String(gettext("Beta-Espilon Jewelers"))@},                 MONSTER_SHOPKEEPER,  GENERATE_JEWELRY)
	/* TRANSLATORS: These names are parodies of well-known trademarks.
	 * If you can't find an equivalent trademark to parody, use a generic
	 * name. */
SHOP_TYPE({@String(gettext("Sahara dot Comma Books"))@},                MONSTER_SHOPKEEPER,  GENERATE_PAPER)
SHOP_TYPE({@String(gettext("Ischer's Weapon Shop"))@},                  MONSTER_SHOPKEEPER,  GENERATE_WEAPON)
SHOP_TYPE({@String(gettext("ArmorAll Armory"))@},                       MONSTER_SHOPKEEPER,  GENERATE_ARMOR)
SHOP_TYPE({@String(gettext("Paul's Power Potions"))@},                  MONSTER_SHOPKEEPER,  GENERATE_POTION)
SHOP_TYPE({@String(gettext("Mel's Magics"))@},                          MONSTER_SHOPKEEPER,  GENERATE_MAGIC)
SHOP_TYPE({@String(gettext("Frobozz General Store"))@},                 MONSTER_SHOPKEEPER,  GENERATE_GENERAL)
SHOP_NOGEN({@String(gettext("Minetown Mining Supplies"))@},             MONSTER_SHOPKEEPER,  GENERATE_GENERAL)

BEGIN_JUMPTAB(GENERATE_GENERAL, jt_unconditional)
  JTENTRY(GENERATE_ARMOR,           15,   range(255,1))
  JTENTRY(GENERATE_WEAPON,          12,   range(255,1))
  JTENTRY(GENERATE_POTION,          13,   range(255,1))
  JTENTRY(GENERATE_SCROLL,          14,   range(255,1))
  JTENTRY(GENERATE_FOOD,            10,   range(255,1))
  JTENTRY(GENERATE_AMMO,            9,    range(255,1))
  JTENTRY(GENERATE_BOOK,            7,    range(255,1))
  JTENTRY(GENERATE_WAND,            10,   range(255,1))
  JTENTRY(GENERATE_RING,            7,    range(255,1))
  JTENTRY(GENERATE_AMULET,          3,    range(255,1))
END_JUMPTAB()

BEGIN_JUMPTAB(GENERATE_WEAPONSHOP, jt_unconditional)
  JTENTRY(GENERATE_AMMO,            15,   range(255,1))
  JTENTRY(GENERATE_WEAPON,          85,   range(255,1))
END_JUMPTAB()

BEGIN_JUMPTAB(GENERATE_MAGIC, jt_unconditional)
  JTENTRY(GENERATE_WAND,            30,    range(255,1))
  JTENTRY(GENERATE_POTION,          25,    range(255,1))
  JTENTRY(GENERATE_SCROLL,          20,    range(255,1))
  JTENTRY(GENERATE_BOOK,            19,    range(255,1))
  JTENTRY(GENERATE_RING,            5,     range(255,1))
  JTENTRY(GENERATE_AMULET,          1,     range(255,1))
END_JUMPTAB()

BEGIN_JUMPTAB(GENERATE_JEWELRY, jt_unconditional)
  JTENTRY(GENERATE_VALUABLE_GEM,    40,   range(255,1))
  JTENTRY(GENERATE_RING,            40,   range(255,1))
  JTENTRY(GENERATE_AMULET,          10,   range(255,1))
END_JUMPTAB()

BEGIN_JUMPTAB(GENERATE_PAPER, jt_unconditional)
  JTENTRY(GENERATE_BOOK,            40,   range(255,1))
  JTENTRY(GENERATE_SCROLL,          60,   range(255,1))
END_JUMPTAB()

