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
// debug.c
/// @file
/// @brief Menu and functions for in-game debugging and diagnostics

#include "crogue.h"
#include "dll.h"

#define NUM_DEBUGOPTS 12

#ifdef ALLOWDEBUG
#ifdef DEBUG_HEAVILY
static void do_diagnostic(void) SEG(4);
static void build_levels_list(void) SEG(4);
static void destroy_levels_list(void) SEG(4);
static void cb_levelname(int n, char *buf) SEG(4);
static void level_teleport(void) SEG(4);

#endif

//{{{
static const char* debugmenuopts[NUM_DEBUGOPTS] = {
	gettext("Gain level"),
	gettext("Gain attributes"),
	gettext("Heal"),
	gettext("Invulnerability"),
	gettext("Show segment headers"),
	gettext("Show free mem"),
	gettext("Reveal map"),
	gettext("Run diagnostic"),
	gettext("Show facing"),
	gettext("Throw exception"),
	gettext("Give item"),
	gettext("Level teleport")
};
//}}}
//{{{
static void debugmenu_pick(int N, char *buf)
{
	strcpy(buf, debugmenuopts[N]);
}
//}}}
//{{{
static void debugmenu_item(int N, char *buf)
{
	item itm = {N+1, 0, 1, 0, 0, 0, 0};
	strcpy(buf, itemname(&itm));
}
//}}}

//{{{
/// Open the debug menu and handle a debugging command
void debug(void)
{
	int ii, jj;
	int choice;
	item itm = {0, 0, 1, 0, 0, 0, 0};
	
	if(!w->debug_mode)
	{
		if(!prompt(gettext("Warning: If you use debug features, you will not receive a score. Continue?")))
			return;
	}
	choice = UI_Menu_Pick(debug_rect, NUM_DEBUGOPTS, &debugmenu_pick);
	
	if(choice>=0)
		w->debug_mode = 1;
	
	// Indeces correspond to debugmenuopts strings
	switch( choice )
	{
		case 0:	// Gain level
			w->plr.level ++;
			w->plr.xp = 0;
			update_player();
			break;
		case 1:	// Gain attributes
			for(ii=0; ii<5; ii++)
				w->plr.intrinsic[ii] += 10;
			
			update_player();
			break;
		case 2: // Heal
			w->plr.hps = w->plr.hps_max;
			break;
		case 3: // Pseudo-invulnerability
			w->plr.hps_max_mod = 2000;
			update_player();
			w->plr.hps = w->plr.hps_max;
			break;
		case 4:	// Remove satiation
			message("%li segments", w->num_segments);
			message("Segment 1 start: %i %i %i %i",
				(int)w->const_file[1][0],
				(int)w->const_file[1][1],
				(int)w->const_file[1][2],
				(int)w->const_file[1][3]);
			message("light plane: %i %i %i",
				(int)w->desc.titlescreen_light_plane.segment,
				(int)w->desc.titlescreen_light_plane.type,
				(int)w->desc.titlescreen_light_plane.offset);
			message("seg1 %lp, file[1] %lp",
				deref_file_ptr(w->desc.titlescreen_light_plane),
				w->const_file[1]);
			break;
		case 5:	// Show free memory
#ifdef IS_CALCULATOR
			message(gettext("Free memory: %li"), HeapAvail());
#else
			message(gettext("Free memory: Lots."));
#endif
			break;
		case 6:
			for(jj=0; jj<MAPSIZE_Y; jj++)
			for(ii=0; ii<MAPSIZE_X; ii++) {
				w->t[jj][ii].flags |= TFLAG_EXPLORED;
				draw_tile(ii, jj);
			}
			break;
		
		case 7:
#ifdef DEBUG_HEAVILY
			do_diagnostic();
#endif
			break;
		case 8:
			message(gettext("Facing: %i, forced: %i"), w->plr.facing, w->plr.facing_forced);
			break;
		
		case 9:
#ifdef IS_CALCULATOR
			if(prompt(gettext("This will end your game. Are you sure?")))
				ER_throw(ER_MEMORY);
#else
			message(gettext("Exceptions are only used on TI calculators."));
#endif
			break;
		case 10:
			// Identify all types
			for(ii=0; ii<w->desc.itementries; ii++) {
				identify_type(ii);
			}
			itm.type = UI_Menu_Pick(debug_item_rect, w->desc.itementries - 1, debugmenu_item) + 1;
			itm.stacksize = ITEMDESC(itm).stacksize;
			give_item(&itm, 1);
			break;
		case 11: // Level teleport
#ifdef DEBUG_HEAVILY
			level_teleport();
			break;
#endif
	}
	
	full_redraw();
}
//}}}

