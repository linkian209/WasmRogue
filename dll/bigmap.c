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
// bigmap.c
/// @file
/// @brief Map generator for big levels

#include "crogue.h"
#include "dll.h"

#define ROOMCONN_RETRIES 2
#define CORRIDOREND_RETRIES 10
#define CORRIDORBRANCH_RETRIES 2
#define ROOMSIZE_MAX_X 8
#define ROOMSIZE_MIN_X 4
#define ROOMSIZE_MAX_Y 8
#define ROOMSIZE_MIN_Y 4
#define CORRIDOR_MAX_LEN 10
#define CORRIDOR_MIN_LEN 4

#define TFLAG_CLEAN          1
#define TFLAG_RECEPTACLE     2
#define TFLAG_JUNCTION       4  /* Later, might put a door here */
//{{{
/// A potential junction point in big-map generation
typedef struct mark
{
	scoord pos;
	unsigned char direction;
	unsigned char retries;
} mark;
//}}}
//{{{
/// Details of a corridor, room or vault selected in bigmap generation
typedef union feature_info
{
	short length;
	
	struct {
		scoord size;
		short offset;
	} room;
	
	struct {
		short vaultid;
	} vault;
} feature_info;
//}}}
//{{{
/// A feature produced in bigmap generation
typedef struct feature
{
	scoord pos;
	feature_info ext;
	short type;
	short direction;
} feature;
//}}}
#define NUM_TYPES 2
#define FEATURE_ROOM       0
#define FEATURE_CORRIDOR   1
#define FEATURE_VAULT      2
//{{{
/// Details of a vault for use in bigmap generation
typedef struct vaultdesc
{
	scoord size;
	scoord offset;
	const char *content;
} vaultdesc;
//}}}

#define NUM_VAULT_TYPES 12

#define VAULTCHAR_BLANK      '/'  /* A tile that's not part of the vault     */
#define VAULTCHAR_WALL_HARD  '#'  /* A 'hard' wall cannot be replaced        */
#define VAULTCHAR_WALL_SOFT  '$'  /* A 'soft' wall could be connected to a   */
                                  /* corridor if something else generates it */
#define VAULTCHAR_DOOR       '+'
#define VAULTCHAR_MARK_DOWN  '2'  /* These correspond to the num pad         */
#define VAULTCHAR_MARK_LEFT  '4'
#define VAULTCHAR_MARK_RIGHT '6'
#define VAULTCHAR_MARK_UP    '8'

