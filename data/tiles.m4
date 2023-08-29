
m4_divert(SEQUENCE_TABLES)

export TILETABLE;

m4_define(numTiles, 0)

m4_syscmd({@echo -n >auto/tiles.dat@})

m4_define(TILE,
 {@m4_syscmd(echo "{@#@}define TILE_{@@}$1 numTiles" >>"auto/automatic.h")
  m4_syscmd({@echo "$2"@} numTiles {@>>"auto/tiles.dat"@})
  m4_define(TILE_{@@}$1, numTiles)
  m4_define({@numTiles@}, m4_eval(numTiles+1))
  export $1;
  uchar: $4;
  uchar: $3;
  uchar: $5;
  uchar: $6;
  uchar: $7;
  uchar: $8;
  uchar: $9;
  even;
#ifdef SUPPORT_COLOR
  uchar: $10; uchar: $11;
  ushort: 0; // padding
#else
  ulong: 0; //padding
#endif
  link:  $12;
 @})

//
// Tile descriptors
//
// Dungeon tiles
//                      Map    Draw   Tr Pa Con Item Wall Door Color    Lit color   Step
TILE( FLOOR,            {@.@},   3,   1, 1, 0,  1,   0,   0,   BLACK,   LBLACK,     floor_step               ) // Dungeon floor
TILE( SHOPFLOOR,        {@s@},   3,   1, 1, 0,  0,   0,   0,   BLACK,   LBLACK,     enter_shop               ) // Shop floor
TILE( FAKEFLOOR,        {@/@},   3,   1, 0, 0,  0,   0,   0,   BLACK,   LBLACK,     NULL                     ) // Impassable tile that looks like floor
TILE( INTERIOR,         {@i@},   3,   1, 0, 0,  0,   0,   0,   BLACK,   LBLACK,     NULL                     ) // Unenterable building interior
TILE( WALL,             {@#@},   5,   0, 0, 0,  0,   1,   0,   WHITE,   WHITE,      NULL                     ) // Wall
TILE( WALL_UNDIGGABLE,  {@W@},   5,   0, 0, 0,  0,   1,   0,   WHITE,   WHITE,      NULL                     ) // Undiggable wall
TILE( SDOOR,            {@X@},   5,   0, 0, 0,  0,   0,   1,   WHITE,   WHITE,      NULL                     ) // Secret door
TILE( ODOOR,            {@-@},  '-',  1, 1, 0,  0,   0,   1,   YELLOW,  YELLOW,     NULL                     ) // Open door
TILE( CDOOR,            {@+@},  '+',  0, 0, 0,  0,   0,   1,   YELLOW,  YELLOW,     try_closed_door          ) // Closed door
TILE( LDOOR,            {@=@},  '+',  0, 0, 0,  0,   0,   1,   YELLOW,  YELLOW,     try_locked_door          ) // Locked door
TILE( SPIDERWEB,        {@|@},   16,  1, 1, 0,  1,   0,   0,   LWHITE,  LWHITE,     web_entangle             ) // Spider web
TILE( SMOKE,            {@~@},  '~',  0, 1, 0,  1,   0,   0,   WHITE,   WHITE,      NULL                     ) // Smoke

TILE( FOUNTAIN,         {@}@},   18,  1, 1, 0,  0,   0,   0,   LBLUE,   LBLUE,      fountain_drink           ) // Fountain
TILE( DRY_FOUNTAIN,     {@}@},   18,  1, 1, 0,  0,   0,   0,   WHITE,   WHITE,      fountain_dried           ) // Fountain
TILE( SIGN,             {@t@},   15,  1, 1, 0,  0,   0,   0,   YELLOW,  YELLOW,     read_tutorial_sign       ) // Tutorial sign

TILE( DOCK,             {@D@},   35,  1, 1, 0,  0,   0,   0,   YELLOW,  YELLOW,     NULL                     ) // Dock
TILE( HORIZ_FENCE,      {@f@},  '-',  1, 0, 0,  0,   0,   0,   YELLOW,  YELLOW,     NULL                     ) // Fence (horizontal)
TILE( VERT_FENCE,       {@F@},  '|',  1, 0, 0,  0,   0,   0,   YELLOW,  YELLOW,     NULL                     ) // Fence (vertical)

TILE( FORGE,            {@!@},  '&',  1, 1, 0,  0,   0,   0,   WHITE,   WHITE,      NULL                     ) // Forge

