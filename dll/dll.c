/* {{{
 * CalcRogue, a roguelike game for PCs, calculators and PDAs
 * Copyright (C) 2003 Jim Babcock
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 * }}} */
// dll.c
/// @file
/// @brief Miscellaneous functions in the DLL
///
/// Functions which either (a) need to be accessible through the data
/// file call table or (b) just wouldn't fit in the main program.

#include "crogue.h"
#include "dll.h"

#ifndef CPROTO
#include "import.h"
#endif

#ifdef IS_CALCULATOR
DLL_INTERFACE

DLL_ID DLL_IDENTIFICATION_NUMBER
DLL_VERSION CROGUE_VERSION_MAJOR, CROGUE_VERSION_MINOR
DLL_EXPORTS dll_load

DLL_IMPLEMENTATION
#endif

#ifndef CPROTO
const import_functions *dll_body_functions;
#endif

//{{{
const void** dll_load(const void *f)
{
	dll_body_functions = f;
	return (const void**)(&dll_exports);
}
//}}}
void no_op(void) {}

static void cause_confusion(void);

//{{{
static const stat_timer_desc spell_shield_dv_timer = {
		TIMER_STAT,
		{STATMOD_ADD, STAT_DV, 8},
		gettext("You are no longer protected.")
	};
//}}}
//{{{
static const stat_timer_desc spell_shield_pv_timer = {
		TIMER_STAT,
		{STATMOD_ADD, STAT_PV, 4},
		NULL
	};
//}}}
//{{{
static const stat_timer_desc spell_gain_strength_timer = {
		TIMER_STAT,
		{STATMOD_ADD, STAT_STRENGTH, 8},
		gettext("Your strength returns to normal.")
	};
//}}}
//{{{
static const stat_timer_desc spell_gain_strength_timer_to = {
		TIMER_STAT,
		{STATMOD_ADD, STAT_TOUGHNESS, 4},
		NULL
	};
//}}}
//{{{
static const stat_timer_desc spell_gain_strength_timer_wi = {
		TIMER_STAT,
		{STATMOD_ADD, STAT_WILLPOWER, 3},
		NULL
	};
//}}}
//{{{
static const stat_timer_desc spell_heal_timer = {
		TIMER_STAT,
		{STATMOD_ADD, STAT_REGEN, 2},
		gettext("You stop regenerating.")
	};
//}}}
//{{{
static const func_timer_desc adrenaline_high_timer = {
		TIMER_FUNC,
		&spell_adrenaline_high_effect,
		&spell_adrenaline_low
	};
//}}}
//{{{
static const func_timer_desc adrenaline_low_timer = {
		TIMER_FUNC,
		&spell_adrenaline_low_effect,
		&spell_adrenaline_expire	
	};
//}}}

//{{{
int tool_holysymbol(void)
{
	int num_scared = 0, x, y, m;
	
	// Repel vampires
	for(y=w->plr.y-1; y<=w->plr.y+1; y++)
	for(x=w->plr.x-1; x<=w->plr.x+1; x++)
	{
		m = monstbytile(x, y);
		if(m<0) continue;
		
		if(MDESC(m)->flags & MONSTFLAG_VAMPIRIC)
		{
			scare_monster_force(m);
			num_scared++;
		}
	}
	
	if(!num_scared)
		message(gettext("Nothing happens."));
	
	timepass(1); 
	
	return 1;
}
//}}}