#ifdef DEBUG_HEAVILY
static draw_string_info output_state = {0, 0};

//{{{
static void diagnostic_print(const char *text)
{
	draw_string(text, &output_state, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 1);
}
//}}}
//{{{
static void do_diagnostic(void)
{
	int xi, yi, ii, pos, total_items=0;
	int pass, failed=0;
	int monstcount = 0;
	output_state.curX = output_state.curRow = 0;
	
	Graph_ClrScr();
	
#ifdef IS_CALCULATOR
	diagnostic_print(gettext("Checking memory... "));
	if(HeapAvail() < 4096) {
		diagnostic_print(retprintf(gettext("Only %li bytes of RAM left! "), HeapAvail()));
		failed++;
	}
#endif
	
	diagnostic_print(gettext("\nChecking world/monster consistency... "));
	for(yi=0; yi<MAPSIZE_Y; yi++)
	for(xi=0; xi<MAPSIZE_X; xi++)
	{
		if(w->t[yi][xi].flags & TFLAG_OCCUPIED)
		{
			pass = 0;
			for(ii=0; ii<MONSTERS_MAX; ii++)
			{
				if(isNull(w->m[ii].type))
					continue;
				if(w->m[ii].x == xi && w->m[ii].y == yi)
				{
					monstcount++;
					pass++;
				}
			}
			if(w->plr.x==xi && w->plr.y==yi)
				pass++;
			if(pass==0)
			{
				diagnostic_print(retprintf(gettext("Found mis-marked monster at (%i, %i)! "), xi, yi));
				failed++;
			}
			else if(pass>1)
			{
				diagnostic_print(retprintf(gettext("Found overlapping %i monsters at (%i, %i): "), pass, xi, yi));
				failed++;
				for(ii=0; ii<MONSTERS_MAX; ii++)
				{
					if(isNull(w->m[ii].type))
						continue;
					if(w->m[ii].x == xi && w->m[ii].y == yi)
						diagnostic_print(retprintf("%i, ", ii));
				}
			}
		}
	}
	
	for(ii=0; ii<MONSTERS_MAX; ii++)
	{
		if(isNull(w->m[ii].type))
			continue;
		if(w->m[ii].x<0 || w->m[ii].y<0 || w->m[ii].x>=MAPSIZE_X || w->m[ii].y>=MAPSIZE_Y)
		{
			diagnostic_print(
				retprintf(gettext("Found out of bounds monster at (%i, %i)! "),
				w->m[ii].x, w->m[ii].y));
			failed++;
			continue;
		}
		if(!(w->t[w->m[ii].y][w->m[ii].x].flags & TFLAG_OCCUPIED))
		{
			diagnostic_print(retprintf(
				gettext("Found monster on unmarked tile at (%i, %i)! "),
				w->m[ii].x, w->m[ii].y));
			failed++;
			continue;
		}
	}
	
	diagnostic_print(gettext("\nChecking item chains... "));
	for(yi=0; yi<MAPSIZE_Y; yi++)
	for(xi=0; xi<MAPSIZE_X; xi++)
	{
		if(w->t[yi][xi].flags & TFLAG_ITEM)
		{
			pos = top_item(xi, yi);
			
			if(w->items.items[pos].type > w->desc.itementries)
			{
				diagnostic_print(retprintf(
					gettext("Invalid item at (%i, %i) has type %i! "),
					xi, yi, w->items.items[pos].type) );
				failed++;
			}
			
			while(pos != 0) {
				pos = w->items.items[pos].next;
				total_items++;
			}
		}
	}
	
	if(total_items != w->items.num)
	{
		diagnostic_print(retprintf(gettext("Total number of items found does not match: expected %i, found %i. "), w->items.num, total_items));
		failed++;
	}
	diagnostic_print(retprintf(gettext("\n%i items stored, %i allocated. "), w->items.num, w->items.alloced));
	diagnostic_print(retprintf(gettext("\n%i monsters."), monstcount));
	
	diagnostic_print(retprintf(gettext("\n\nSummary: %i tests failed"),failed));
	read_char();
}
//}}}