//
// Wilderness tiles
//
TILE( WATER,            {@%@},   6,   1, 0, 0,  0,   0,   0,   LBLUE,   LBLUE,      NULL                     ) // Water
TILE( PLAINS,           {@:@},   7,   1, 1, 0,  0,   0,   0,   GREEN,   GREEN,      NULL                     ) // Plains
TILE( ROAD,             {@_@},   8,   1, 1, 0,  0,   0,   0,   WHITE,   WHITE,      NULL                     ) // Road
TILE( MOUNT1,           {@^@},   9,   0, 0, 0,  0,   0,   0,   WHITE,   WHITE,      NULL                     ) // Mountain (1)
TILE( MOUNT2,           {@*@},   10,  0, 0, 0,  0,   0,   0,   WHITE,   WHITE,      NULL                     ) // Mountain (2)
TILE( FOREST,           {@&@},  '&',  0, 1, 0,  0,   0,   0,   GREEN,   GREEN,      NULL                     ) // Forest
TILE( TREE,             {@T@},  '&',  0, 0, 0,  0,   0,   0,   GREEN,   GREEN,      NULL                     )
//
// Traps
//
TILE( PITTRAP,          1,      '^',  1, 1, 0,  1,   0,   0,   LRED,    LRED,       trap_pit   )
TILE( DARTTRAP,         1,      '^',  1, 1, 0,  1,   0,   0,   LRED,    LRED,       trap_dart  )
TILE( FLAMETRAP,        1,      '^',  1, 1, 0,  1,   0,   0,   LRED,    LRED,       trap_flame )
//
// Connections
//
TILE( STAIRUP,          {@<@},  '<',  1, 1, 1,  0,   0,   0,   WHITE,   WHITE,      auto_follow_connection   ) // Stairs up
TILE( STAIRDN,          {@>@},  '>',  1, 1, 1,  0,   0,   0,   WHITE,   WHITE,      auto_follow_connection   ) // Stairs down
TILE( CONNECTION,       {@C@},   3,   1, 0, 1,  0,   0,   0,   BLACK,   LBLACK,     force_follow_connection  ) // Direct connection
TILE( TOWN,             {@V@},   19,  1, 0, 1,  0,   0,   0,   YELLOW,  YELLOW,     force_follow_connection  )
TILE( CAVE,             {@c@},   20,  1, 0, 1,  0,   0,   0,   LBLACK,  LBLACK,     force_follow_connection  )
TILE( FORESTCONN,       {@a@},  '&',  1, 0, 1,  0,   0,   0,   GREEN,   GREEN,      force_follow_connection  )
TILE( ROADCONN,         {@R@},   8,   1, 0, 1,  0,   0,   0,   WHITE,   WHITE,      force_follow_connection  )
TILE( BRIDGECONN,       {@B@},   35,  1, 0, 1,  0,   0,   0,   YELLOW,  YELLOW,     force_follow_connection  )
TILE( AIRFALL,          {@A@},   6,   1, 0, 1,  0,   0,   0,   LBLUE,   LBLUE,      falling_connection       )
//
// Meta
//
TILE( BLANK,            {@?@},   0,   1, 0, 0,  0,   0,   0,   GREEN,   GREEN,      NULL    )

//{{{
void floor_step(int x, int y)
{
	get_w()->game_flags[IS_IN_SHOP] = 0;
}
//}}}
//{{{
void enter_shop(int x, int y)
{
	if(!get_w()->game_flags[IS_IN_SHOP])
	{
		get_w()->game_flags[IS_IN_SHOP] = 1;
	}
}
//}}}
//{{{
void try_closed_door(int x, int y)
{
	get_w()->t[y][x].type = TILE_ODOOR;
	draw_tile(x, y);
	calc_light();
}
//}}}
//{{{
void try_locked_door(int x, int y)
{
	message(gettext("The door is locked."));
}
//}}}

//{{{
void trap_pit(int x, int y)
{
	if(!(get_w()->t[y][x].flags & TFLAG_HIDETRAP) && random(3,0))
		message(gettext("You evade the trap."));
	else
	{
		get_w()->t[y][x].flags &= ~TFLAG_HIDETRAP;
		message(gettext("You fall into a pit!"));
		plr_takedamage(random(5,3), gettext("Killed by a pit trap"));
	}
	floor_step();
}
//}}}
//{{{
void trap_dart(int x, int y)
{
	if(!(get_w()->t[y][x].flags & TFLAG_HIDETRAP) && random(3,0))
		message(gettext("You evade the trap."));
	else
	{
		get_w()->t[y][x].flags &= ~TFLAG_HIDETRAP;
		message(gettext("You are hit by a dart!"));
		plr_takedamage(random(7,4), gettext("Killed by a dart trap"));
	}
	floor_step();
}
//}}}
//{{{
void trap_flame(int x, int y)
{
	if(!(get_w()->t[y][x].flags & TFLAG_HIDETRAP) && random(3,0))
		message(gettext("You evade the trap."));
	else
	{
		get_w()->t[y][x].flags &= ~TFLAG_HIDETRAP;
		message(gettext("A tower of flame erupts from the floor!"));
		plr_takedamage(random(15,9), gettext("Killed by a fire trap"));
	}
	floor_step();
}
//}}}