//{{{
void spell_shield(void)
{
	message(gettext("You are surrounded by a golden haze."));
	add_timer((timer_desc*)&spell_shield_dv_timer, 50);
	add_timer((timer_desc*)&spell_shield_pv_timer, 50);
}
//}}}
//{{{
void spell_confusion(void)
{
	if( !(w->plr.extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_DAGGER) )
		message(gettext("You need a dagger to cast that spell."));
	else if( w->plr.hps <= 1 && !(w->plr.extrinsic[STAT_FLAGS] & STAT_FLAG_NUMB) )
		message(gettext("You need to rest a bit before you can use your blood for a spell."));
	else if( w->plr.extrinsic[STAT_COMPONENTS] & STAT_COMPONENT_GLOVES )
		message(gettext("You need to remove your gloves to cast that spell."));
	else
	{
		plr_takedamage(1, gettext("Killed by excessive blood loss"));
		cause_confusion();
	}
}
//}}}
//{{{
void spell_gain_strength(void)
{
	add_timer((timer_desc*)&spell_gain_strength_timer, 100);
	add_timer((timer_desc*)&spell_gain_strength_timer_to, 100);
	add_timer((timer_desc*)&spell_gain_strength_timer_wi, 100);
	message(gettext("Power ripples through your body."));
}
//}}}
//{{{
void spell_heal(void)
{
	add_timer((timer_desc*)&spell_heal_timer, 30);
	message(gettext("Your wounds heal quickly."));
}
//}}}
//{{{
void spell_adrenaline(void)
{
	message(gettext("You feel a surge of adrenaline."));
	add_timer((timer_desc*)&adrenaline_high_timer, 20);
}
//}}}
//{{{
void spell_adrenaline_low(void)
{
	message(gettext("You run out of breath."));
	add_timer((timer_desc*)&adrenaline_low_timer, 20);
}
//}}}
//{{{
void spell_adrenaline_expire(void)
{
	message(gettext("You catch your breath."));
}
//}}}
//{{{
void spell_adrenaline_high_effect(void)
{
	const stat_mod_desc speed_effect = {STATMOD_ADD, STAT_SPEED, 3};
	const stat_mod_desc strength_effect = {STATMOD_ADD, STAT_STRENGTH, 5};
	const stat_mod_desc dexterity_effect = {STATMOD_ADD, STAT_DEXTERITY, 3};
	const stat_mod_desc dv_effect = {STATMOD_ADD, STAT_DV, 6};
	apply_stat_mod_desc(NULL, &speed_effect, 0);
	apply_stat_mod_desc(NULL, &strength_effect, 0);
	apply_stat_mod_desc(NULL, &dexterity_effect, 0);
	apply_stat_mod_desc(NULL, &dv_effect, 0);
}
//}}}
//{{{
void spell_adrenaline_low_effect(void)
{
	const stat_mod_desc speed_effect = {STATMOD_ADD, STAT_SPEED, -3};
	const stat_mod_desc strength_effect = {STATMOD_ADD, STAT_STRENGTH, -3};
	const stat_mod_desc dv_effect = {STATMOD_ADD, STAT_DV, -4};
	apply_stat_mod_desc(NULL, &speed_effect, 0);
	apply_stat_mod_desc(NULL, &strength_effect, 0);
	apply_stat_mod_desc(NULL, &dv_effect, 0);

}
//}}}

//{{{
static void cause_confusion(void)
{
	int i;
	message(gettext("You sense chaos and confusion."));
	
	for(i=0; i<MONSTERS_MAX; i++)
	{
		if(!isNull(w->m[i].type) && !monst_is_peaceful(i))
			confuse_monster(i);
	}
}
//}}}