static filelink *level_refs = NULL;
static int num_levels = 0;
//{{{
static void build_levels_list(void)
{
	static const mapdesc **levels = NULL;
	const mapdesc *current_level, *target_level;
	int pos = 0;
	int ii, jj, kk, type;
	
	if(level_refs != NULL)
		return;
	
	level_refs = (filelink*)debug_malloc(sizeof(filelink) * 100);
	levels = (const mapdesc**)debug_malloc(sizeof(const mapdesc*) * 100);
	
	// Start by assembling a list of all the levels in the game, by doing a
	// depth-first search of connections starting from level 1.
	level_refs[0] = w->desc.mainmap;
	levels[0] = (const mapdesc*)deref_file_ptr(w->desc.mainmap);
	num_levels = 1;
	
	// Foreach map seen so far
	for(ii=pos; ii<num_levels; ii++) {
		current_level = levels[ii];
		// Foreach connection
		for(jj=0; jj<current_level->numspecial; jj++) {
			type = current_level->ext[jj].type;
			// If it's a link to another level
			if(type == MAPSPEC_CONNECT ||
			   type == MAPSPEC_USER1 ||
			   type == MAPSPEC_USER2 ||
			   (type>=0 && w->tiledescs[type].is_connection))
			{
				target_level = deref_file_ptr(
					current_level->ext[jj].ext.lvl.destmap);
				
				// Check if it's a duplicate
				for(kk=0; kk<num_levels; kk++) {
					if(levels[kk] == target_level)
						goto is_duplicate;
				}
				
				level_refs[num_levels] = current_level->ext[jj].ext.lvl.destmap;
				levels[num_levels] = target_level;
				num_levels++;
			is_duplicate:;
			}
		}
	}
	
	free(levels);
}
//}}}
//{{{
static void destroy_levels_list(void)
{
	debug_free(level_refs);
	level_refs = NULL;
	num_levels = 0;
}
//}}}
//{{{
static void cb_levelname(int n, char *buf)
{
	const mapdesc *level = deref_file_ptr(level_refs[n]);
	strcpy(buf, (const char*)deref_file_ptr(level->name));
}
//}}}
//{{{
static void level_teleport(void)
{
	int target_level_num;
	filelink target_level_ref;
	const mapdesc *target_level;
	spec_descriptor_ext_level connection;
	
	build_levels_list();
	target_level_num = UI_Menu_Pick(inventory_rect, num_levels, cb_levelname);
	
	if(target_level_num < 0)
		return;
	target_level_ref = level_refs[target_level_num];
	target_level = (const mapdesc*)deref_file_ptr(target_level_ref);
	destroy_levels_list();
	
	connection.destmap = target_level_ref;
	connection.destcoord = COORD(0,0);
	goto_level(target_level_ref, &connection);
}
//}}}

#endif

#else

// Stub for debug() (since it's part of the exported interface, it can't be
// left out entirely)
void debug() {}

#endif

