m4_define({@numSpells@}, 0)

m4_define(SPELL,
 {@m4_divert(SEQUENCE_STRINGS)
  export SPELL_{@@}numSpells;
  string: $2;
  m4_divert(SEQUENCE_TABLES)
  
  link: SPELL_{@@}numSpells;
  uint: numSpells;
  m4_define(SPELL_{@@}$1, numSpells)
  uint: $3;
  uint: $4;
  link: $5; //on learn
  link: $6; //effect
  
  m4_define({@numSpells@}, m4_eval(numSpells+1))
 @})

m4_divert(SEQUENCE_TABLES)
splitpoint; even;
export SPELLSTABLE;
SPELL(BOLT,            gettext("Magic Bolt"),     5,  7,  learn_spell_bolt,           spell_bolt         )
SPELL(LIGHT,           gettext("Light"),          4,  6,  NULL,                       spell_light        )
SPELL(DETECTINVIS,     gettext("Detect invisible"),15,20, NULL,                       spell_detect_invisible )
SPELL(IDENTIFY,        gettext("Identify"),       20, 40, learn_spell_identify,       spell_identify     )
// gather energy

SPELL(SCAREMONSTER,    gettext("Scare monster"),  12, 11, learn_scare_monster,        spell_scaremonster )
SPELL(CONFUSION,       gettext("Confusion"),      15, 25, learn_spell_confusion,      spell_confusion    )
SPELL(LIGHTNING,       gettext("Lightning bolt"), 13, 40, learn_spell_lightning,      spell_lightning    )
// Charging, repulsion

SPELL(ADRENALINE,      gettext("Adrenaline"),     9,  16, NULL,                       spell_adrenaline   )
SPELL(GAINSTRENGTH,    gettext("Gain strength"),  10, 25, NULL,                       spell_gain_strength)
SPELL(HEAL,            gettext("Heal"),           15, 50, NULL,                       spell_heal         )
SPELL(SCAREMONSTER_PRIEST,gettext("Scare monster"),12,30, learn_scare_monster,        spell_scaremonster )

SPELL(BLINK,           gettext("Blink"),          5,  15, NULL,                       spell_blink        )
SPELL(TELEPORT,        gettext("Teleport"),       14, 35, NULL,                       spell_teleport     )
SPELL(REMOVECURSE,     gettext("Remove curse"),   35, 50, NULL,                       spell_removecurse  )
// wall of force, mirror

	// Component: Staff
SPELL(WINDBLAST,       gettext("Windblast"),      20, 50, learn_spell_windblast,      spell_windblast    )
	// Component: Large shield
SPELL(WINDSHIELD,      gettext("Windshield"),     30, 50, learn_spell_windshield,     spell_windshield   )
	// Component: an open flame (torch), which is drained by 20 turns
SPELL(FIREBALL,        gettext("Fireball"),       16, 50, learn_spell_fireball,       spell_fireball     )
SPELL(DIG,             gettext("Dig"),            25, 50, NULL,                       spell_dig          )

SPELL(SHIELD,          gettext("Shield"),         5,  5,  NULL,                       spell_shield       )
SPELL(PURIFY,          gettext("Purify"),         20, 25, NULL,                       spell_purify       )
SPELL(HEAL_PRIEST,     gettext("Heal"),           15, 30, NULL,                       spell_heal         )
SPELL(DIVINE_AID,      gettext("Divine Aid"),     25, 65, NULL,                       spell_divine_aid   )
// turn undead

SPELL(CREATE_SKELETON, gettext("Summon skeleton"),9,  7,  NULL,                       spell_create_skeleton )
SPELL(CREATE_ZOMBIE,   gettext("Summon zombie"),  16, 25, NULL,                       spell_create_zombie )
SPELL(CREATE_MUMMY,    gettext("Summon mummy"),   25, 45, NULL,                       spell_create_mummy  )
SPELL(CREATE_WRAITH,   gettext("Summon wraith"),  40, 65, NULL,                       spell_create_wraith )

SPELL(MEND_BONE,       gettext("Mend bone"),      4,  7,  NULL,                       spell_mend_bone     )
SPELL(REPAIR_ZOMBIE,   gettext("Repair zombie"),  6,  25, NULL,                       spell_repair_zombie )
SPELL(REPAIR_MUMMY,    gettext("Repair mummy"),   8,  45, NULL,                       spell_repair_mummy  )
SPELL(SHADOW_HEALING,  gettext("Shadow healing"), 12, 65, NULL,                       spell_shadow_healing )