//{{{
void read_tutorial_sign(uint x, uint y)
{
	int sign_num = TILESPEC(x,y).ext.sign_id;
	char str[512] = "";
	const char *strptr = str;
	
	switch(sign_num)
	{
//{{{
		case 0:
			sprintf(str,
gettext("Welcome to CalcRogue! Look for signs like this one throughout"
" this level. At any point, press '%s' to open a controls reference."),
				get_keyname(KEY_ACT_MENU) );
			break;
//}}}
//{{{
		case 1:
			sprintf(str,
gettext("The + represents a door. To open it, you can move into it and it will"
" open automatically. When open, it will change to a -. You can also press"
" '%s' to open doors."),
				get_keyname(KEY_OPENDOOR) );
			break;
//}}}
//{{{
		case 2:
			sprintf(str, gettext("To close the door, press '%s'."),
				get_keyname(KEY_CLOSEDOOR) );
			break;
//}}}
//{{{
		case 3:
			sprintf(str, 
gettext("There is a monster behind this door, so before you proceed, be sure"
" to pick up the sword and equip it. To equip items, press '%s'. To unequip"
" them, press '%s', and to drop them press '%s'."),
				get_keyname(KEY_WEAR),
				get_keyname(KEY_TAKEOFF),
				get_keyname(KEY_DROP) );
			break;
//}}}
//{{{
		case 4:
			sprintf(str,
gettext("There is a secret door behind this sign. To search for secret doors,"
" press '%s'. (You may not find it on the first try.)"),
				get_keyname(KEY_SEARCH) );
			break;
//}}}
//{{{
		case 5:
			sprintf(str,
gettext("You'll have to dig through this wall. To use the wand of digging you"
" found, press '%s'."),
				get_keyname(KEY_USE) );
			break;
//}}}
//{{{
		case 6:
			sprintf(str,
gettext("When you have equipped a bow and arrows, fire arrows by pressing"
" '%s'. (You can throw/fire items that you haven't readied with '%s'.) Use"
" these arrows on the bats in the next room."),
				get_keyname(KEY_FIRE),
				get_keyname(KEY_THROW) );
			break;
//}}}
//{{{
		case 7:
			sprintf(str,
gettext("To read this spellbook, press '%s' and select it. When you have"
" learned a spell, you can open a menu of the spells you can cast by pressing"
" '%s'.\n"
"\n"
"Casting spells requires energy, which is shown on the status line as PW."
" Some spells also have other requirements, and some spells require that"
" you commit energy for the entire duration of the spell."),
				get_keyname(KEY_USE),
				get_keyname(KEY_CAST) );
			break;
//}}}
//{{{
		case 8:
			strptr =
				gettext("Gold adds to your score, and can be spent in shops.");
			break;
//}}}
//{{{
		case 9:
			sprintf(str,
gettext("This ring boosts your strength when worn. To view your stats, press"
" '%s'. Your base attribute is shown, and the modified attribute is in"
" parentheses."),
				get_keyname(KEY_STATS) );
			break;
//}}}
//{{{
		case 10:
			strptr =
gettext("The effectiveness of armor is shown in brackets in the form [DV, PV]."
" DV (Defense) makes you harder to hit, while PV (Protection) reduces the"
" damage hits do. Similarly, weapons use the form (Damage, To-hit) (note"
" the use of parentheses, not brackets.");
			break;
//}}}
//{{{
		case 11:
			sprintf(str,
gettext("You can run down long corridors in a single keystroke by pressing"
" '%s'."),
			get_keyname(KEY_RUN_SOUTH) );
			break;
//}}}
//{{{
		case 12:
			sprintf(str,
gettext("You are now ready to start a normal game. Remember, if you forget any"
" of the controls, press '%s' to bring up a menu."),
				get_keyname(KEY_ACT_MENU) );
			break;
//}}}
	}
	
	UI_Dialog_Default(strptr);
}
//}}}
//{{{
void auto_follow_connection(uint x, uint y)
{
	filelink target_map_handle;
	mapdesc *target_map;
	const char *target_map_name;
	
	target_map_handle = TILESPEC(x,y).ext.lvl.destmap;
	target_map = (mapdesc*)deref_file_ptr(target_map_handle);
	target_map_name = (const char*)deref_file_ptr( target_map->name );
	switch(get_option(OPTION_AUTOFOLLOW))
	{
		case OPTION_AUTO_PROMPT:
			if( !prompt(
			      retprintf(
				    gettext("These stairs lead to %s. Climb them?"),
			          target_map_name
			      )
			    )
			  )
			{
				break;
			}
			/*@fallthrough@*/
		case OPTION_AUTO_YES:
			follow_connection();
			break;
		case OPTION_AUTO_NO:
			message( gettext("These stairs lead to %s."), target_map_name );
			break;
	}
}
//}}}
//{{{
void force_follow_connection(uint x, uint y)
{
	w->t[w->plr.y][w->plr.x].flags &= ~TFLAG_OCCUPIED;
	w->plr.x = x;
	w->plr.y = y;
	follow_connection();
}
//}}}