//{{{
void drain_fountain(int x, int y)
{
	int charges = get_w()->t[y][x].special & 15;
	int type = get_w()->t[y][x].special >> 4;
	charges--;
	if(!charges)
		type = random(2, 0);
	get_w()->t[y][x].special = (type<<4) + charges;
}
//}}}
//{{{
void dry_fountain(int x, int y)
{
	get_w()->t[y][x].type = TILE_DRY_FOUNTAIN;
}
//}}}
//{{{
void fountain_drink(int x, int y)
{
	int charges = get_w()->t[y][x].special & 15;
	int type = get_w()->t[y][x].special >> 4;
	int i;
	int effect;
	
	floor_step();
	
	if(prompt(gettext("There is a fountain here. Drink from it?")))
	{
		if(charges)
		{
			if(type == FOUNTAIN_HEALING)
			{
				if(get_plr()->hps < get_plr()->hps_max)
				{
					message(gettext("The water heals you."));
					plr_heal(random(15, 10));
				} else {
					message(gettext("The water is warm."));
				}
			}
			else if(type == FOUNTAIN_MANA)
			{
				if(get_plr()->pps < get_plr()->pps_max)
				{
					message(gettext("The water recharges you."));
					get_plr()->pps += random(15, 10);
					if(get_plr()->pps > get_plr()->pps_max)
						get_plr()->pps = get_plr()->pps_max;
				} else {
					message(gettext("The water is cold."));
				}
			}
			else if(type == FOUNTAIN_POISON)
			{
				if(get_plr()->extrinsic[STAT_FLAGS] & STAT_FLAG_RESIST_POISON)
				{
					message(gettext("The water is dirty."));
				} else {
					message(gettext("Yurgh! The water is vile!"));
					plr_takedamage(random(10, 6), gettext("Drank poison."));
				}
			}
			else if(type == FOUNTAIN_HALLUCINOGEN)
			{
				message(gettext("The water tastes funky."));
				hallucinate( random(100,50) );
			}
			else if(type == FOUNTAIN_RESTORE)
			{
				effect = 0;
				for(i=0; i<NUM_BASE_STATS; i++)
					if(plr_restore_stat(i, 2))
						effect=1;
				if(!effect)
					message(gettext("The water is cold."));
			}
			else if(type == FOUNTAIN_NUMB)
			{
				if(get_plr()->hps*4 < get_plr()->hps_max)
					message(gettext("You lose all feeling and the pain disappears."));
				else
					message(gettext("You lose all feeling in your body."));
				numb(120);
			}
			else if(type == FOUNTAIN_ELEMENTAL)
			{
				message(gettext("The water suddenly comes to life!"));
				create_companion(LINK_WATER_ELEMENTAL);
				dry_fountain(x, y);
			}
			else
			{
				message(gettext("The water is tasteless."));
			}
			
			drain_fountain(x,y);
		}
		else
		{
			if(type == FOUNTAIN_DEPLETED_COLD)
				message(gettext("The water is cold."));
			else if(type == FOUNTAIN_DEPLETED_WARM)
				message(gettext("The water is warm."));
			else if(type == FOUNTAIN_DEPLETED_DIRTY)
				message(gettext("The water is dirty."));
			else
				message(gettext("The water is tasteless."));
			if(random(5,1)==1) {
				message(gettext("The fountain dries up."));
				dry_fountain(x, y);
			}
		}
	}
}
//}}}
//{{{
void fountain_dried(int x, int y)
{
	message(gettext("This fountain is dried up."));
}
//}}}
//{{{
void web_entangle(int x, int y)
{
	int time = 5 - get_plr()->extrinsic[STAT_STRENGTH]/5;
	get_w()->t[y][x].type = TILE_FLOOR;
	
	if(time>0)
	{
		message(gettext("You get stuck in a giant spider web!"));
		entangle(time);
	} else {
		message(gettext("You tear through the webs."));
	}
}
//}}}

//{{{
void falling_connection()
{
	int x; int y;
	
	message(gettext("You fall..."));
	plr_takedamage(random(30,15), "Fell from the sky.");
	
	get_w()->t[get_w()->plr.y][get_w()->plr.x].flags &= ~TFLAG_OCCUPIED;
	get_w()->plr.x = x;
	get_w()->plr.y = y;
	follow_connection();
	
	message("Ouch!");
}
//}}}