const vaultdesc vaults[] =
	{
//{{{
		{ {7,7}, {4,0},  // 5x5 Circular room
		  "/## ##/"
		  "##   ##"
		  "#     #"
		  "4     6"
		  "#     #"
		  "##   ##"
		  "/##2##/"
		},
//}}}
//{{{
		{ {9,9}, {4,0},  // 7x7 Circular room
		  "//## ##//"
		  "/##   ##/"
		  "##     ##"
		  "#       #"
		  "4       6"
		  "#       #"
		  "##     ##"
		  "/##   ##/"
		  "//##2##//"
		},
//}}}
//{{{
		{ {11,11}, {5,0},// 9x9 Circular room
		  "//### ###//"
		  "/##     ##/"
		  "##       ##"
		  "#         #"
		  "#         #"
		  "4         6"
		  "#         #"
		  "#         #"
		  "##       ##"
		  "/##     ##/"
		  "//###2###//"
		},
//}}}
//{{{
		{ {9,9}, {4,0},  // 7x7 Cross-shaped room
		  "//## ##//"
		  "//#   #//"
		  "###   ###"
		  "#       #"
		  "4       6"
		  "#       #"
		  "###   ###"
		  "//#   #//"
		  "//##2##//"
		},
//}}}
//{{{
		{ {13,13}, {8,0},// 11x11 star
		  "/////# #/////"
		  "////## ##////"
		  "////#   #////"
		  "///##   ##///"
		  "/###     ###/"
		  "##         ##"
		  "4           6"
		  "##         ##"
		  "/###     ###/"
		  "///##   ##///"
		  "////#   #////"
		  "////## ##////"
		  "/////#2#/////"
		},
//}}}
//{{{
		{ {15,15}, {8,0},// 13x13 star
		  "//////# #//////"
		  "/////## ##/////"
		  "/////#   #/////"
		  "/////#   #/////"
		  "////##   ##////"
		  "/####     ####/"
		  "##           ##"
		  "4             6"
		  "##           ##"
		  "/####     ####/"
		  "////##   ##////"
		  "/////#   #/////"
		  "/////#   #/////"
		  "/////## ##/////"
		  "//////#2#//////"
		},
//}}}
//{{{
		{ {9,9}, {4,0},  // 7x7 rotary
		  "//## ##//"
		  "/##   ##/"
		  "##     ##"
		  "#  ###  #"
		  "4  ###  6"
		  "#  ###  #"
		  "##     ##"
		  "/##   ##/"
		  "//##2##//"
		},
//}}}
//{{{
		{ {11,11}, {5,0},// 9x9 rotary
		  "//### ###//"
		  "/##     ##/"
		  "##  ###  ##"
		  "#  #####  #"
		  "# ####### #"
		  "4 ####### 6"
		  "# ####### #"
		  "#  #####  #"
		  "##  ###  ##"
		  "/##     ##/"
		  "//###2###//"
		},
//}}}
//{{{
		{ {13,13}, {6,0},// 11x11 rotary
		  "///### ###///"
		  "//##     ##//"
		  "/##       ##/"
		  "##   ###   ##"
		  "#   #####   #"
		  "#  #######  #"
		  "4  #######  6"
		  "#  #######  #"
		  "#   #####   #"
		  "##   ###   ##"
		  "/##       ##/"
		  "//##     ##//"
		  "///###2###///"
		},
//}}}
//{{{
		{ {17,17}, {8,0},// 15x15 rotary
		  "/////### ###/////"
		  "///###     ###///"
		  "//##         ##//"
		  "/##    ###    ##/"
		  "/#   #######   #/"
		  "##  #########  ##"
		  "#   #########   #"
		  "#  ###########  #"
		  "4  ###########  6"
		  "#  ###########  #"
		  "#   #########   #"
		  "##  #########  ##"
		  "/#   #######   #/"
		  "/##    ###    ##/"
		  "//##         ##//"
		  "///###     ###///"
		  "/////###2###/////"
		},
//}}}
//{{{
		{ {15,15}, {3,0},  // Wizard's tower (ala NetHack)
		  "### ###########"
		  "#             #"
		  "#             #"
		  "4             6"
		  "#             #"
		  "#     ###     #"
		  "#    ## ##    #"
		  "4    #   #    6"
		  "#    ## ##    #"
		  "#     ###     #"
		  "#             #"
		  "4             6"
		  "#             #"
		  "#             #"
		  "###2###2###2###"
		},
//}}}
//{{{
		{ {13,11}, {6,0},  // Moria-style rooms
		  "###### ######"
		  "#           #"
		  "# ######### #"
		  "# +   #   + #"
		  "# #   #   # #"
		  "4 ######### 6"
		  "# #   #   # #"
		  "# +   #   + #"
		  "# ######### #"
		  "#           #"
		  "######2######"
		},
//}}}
	};

//{{{
static scoord directions[4] =
	{
		{  1,  0 },
		{  0, -1 },
		{ -1,  0 },
		{  0,  1 }
	};
//}}}
#define DIR_RIGHT 0
#define DIR_UP    1
#define DIR_LEFT  2
#define DIR_DOWN  3

static void bigmap_prepass(void);
static int bigmap_postpass(void);
static void bigmap_fill(void);
static int bigmap_place_feature(feature *feature, mark *marks, int *marks_pending);
static int bigmap_place_corridor(feature *feature, int dry, mark *marks, int *marks_pending);
static int bigmap_place_room(feature *feature, int dry, mark *marks, int *pending);
static int bigmap_place_vault(feature *feature, int dry, mark *marks, int *pending);
static void rand_feature(feature *feature, mark *m);
static void add_mark(int x, int y, int dir, mark *marks, int *pending, int retries);