//{{{
static void light_room(room r)
{
	int x, y;
	for(y=r.top-1; y<=r.bottom+1; y++)
		for(x=r.left-1; x<=r.right+1; x++)
			w->t[y][x].flags |= TFLAG_INTRINSIC_LIGHT;
	
	illuminate( (r.left+r.right)/2, (r.top+r.bottom)/2, 400);
}
//}}}
//{{{
static void place_shop(room r, int portal_x, int portal_y)
{
	int x, y;
	int perturb_x=0, perturb_y=0;
	int shop_type;
	item itm;
	
	shop_type = lrand() % w->desc.numshoptypes;
	
	for(y=r.top; y<=r.bottom; y++)
		for(x=r.left; x<=r.right; x++)
		{
			w->t[y][x].type = TILE_SHOPFLOOR;
			w->t[y][x].special = shop_type;
		}
	light_room(r);
	
	// Place shopkeeper
	if(portal_x == r.left-1)
		portal_x++, r.left++;
	else if(portal_x == r.right+1)
		portal_x--, r.right--;
	else
		perturb_x = 1;
	
	if(portal_y == r.top-1)
		portal_y++, r.top++;
	else if(portal_y == r.bottom+1)
		portal_y--, r.bottom--;
	else
		perturb_y = 1;
	
	if(perturb_x)
	{
		if(w->t[portal_y][portal_x+1].type == TILE_SHOPFLOOR)
			portal_x++;
		else
			portal_x--;
	}
	if(perturb_y)
	{
		if(w->t[portal_y+1][portal_x].type == TILE_SHOPFLOOR)
			portal_y++;
		else
			portal_y--;
	}
	addmonster( portal_x, portal_y, w->shopdescs[shop_type].shopkeeper);

	// Fill with items
	for(y=r.top; y<=r.bottom; y++)
		for(x=r.left; x<=r.right; x++)
		{
			itm = randitem(w->shopdescs[shop_type].generate_item);
			itm.flags |= ITEMFLAG_UNPAID;
			place_item(&itm, x, y);
		}
}
//}}}
//{{{
static void place_fountain(int x, int y)
{
	w->t[y][x].type = TILE_FOUNTAIN;
	w->t[y][x].special = ((RANGE(NUM_FOUNTAIN_TYPES-1, 0) << 4) + (RANGE(2,0)?RANGE(6,3):0));
}
//}}}
//{{{
void dll_fill_room(room *r)
{
	int which_room;
	int x, y;
	int width, height;
	int num_portals = 0, portal_x=-1, portal_y=-1;
	
	width = r->right - r->left + 1;
	height = r->bottom - r->top + 1;
	
retry:
	y=r->top-1;
	for(x=r->left-1; x<=r->right+1; x++)
		if(!TILEDESC(w->t[y][x]).is_wall)
			num_portals++, portal_x=x, portal_y=y;
	y=r->bottom+1;
	for(x=r->left-1; x<=r->right+1; x++)
		if(!TILEDESC(w->t[y][x]).is_wall)
			num_portals++, portal_x=x, portal_y=y;
	
	x=r->left-1;
	for(y=r->top-1; y<=r->bottom+1; y++)
		if(!TILEDESC(w->t[y][x]).is_wall)
			num_portals++, portal_x=x, portal_y=y;
	x=r->right+1;
	for(y=r->top-1; y<=r->bottom+1; y++)
		if(!TILEDESC(w->t[y][x]).is_wall)
			num_portals++, portal_x=x, portal_y=y;
	
	if(num_portals==1 && RANGE(9,1)>=MAPDESC_CURRENT.difficulty)
	{
		place_shop(*r, portal_x, portal_y);
		return;
	}

	which_room = RANGE(28,0);
	switch(which_room)
	{
		case 0: // Checkerboard
			// ##########
			// ## # # # #
			// # # # # ##
			// ## # # # #
			// # # # # ##
			// ## # # # #
			// ##########
			if(w->level < 3) // No checkerboard rooms above level 3
				goto retry;
			
			for(y=r->top; y<=r->bottom; y++)
				for(x=r->left+(y%2); x<=r->right; x+=2)
					w->t[y][x].type = TILE_WALL;
			break;
			
		case 1: // Pillars
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			// #########
			// #       #
			// # # # # #
			// #       #
			// # # # # #
			// #       #
			// #########
			// Only for odd-width rooms with size >4
			if( !(width%2) || height<=4 )
				goto retry;
			
			y=r->top + 1;
			for(x=r->left+1; x<r->right; x+=2)
				w->t[y][x].type = TILE_WALL;
			
			if(r->bottom-r->top > 3)
			{
				y = r->bottom - 1;
				for(x=r->left+1; x<r->right; x+=2)
					w->t[y][x].type = TILE_WALL;
			}
			break;
			
		case 8: // Smoke-filled room
			// ##########
			// #~~~~~~~~#
			// #~~~~~~~~#
			// #~~~~~~~~#
			// #~~~~~~~~#
			// #~~~~~~~~#
			// ##########
			for(y=r->top; y<=r->bottom; y++)
				for(x=r->left; x<=r->right; x++)
					w->t[y][x].type = TILE_SMOKE;
			break;	
/*		case 9: // Trap room
			// ##########
			// #^^^^^^^^#
			// #^^^^^^^^#
			// #^^^^^^^^#
			// #^^^^^^^^#
			// #^^^^^^^^#
			// ##########
			if(w->level < 5) // No trap rooms above level 5
				goto retry;

			for(y=r->top; y<=r->bottom; y++)
				for(x=r->left; x<=r->right; x++)
					place_trap(x, y);
			break;*/
		case 10: // Room with fountain
			x = RANGE(r->right, r->left);
			y = RANGE(r->bottom, r->top);
			place_fountain(x, y);
			break;
	}
	
	// 50% chance: intrinsically light room
	if(RANGE(1,0)==0)
	{
		light_room(*r);
	}
}
//}}}