BEGIN_SHUFFLETAB(SPELLBOOKNAMES)
  STENTRYITEM(LRED,     gettext("red book"))
  STENTRYITEM(LWHITE,   gettext("white book"))
  STENTRYITEM(LBLUE,    gettext("blue book"))
  STENTRYITEM(LYELLOW,  gettext("yellow book"))
  STENTRYITEM(LRED,     gettext("orange book"))
  STENTRYITEM(MAGENTA,  gettext("purple book"))
  STENTRYITEM(WHITE,    gettext("gray book"))
  STENTRYITEM(LBLACK,   gettext("black book"))
  STENTRYITEM(LGREEN,   gettext("green book"))
  STENTRYITEM(LCYAN,    gettext("cyan book"))
  STENTRYITEM(MAGENTA,  gettext("mauve book"))
  STENTRYITEM(LMAGENTA, gettext("pink book"))
  STENTRYITEM(YELLOW,   gettext("brown book"))
END_SHUFFLETAB()

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      C   Identifier                Color     Name                                           UnID Name            Flags                 Stack  Weight Value   Category    Slot  Num   Properties                           //
//{{{
ITEM( '+',  BOOK_TUTORIAL,            0,
      {@String(gettext("book of spells"))@},
      NULL,
      FLAGS_BOOK,           1,     20,    100,    CAT_BOOK,   -1,
	1,
	{@USEEFFECT(tutorial_spell_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_FADED,               WHITE,
      {@String(gettext("faded book"))@},
      NULL,
      FLAGS_BOOK,           1,     20,    10,     CAT_BOOK,   -1,
	1,
	{@USEEFFECT(faded_book)@})
//}}}
// Wizardry
//{{{
ITEM( '+',  BOOK_BASIC_SPELLS,        0,
      {@String(gettext("book of basic spells"))@},
      SPELLBOOKNAMES_1,
      FLAGS_SPELLBOOK,      20,    20,    400,    CAT_BOOK,   -1,
	1,
	{@USEEFFECT(basic_spell_book)       @})
//}}}
//{{{
ITEM( '+',  BOOK_LIFE_SPELLS,         0,
      {@String(gettext("book of life spells"))@},
      SPELLBOOKNAMES_2,
      FLAGS_SPELLBOOK,      20,    20,    800,    CAT_BOOK,   -1,
	1,
	{@USEEFFECT(life_spell_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_MISC_SPELLS,         0,
      {@String(gettext("book of miscellaneous spells"))@},
      SPELLBOOKNAMES_3,
      FLAGS_SPELLBOOK,      20,    20,    800,    CAT_BOOK,   -1,
	1,
	{@USEEFFECT(misc_spell_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_CHANNELING_SPELLS,   0,
      {@String(gettext("book of channeling spells"))@},
      SPELLBOOKNAMES_4,
      FLAGS_SPELLBOOK,      20,    20,    1200,   CAT_BOOK,   -1,
      1,
      {@USEEFFECT(channeling_spell_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_ELEMENTAL_SPELLS,    0,
      {@String(gettext("book of elemental spells"))@},
      SPELLBOOKNAMES_5,
      FLAGS_SPELLBOOK,      20,    20,    2000,   CAT_BOOK,   -1,
      1,
      {@USEEFFECT(elemental_spell_book)@})
//}}}
// Prayers
//{{{
ITEM( '+',  BOOK_BASIC_PRAYERS,       0,
      {@String(gettext("book of basic prayers"))@},
      SPELLBOOKNAMES_6,
      FLAGS_SPELLBOOK,      20,    20,    400,    CAT_BOOK,   -1,
      1,
      {@USEEFFECT(basic_prayer_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_BLESSINGS,           0,
      {@String(gettext("book of blessings"))@},
      SPELLBOOKNAMES_7,
      FLAGS_SPELLBOOK,      20,    20,    800,    CAT_BOOK,   -1,
      1,
      {@USEEFFECT(blessings_prayer_book)@})
//}}}
// Necromancy
//{{{
ITEM( '+',  BOOK_ANIMATION,           0,
      {@String(gettext("book of animation spells"))@},
      SPELLBOOKNAMES_8,
      FLAGS_SPELLBOOK,      20,    20,    400,    CAT_BOOK,   -1,
      1,
      {@USEEFFECT(animation_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_REPAIRS,             0,
      {@String(gettext("book of magical repairs"))@},
      SPELLBOOKNAMES_9,
      FLAGS_SPELLBOOK,      20,    20,    800,    CAT_BOOK,   -1,   1,
	  {@USEEFFECT(repairs_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_LICHDOM,             LBLACK,
      {@String(gettext("book of lichdom"))@},
      {@Itemstring(gettext("black tome"))@},
      FLAGS_SPELLBOOK,      20,    20,    0,       CAT_BOOK,   -1,   1,
	  {@USEEFFECT(lichdom_book)@})
//}}}

// Non-spell
//{{{
ITEM( '+',  BOOK_WEAPONRY,            0,
      {@String(gettext("book of weaponry"))@},
      SPELLBOOKNAMES_10,
      FLAGS_BOOK,           1,     20,    400,    CAT_BOOK,   -1,
      1,
      {@USEEFFECT(weaponry_book)@})
//}}}
//{{{
ITEM( '+',  BOOK_GEMOLOGY,            0,
      {@String(gettext("book of gemology"))@},
      SPELLBOOKNAMES_11,
      FLAGS_BOOK,           1,     20,    200,    CAT_BOOK,   -1,
      1,
      {@USEEFFECT(gemology_book)@})
//}}}

BEGIN_JUMPTAB(GENERATE_BOOK, jt_dungeonlevel)
//        Item                           Freq  Level range
  JTENTRY(ITYPE_BOOK_FADED,              6,    range(255,1))
  JTENTRY(ITYPE_BOOK_BASIC_SPELLS,       6,    range(255,1))
  JTENTRY(ITYPE_BOOK_LIFE_SPELLS,        3,    range(255,1))
  JTENTRY(ITYPE_BOOK_MISC_SPELLS,        3,    range(255,1))
  JTENTRY(ITYPE_BOOK_CHANNELING_SPELLS,  3,    range(255,1))
  JTENTRY(ITYPE_BOOK_BASIC_PRAYERS,      6,    range(255,1))
  JTENTRY(ITYPE_BOOK_BLESSINGS,          3,    range(255,1))
  JTENTRY(ITYPE_BOOK_ANIMATION,          6,    range(255,1))
  JTENTRY(ITYPE_BOOK_REPAIRS,            3,    range(255,1))
  JTENTRY(ITYPE_BOOK_WEAPONRY,           3,    range(255,1))
  JTENTRY(ITYPE_BOOK_GEMOLOGY,           3,    range(255,1))
END_JUMPTAB()

//{{{
void faded_book(int which)
{
	message(gettext("The pages of this book are too faded to be read anymore."));
}
//}}}
//{{{
void fade_book(int which)
{
	get_plr()->inventory[which].stacksize -= 1;
	
	if(get_plr()->inventory[which].stacksize == 0)
	{
		message(gettext("The spellbook fades."));
		get_plr()->inventory[which].type = ITEM_BOOK_FADED;
		get_plr()->inventory[which].stacksize = 1;
	}
}
//}}}

//{{{
int tutorial_spell_book(void)
{
	study_book(4, SPELLTYPE_ARCANE,
		SPELL_BOLT,
		SPELL_LIGHT,
		SPELL_CREATE_SKELETON,
		SPELL_BLINK);
	return 1;
}
//}}}

//{{{
int basic_spell_book(int which)
{
	if(study_book(4, SPELLTYPE_ARCANE,
		SPELL_BOLT,
		SPELL_LIGHT,
		SPELL_DETECTINVIS,
		SPELL_IDENTIFY))
			fade_book(which);
	return 1;
}
//}}}
//{{{
int misc_spell_book(int which)
{
	if(study_book(3, SPELLTYPE_ARCANE,
		SPELL_BLINK,
		SPELL_TELEPORT,
		SPELL_REMOVECURSE))
			fade_book(which);
	return 1;
}
//}}}
//{{{
int life_spell_book(int which)
{
	if(study_book(3, SPELLTYPE_ARCANE,
		SPELL_ADRENALINE,
		SPELL_GAINSTRENGTH,
		SPELL_HEAL))
			fade_book(which);
	return 1;
}
//}}}
//{{{
int channeling_spell_book(int which)
{
	if(study_book(4, SPELLTYPE_ARCANE,
		SPELL_BOLT,
		SPELL_SCAREMONSTER,
		SPELL_CONFUSION,
		SPELL_LIGHTNING))
			fade_book(which);
	return 1;
}
//}}}
//{{{
int elemental_spell_book(int which)
{
	if(study_book(3, SPELLTYPE_ARCANE,
		SPELL_WINDBLAST,
//		SPELL_WINDSHIELD,
		SPELL_FIREBALL,
		SPELL_DIG))
			fade_book(which);
	return 1;
}
//}}}

//{{{
int basic_prayer_book(int which)
{
	if(study_book(4, SPELLTYPE_DIVINE,
		SPELL_LIGHT,
		SPELL_SHIELD,
		SPELL_HEAL_PRIEST,
		SPELL_SCAREMONSTER_PRIEST))
			fade_book(which);
	return 1;
}
//}}}
//{{{
int blessings_prayer_book(int which)
{
	if(study_book(4, SPELLTYPE_DIVINE,
		SPELL_PURIFY,
		SPELL_DETECTINVIS,
		SPELL_REMOVECURSE,
		SPELL_DIVINE_AID))
			fade_book(which);
	return 1;
}
//}}}

//{{{
int animation_book(int which)
{
	if(study_book(4, SPELLTYPE_NECROMANCY,
		SPELL_CREATE_SKELETON,
		SPELL_CREATE_ZOMBIE,
		SPELL_CREATE_MUMMY,
		SPELL_CREATE_WRAITH))
			fade_book(which);
	return 1;
}
//}}}
//{{{
int repairs_book(int which)
{
	if(study_book(4, SPELLTYPE_NECROMANCY,
		SPELL_MEND_BONE,
		SPELL_REPAIR_ZOMBIE,
		SPELL_REPAIR_MUMMY,
		SPELL_SHADOW_HEALING))
			fade_book(which);
	return 1;
}
//}}}
//{{{
int lichdom_book(int which)
{
	message(gettext("This book contains a ritual which will turn the caster into a lich."));
	if(get_plr()->class == CLASS_LICH) {
		message(gettext("You no longer need it."));
	} else if(get_plr()->class == CLASS_WIZARD) {
		message(gettext("You can't even begin to understand the details."));
		return 1;
	} else if(get_plr()->class == CLASS_NECROMANCER) {
		if(get_plr()->level < 10) {
			message(gettext("You can't quite comprehend all the details. Perhaps you should revisit this when you are more experienced."));
			return 1;
		}
		if(!prompt(gettext("Do you want to attempt the ritual?"))) {
			return 1;
		}
		message(gettext("If the spell is interrupted, the result may be fatal."));
		if(!prompt(gettext("Are you sure you want to continue?"))) {
			return 1;
		}
		attempt_lich_transformation();
		return 1;
	} else {
		if(prompt(gettext("Burn it?"))) {
			if(!(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_FLAME)){
				message(gettext("You need to get a torch ready."));
			} else {
				message(gettext("It burns nicely. You feel like that was a good thing to do."));
				destroy_item(which);
				boost_max_stat(STAT_WILLPOWER, 1);
			}
		}
	}
}
//}}}

//{{{
// Read a long book
// 'title' is the book's title. 'length' is the book's length in 
// *turns* (about three pages are read in a turn.).
// 'field' corresponds to a flag unique to this title for use as a 
// bookmark.
// Returns 1 if finished reading the book for the first time or zero
// if the book is already read, or reading was interrupted.
int read_long_book(char *title, int length, int field)
{
	int pageno = 0;
	int read = 0;
	
	if( GFLAG(field) == 0 ) {
		message(gettext("This book is titled '%s'."), title);
		if( prompt(gettext("Read it?")) )
			read = 1;
	} else if( GFLAG(field) >= length ) {
		message(gettext("You've already read that book."));
	} else {
		pageno = GFLAG(field)*3 + random(3,1);
		read = 1;
	}
	
	if(read)
	{
		if(pageno > 0)
			message(gettext("You resume reading at page %li."), pageno);
		else
			message(gettext("You start reading."));
		
		get_w()->interrupt = 0;
		do {
			GFLAG(field) += 1;
			timepass(1);
			if(get_w()->interrupt) {
				message(gettext("You are interrupted."));
				break;
			}
		} while(GFLAG(field) < length);
		
		if(GFLAG(field) >= length)
			return 1;
	}
	return 0;
}
//}}}

//{{{
int weaponry_book(int which)
{
	int i;
	if( read_long_book(gettext("Improvisational Armed Fighting"), 100, BOOK_PROGRESS_WEAPONRY) )
	{
		message(gettext("You improve your weapon skills."));
		for(i=1; i<NUM_SKILLS+1; i++)
		{
			if(get_plr()->skill[i] < 3)
				get_plr()->skill[i] += 2;
			else if(get_plr()->skill[i] < 10)
				get_plr()->skill[i] += 1;
			else
				continue;
			get_plr()->skill_marks[i] = 0;
		}
	}
	return 1;
}
//}}}
//{{{
int gemology_book(int which)
{
	int i;
	if( read_long_book(gettext("Gems and Minerals"), 75, BOOK_PROGRESS_GEMOLOGY) )
	{
		message(gettext("You learn how to recognize various types of gems."));
		for(i=ITEM_GEM_DIAMOND; i<=ITEM_GEM_VIOLETGLASS; i++)
			identify_type(i);
	}
	return 1;
}
//}}}

//{{{
void deplete_component(int type, int amt)
{
	int ii;
	int stacksize;
	
	for(ii=0; ii<PLRINVSIZE; ii++)
	{
		if( get_plr()->inventory[ii].type == type )
		{
			stacksize = get_plr()->inventory[ii].stacksize;
			
			if(stacksize > amt) {
				get_plr()->inventory[ii].stacksize = stacksize - amt;
			} else {
				get_plr()->inventory[ii].type = 0;
				update_player();
			}
			break;
		}
	}
}
//}}}
//{{{
int have_component(int type, int amt)
{
	int ii;
	int stacksize;
	
	for(ii=0; ii<PLRINVSIZE; ii++)
	if( get_plr()->inventory[ii].type == type )
	{
		if( get_plr()->inventory[ii].stacksize > amt )
			return 1;
	}
	
	return 0;
}
//}}}
//{{{
int distancesqr(int x1, int y1, int x2, int y2)
{
	int dx = (x1-x2);
	int dy = (y1-y2);
	return dx*dx + dy*dy;
}
//}}}
//{{{
int bound(int n, int min, int max)
{
	if(n<min) return min;
	if(n>max) return max;
	return n;
}
//}}}
//{{{
void invest_energy(int amt)
{
	get_plr()->pps_max_mod -= amt;
	update_player();
}
//}}}
//{{{
void release_energy(int amt)
{
	get_plr()->pps_max_mod += amt;
	update_player();
}
//}}}

//{{{
void spell_bolt(void)
{
	char dir[2];
	
	if(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_STAFF)
	{
		prompt_dir(gettext("In what direction?"), dir);
		bolt( get_player_x(), get_player_y(), dir[0], dir[1], 6 );
	}
	else
	{
		message(gettext("You need a staff ready to cast that spell."));
	}
}
//}}}
//{{{
void spell_light(void)
{
	message(gettext("A lit field surrounds you."));
	illuminate(get_player_x(), get_player_y(), 36);
	calc_light();
}
//}}}
//{{{
void spell_lightning(void)
{
	char dir[2];
	
	if( !(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_STAFF) )
	{
		message(gettext("You need a staff ready to cast that spell."));
	} else if( player_gold() < 2 )
	{
		message(gettext("You need two coins to cast that spell."));
	} else {
		debit_gold(2);
		prompt_dir(gettext("In what direction?"), dir);
		chain_lightning(get_player_x(), get_player_y(), dir[0], dir[1], 3);
	}
}
//}}}
//{{{
void spell_detect_invisible(void)
{
	message(gettext("Your eyes tingle."));
	detect_invisible(30);
	secretdoordetect();
}
//}}}
//{{{
void spell_scaremonster(void)
{
	int x;
	int y;
	int m;
	int stacksize;
	
	if( !(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_SNAKETOOTH) )
	{
		message(gettext("To cast that spell, you need a rattlesnake tooth."));
	}
	else
	{
		deplete_component(ITEM_RATTLESNAKE_TOOTH, 1);
		
		message(gettext("You hear maniacal laughter."));
		
		for(y=get_plr()->y-1; y<=get_plr()->y+1; y++)
		for(x=get_plr()->x-1; x<=get_plr()->x+1; x++)
		{
			m = monstbytile(x, y);
			if(m >= 0)
				scare_monster(m);
		}
	}
}
//}}}
//{{{
void spell_identify(void)
{
	if( !(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_BLANKSCROLL) )
	{
		message(gettext("You need a blank scroll to cast that spell."));
	}
	else
	{
		deplete_component(ITEM_SCROLL_BLANK, 1);
		identify();
	}
}
//}}}
//{{{
void spell_blink(void)
{
	int x = get_w()->plr.x;
	int y = get_w()->plr.y;
	int retries = 0;
	int left = bound(get_w()->plr.x - 6, 0, MAPSIZE_X-1);
	int right = bound(get_w()->plr.x + 6, 0, MAPSIZE_X-1);
	int top = bound(get_w()->plr.y - 6, 0, MAPSIZE_Y-1);
	int bottom = bound(get_w()->plr.y + 6, 0, MAPSIZE_Y-1);
	
	do
	{
		x = random(right, left);
		y = random(bottom, top);
		retries++;
		
		if(retries > 100) // Nowhere to land!
		{
			message(gettext("You feel crowded."));
			break;
		}
		
		if( tile_is_passable(x,y) == 0 ) {
			continue;
		}
		if( tile_is_occupied(x, y) ) {
			continue;
		}
		
		break;
	} while(1);
	
	plr_moveto(x, y, -1);
}
//}}}
//{{{
void spell_teleport(void)
{
	if( get_w()->current_map->flags & MAPFLAG_NOTELEPORT )
		message(gettext("That spell does not work here."));
	else
	{
		message(gettext("Suddenly you stand somewhere else."));
		confuse(5);
		place_player_randomly();
	}
}
//}}}

//{{{
void spell_windblast(void)
{
	char dir[2];
	int target;
	
	if(!(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_STAFF))
		message(gettext("You need a staff ready to cast that spell."));
	else
	{
		wand_aim(dir);
		target = monstbytile( get_plr()->x+dir[0], get_plr()->y+dir[1] );
		if(target==-1) {
			message("The wind dissipates harmlessly.");
		} else {
			mspell_windblast(-1, random(14,10), target);
		}
	}
}
//}}}
//{{{
void spell_windshield(void)
{
	char dir[2];
	if(!(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_SHIELD))
		message(gettext("You need a shield equipped to cast that spell."));
	else
	{
		//TODO
	}
}
//}}}
//{{{
void spell_fireball(void)
{
	char dir[2];
	
	if(!(get_plr()->extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_FLAME))
		message(gettext("You need an open flame to cast that spell."));
	else
	{
		wand_aim(dir);
		fireball(get_player_x(), get_player_y(), dir[0], dir[1], 10);
	}
}
//}}}
//{{{
void spell_dig(void)
{
	char dir[2];
	wand_aim(dir);
	dig_ray(get_player_x(), get_player_y(), dir[0], dir[1], 10);
}
//}}}

//{{{
void spell_purify(void)
{
	int restore_st=0;
	int restore_to=0;
	if(get_plr()->intrinsic[STAT_STRENGTH] < get_plr()->maximum[STAT_STRENGTH])
		restore_st = 1;
	if(get_plr()->intrinsic[STAT_TOUGHNESS] < get_plr()->maximum[STAT_TOUGHNESS])
		restore_to = 1;
	if(restore_st && restore_to)
		message(gettext("You are purified of poison and disease."));
	else if(restore_st)
		message(gettext("You are purified of poison."));
	else if(restore_to)
		message(gettext("You are purified of disease."));
	else
		message(gettext("You are already pure."));
	
	plr_restore_stat(STAT_STRENGTH, 20);
	plr_restore_stat(STAT_TOUGHNESS, 20);
}
//}}}
//{{{
void spell_divine_aid(void)
{
	int d[1]; // HACKHACK: Can't put a proper struct on the stack yet, but
	          // this is the same size so it works the same
	if(GFLAG(HAVE_PET_ANGEL))
	{
		message(gettext("Nothing happens."));
	}
	else
	{
		create_companion(LINK_SUMMON_ANGEL);
		invest_energy(25);
		GFLAG(HAVE_PET_ANGEL) = 1;
		message(gettext("An angel appears by your side!"));
	}
}
//}}}
//{{{
void spell_removecurse(void)
{
	removecurses();
}
//}}}
//{{{
void spell_create_skeleton(void)
{
	create_companion(LINK_SUMMON_SKELETON);
	invest_energy(9);
}
//}}}
//{{{
void spell_create_zombie(void)
{
	create_companion(LINK_SUMMON_ZOMBIE);
	invest_energy(16);
}
//}}}
//{{{
void spell_create_mummy(void)
{
	create_companion(LINK_SUMMON_MUMMY);
	invest_energy(25);
}
//}}}
//{{{
void spell_create_wraith(void)
{
	create_companion(LINK_SUMMON_WRAITH);
	invest_energy(40);
}
//}}}

//{{{
void repair_monst_type(char *type)
{
	char dir[2];
	int distance = 5;
	int dir_x; int dir_y;
	int monstid;
	char *name;
	int x = get_plr()->x;
	int y = get_plr()->y;
	
	prompt_dir(gettext("In what direction"), dir);
	
	dir_x = dir[0];
	dir_y = dir[1];
	
	for(; distance>0; distance--)
	{
		x += dir_x;
		y += dir_y;
		monstid = monstbytile(x,y);
		if(monstid >= 0)
		{
			name = monstname(monstid);
			if( strcmp(name, type) ) {
				message(gettext("The %s is unaffected."), name);
				break;
			}
			monst_heal(monstid, 200);
			message(gettext("The %s looks better."), name);
		}
		if( !tile_is_transparent(x, y) )
			break;
	}

}
//}}}
//{{{
void spell_mend_bone(void)
{
	repair_monst_type(gettext("Skeleton"));
}
//}}}
//{{{
void spell_repair_zombie(void)
{
	repair_monst_type(gettext("Zombie"));
}
//}}}
//{{{
void spell_repair_mummy(void)
{
	repair_monst_type(gettext("Mummy"));
}
//}}}
//{{{
void spell_shadow_healing(void)
{
	repair_monst_type(gettext("Wraith"));
}
//}}}

//{{{
void learn_spell_bolt(void)
{
	message(gettext("To cast that spell, you will need a staff or rod."));
}
//}}}
//{{{
void learn_scare_monster(void)
{
	message(gettext("To cast that spell, you will need a rattlesnake tooth, which will be destroyed by the casting."));
}
//}}}
//{{{
void learn_spell_lightning(void)
{
	message(gettext("To cast that spell, you will need a staff or rod and two coins, which will be destroyed by the casting."));
}
//}}}
//{{{
void learn_spell_confusion(void)
{
	message(gettext("To cast that spell, you will to draw some blood with a dagger."));
}
//}}}
//{{{
void learn_spell_identify(void)
{
	message(gettext("To cast that spell, you will need some paper."));
}
//}}}
//{{{
void learn_spell_windblast(void)
{
	message(gettext("To cast that spell, you will need a staff or rod."));
}
//}}}
//{{{
void learn_spell_windshield(void)
{
	message(gettext("To cast that spell, you must equip a shield."));
}
//}}}
//{{{
void learn_spell_fireball(void)
{
	message(gettext("To cast that spell, you will need an open flame ready."));
}
//}}}

//{{{
void minion_skeleton_die(void)
{
	release_energy(9);
}
//}}}
//{{{
void minion_zombie_die(void)
{
	release_energy(16);
}
//}}}
//{{{
void minion_mummy_die(void)
{
	release_energy(25);
}
//}}}
//{{{
void minion_wraith_die(void)
{
	release_energy(40);
}
//}}}
//{{{
void minion_angel_die(void)
{
	GFLAG(HAVE_PET_ANGEL) = 0;
	release_energy(25);
}
//}}}