//{{{
/// @brief Generate a large map
///
/// This uses the active-points algorithm: a feature is placed on the map,
/// along with some candidate points for extending the dungeon. Select a
/// point and a feature at random, and if it fits, place it. If a point fails
/// to fit too many times, it is removed. When a corridor is generated, its
/// length will be adjusted to make a junction if it wouldn't fit, to make the
/// map better connected.
int mkmap_big(void)
{
	bigmap_prepass();
	bigmap_fill();
	return bigmap_postpass();
}
//}}}
//{{{
static int is_in_bounds(scoord pos)
{
	if(pos.x<=0 || pos.y<=0 || pos.x>=MAPSIZE_X-1 || pos.y>=MAPSIZE_Y-1)
		return 0;
	else
		return 1;
}
//}}}
//{{{
static void bigmap_prepass(void)
{
	int xi, yi;
	for(yi=0; yi<MAPSIZE_Y; yi++)
	for(xi=0; xi<MAPSIZE_X; xi++)
		w->t[yi][xi].flags = TFLAG_CLEAN;
}
//}}}
//{{{
static int bigmap_postpass(void)
{
	int xi, yi;
	unsigned filled=0, empty=0;
	for(yi=1; yi<MAPSIZE_Y-1; yi++)
	for(xi=1; xi<MAPSIZE_X-1; xi++)
	{
		if(w->t[yi][xi].type == TILE_FLOOR)
			empty++;
		else
			filled++;
		if(w->t[yi][xi].flags & TFLAG_JUNCTION && make_door(xi, yi))
		{
			if(nrandom(15,0)==0)
				w->t[yi][xi].type = TILE_SDOOR;
			else
				w->t[yi][xi].type = TILE_CDOOR;
		}
	}
	
	for(yi=0; yi<MAPSIZE_Y; yi++)
	for(xi=0; xi<MAPSIZE_X; xi++)
		w->t[yi][xi].flags = 0;
	
	if(empty < 100)
		return 0;
	else
		return 1;
}
//}}}
//{{{
static void bigmap_fill(void)
{
#ifdef CONSERVE_STACK
	mark *marks = debug_malloc(sizeof(mark) * 512);
#else
	mark marks[512];
#endif
	int marks_pending = 0;
	int current_mark;
	feature current_feature;
	
	add_mark(MAPSIZE_X/2, MAPSIZE_Y/2, nrandom(3,0), marks, &marks_pending,255);
	
	while(marks_pending > 0)
	{
		// Pick a random mark
		current_mark = nrandom(marks_pending-1, 0);
		
		// Pick a type
		rand_feature(&current_feature, &marks[current_mark]);
		
		// Check for fit
		if( bigmap_place_feature(&current_feature, marks, &marks_pending) ) {
			marks[current_mark] = marks[--marks_pending];
		} else {
			marks[current_mark].retries --;
			if(marks[current_mark].retries == 0)
				marks[current_mark] = marks[--marks_pending];
		}
	}
}
//}}}
//{{{
static int bigmap_place_feature(feature *feature, mark *marks, int *pending)
{
	switch(feature->type)
	{
		case FEATURE_CORRIDOR:
			// Dry run: See if it fits first, then try to place it
			if(bigmap_place_corridor(feature, 1, marks, pending))
			     return bigmap_place_corridor(feature, 0, marks, pending);
			else return 0;
		default:
		case FEATURE_ROOM:
			// Dry run: See if it fits first, then try to place it
			if(bigmap_place_room(feature, 1, marks, pending))
			     return bigmap_place_room(feature, 0, marks, pending);
			else return 0;
		case FEATURE_VAULT:
			if(bigmap_place_vault(feature, 1, marks, pending))
			     return bigmap_place_vault(feature, 0, marks, pending);
			else return 0;
	}
}
//}}}
//{{{
static int bigmap_place_corridor(feature *feature, int dry,
	mark *marks, int *marks_pending)
{
	int ii;
	scoord pos = feature->pos;
	scoord delta = directions[feature->direction];
	scoord perpendicular = directions[ (feature->direction+1)%4 ];
	scoord tmp;
	int branch_direction = (feature->direction+1)%4;
	
	for(ii=0; ii<feature->ext.length; ii++)
	{
		// OPTIMIZEME: This bounds check should be outside the loop
		if(!is_in_bounds(pos)) return 0;
		
		if(dry)
		{
			if(w->t[pos.y][pos.x].flags & TFLAG_RECEPTACLE)
					// Hit another room, but in a spot where it doesn't mind
					// having a corridor sticking out
				return 1;
			if(w->t[pos.y][pos.x].flags & TFLAG_CLEAN)
					// Tunneling through new ground
				continue;
			return 0;
		}
		else
		{
			if(w->t[pos.y][pos.x].flags & TFLAG_CLEAN)
			{
				w->t[pos.y][pos.x].type = TILE_FLOOR;
				w->t[pos.y][pos.x].flags &= ~TFLAG_CLEAN;
				
				// 1 in 9 chance: Put a mark here
				if(nrandom(8,0)==0)
				{
					if(nrandom(1,0)) // Random side
					{
						perpendicular.x = -perpendicular.x;
						perpendicular.y = -perpendicular.y;
						branch_direction = (branch_direction+2)%4;
					}
					tmp.x = pos.x + perpendicular.x;
					tmp.y = pos.y + perpendicular.y;
					add_mark(tmp.x, tmp.y, branch_direction,
						marks, marks_pending, CORRIDORBRANCH_RETRIES);
				}
			}
			else if(w->t[pos.y][pos.x].flags & TFLAG_RECEPTACLE)
			{
				w->t[pos.y][pos.x].type = TILE_FLOOR;
				return 1;
			}
			else
			{
				pos.x -= delta.x;
				pos.y -= delta.y;
				w->t[pos.y][pos.x].flags |= TFLAG_JUNCTION;
				return 1;
			}
		}
		
		pos.x += delta.x;
		pos.y += delta.y;
	}
	// Put a mark at the end
	if(!dry) {
		add_mark(pos.x, pos.y, feature->direction,
			marks, marks_pending, CORRIDOREND_RETRIES);
	}
	
		// Disappeared into the ether, making a dead end
	return 1;
}
//}}}
//{{{
static int bigmap_place_room(feature *feature, int dry,
	mark *marks, int *pending)
{
	scoord next_cell, next_row;
	scoord pos;
	int xi, yi;
	int min_x, max_x, min_y, max_y;
	int intersections = 0;
	
	next_cell.x = directions[(feature->direction+1)%4].x;
	next_cell.y = directions[(feature->direction+1)%4].y;
	next_row.x  = directions[feature->direction].x
	              - next_cell.x*feature->ext.room.size.x;
	next_row.y  = directions[feature->direction].y
	              - next_cell.y*feature->ext.room.size.x;
	
	if(dry) {
		if(!(w->t[feature->pos.y][feature->pos.x].flags & TFLAG_CLEAN))
			return 0;
	} else {
		w->t[feature->pos.y][feature->pos.x].flags &= ~TFLAG_CLEAN;
		w->t[feature->pos.y][feature->pos.x].type = TILE_FLOOR;
	}
	
	pos.x = feature->pos.x + directions[feature->direction].x;
	pos.y = feature->pos.y + directions[feature->direction].y;
	pos.x -= next_cell.x * feature->ext.room.offset;
	pos.y -= next_cell.y * feature->ext.room.offset;
	min_x = max_x = pos.x;
	min_y = max_y = pos.y;
	
	for(yi=0; yi<feature->ext.room.size.y; yi++)
	{
		for(xi=0; xi<feature->ext.room.size.x; xi++)
		{
			// OPTIMIZEME: This bounds check should be outside the loop
			if(!is_in_bounds(pos)) return 0;
			
			if(dry) {
				if(!(w->t[pos.y][pos.x].flags & TFLAG_CLEAN))
					return 0;
			} else {
				w->t[pos.y][pos.x].type = TILE_FLOOR;
				w->t[pos.y][pos.x].flags &= ~TFLAG_CLEAN;
			}
			// OPTIMIZEME: This really ought to be hoisted
			if(pos.x < min_x) min_x = pos.x;
			if(pos.x > max_x) max_x = pos.x;
			if(pos.y < min_y) min_y = pos.y;
			if(pos.y > max_y) max_y = pos.y;
			pos.x += next_cell.x;
			pos.y += next_cell.y;
		}
		pos.x += next_row.x;
		pos.y += next_row.y;
	}
	
	if(dry)
	{
		// Expand by 1, since multiple non-walls there would indicate a
		// collision. Testing isn't done when the border falls outside the
		// or onto the map's outer boundary, since that area is guaranteed to
		// be wall, but not TILE_WALL.
		min_x --; max_x ++;
		min_y --; max_y ++;
		
		// Check walls
		// OPTIMIZEME: Checking bounds *inside* the loop here is just bad
		for(xi=min_x; xi<=max_x; xi++) {
			if(min_y>0 && w->t[min_y][xi].type != TILE_WALL)
				intersections++;
			if(max_y<MAPSIZE_Y-1 && w->t[max_y][xi].type != TILE_WALL)
				intersections++;
		}
		for(yi=min_y; yi<=max_y; yi++) {
			if(min_x>0 && w->t[yi][min_x].type != TILE_WALL)
				intersections++;
			if(max_x<MAPSIZE_X-1 && w->t[yi][max_x].type != TILE_WALL)
				intersections++;
		}
		if(intersections>1) // More collisions than just where it came in
			return 0;
	}
	else
	{
		add_mark(nrandom(max_x, min_x), max_y+1, DIR_DOWN,
			marks, pending, ROOMCONN_RETRIES);
		add_mark(nrandom(max_x, min_x), min_y-1, DIR_UP,
			marks, pending, ROOMCONN_RETRIES);
		add_mark(min_x-1, nrandom(max_y, min_y), DIR_LEFT,
			marks, pending, ROOMCONN_RETRIES);
		add_mark(max_x+1, nrandom(max_y, min_y), DIR_RIGHT,
			marks, pending, ROOMCONN_RETRIES);
	}
	
	return 1;
}
//}}}
//{{{
static int bigmap_place_vault(feature *feature, int dry,
	mark *marks, int *pending)
{
	scoord next_cell, next_row;
	scoord perpendicular_cell;
	scoord pos;
	int xi, yi;
	int direction = feature->direction;
	const vaultdesc *desc = &vaults[feature->ext.vault.vaultid];
	
	next_cell.x = directions[(feature->direction+1)%4].x;
	next_cell.y = directions[(feature->direction+1)%4].y;
	next_row.x  = directions[feature->direction].x
	              - next_cell.x*desc->size.x;
	next_row.y  = directions[feature->direction].y
	              - next_cell.y*desc->size.x;
	perpendicular_cell.x = directions[feature->direction].x;
	perpendicular_cell.y = directions[feature->direction].y;
	
	pos.x = feature->pos.x + directions[feature->direction].x;
	pos.y = feature->pos.y + directions[feature->direction].y;
	pos.x -= next_cell.x * desc->offset.x;
	pos.y -= next_cell.y * desc->offset.x;
	pos.x -= perpendicular_cell.x * desc->offset.y;
	pos.y -= perpendicular_cell.y * desc->offset.y;
	
	for(yi=0; yi<desc->size.y; yi++)
	{
		for(xi=0; xi<desc->size.x; xi++)
		{
			// OPTIMIZEME: This bounds check should be outside the loop
			if(!is_in_bounds(pos)) return 0;
			
			if(dry) {
				if(desc->content[yi*desc->size.x + xi] != '/')
				{
					if(w->t[pos.y][pos.x].type != TILE_WALL)
						return 0;
				}
			} else {
				switch(desc->content[ yi*desc->size.x + xi ])
				{
					case '/':
						break;
					case '2':
						add_mark(pos.x, pos.y, (DIR_DOWN+direction+1)%4,
							marks, pending, ROOMCONN_RETRIES);
						break;
					case '4':
						add_mark(pos.x, pos.y, (DIR_LEFT+direction+1)%4,
							marks, pending, ROOMCONN_RETRIES);
						break;
					case '6':
						add_mark(pos.x, pos.y, (DIR_RIGHT+direction+1)%4,
							marks, pending, ROOMCONN_RETRIES);
						break;
					case '8':
						add_mark(pos.x, pos.y, (DIR_UP+direction+1)%4,
							marks, pending, ROOMCONN_RETRIES);
						break;
					case '#':
						w->t[pos.y][pos.x].flags &= ~TFLAG_CLEAN;
						break;
					case ' ':
						w->t[pos.y][pos.x].type = TILE_FLOOR;
						w->t[pos.y][pos.x].flags &= ~TFLAG_CLEAN;
						break;
					case '+':
						w->t[pos.y][pos.x].type = TILE_CDOOR;
						w->t[pos.y][pos.x].flags &= ~TFLAG_CLEAN;
				}
			}
			pos.x += next_cell.x;
			pos.y += next_cell.y;
		}
		pos.x += next_row.x;
		pos.y += next_row.y;
	}
	return 1;
}
//}}}
//{{{
static void rand_feature(feature *feature, mark *m)
{
	const vaultdesc *vault_desc;
	
	feature->pos = m->pos;
	feature->direction = m->direction;
	if(nrandom(5,1)==1)
		feature->type = FEATURE_CORRIDOR;
	else if(nrandom(2,1)==1)
		feature->type = FEATURE_ROOM;
	else
		feature->type = FEATURE_VAULT;
	
	switch(feature->type)
	{
		case FEATURE_CORRIDOR:
			feature->ext.length = nrandom(CORRIDOR_MAX_LEN, CORRIDOR_MIN_LEN);
			break;
		case FEATURE_ROOM:
			feature->ext.room.size.x = nrandom(ROOMSIZE_MAX_X, ROOMSIZE_MIN_Y);
			feature->ext.room.size.y = nrandom(ROOMSIZE_MAX_X, ROOMSIZE_MIN_Y);
			feature->ext.room.offset = nrandom(feature->ext.room.size.x-1, 0);
			break;
		case FEATURE_VAULT:
			feature->ext.vault.vaultid = nrandom(NUM_VAULT_TYPES-1, 0);
			vault_desc = &vaults[feature->ext.vault.vaultid];
			break;
	}
}
//}}}
//{{{
static void add_mark(int x, int y, int dir, mark *marks, int *pending,
	int retries)
{
	if(*pending >= 512) return;
	marks[*pending].pos.x = x;
	marks[*pending].pos.y = y;
	marks[*pending].direction = dir;
	marks[*pending].retries = retries;
	w->t[y][x].flags |= TFLAG_JUNCTION;
	(*pending)++;
}
//}}}

