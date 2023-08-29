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
// help.c
/// @file
/// @brief In-game documentation

#include "crogue.h"
#include "dll.h"

#define NUM_HELP_PAGES 5
static const char *help_titles[] = {
	gettext("How to play"),
	gettext("Game Options"),
	gettext("Classes"),
	gettext("Hints"),
	gettext("About")
	};

//{{{
static void helptitlebynum(int N, char *buf)
{
	strcpy(buf, help_titles[N]);
}
//}}}

#ifdef PALMOS
//{{{
static const char *help_palmos =
gettext("How to Play\n"
"\n"
"Your character moves in each of the cardinal directions, plus diagonals."
" To move, tap the stylus near the edge of the screen corresponding to the"
" direction you want to move in. To move more than one space at a time (run),"
" put the stylus in the center of the screen and drag it out to the edge. To"
" scroll the viewport, put the stylus in the center of the screen and draw a"
" squiggle ending with the corresponding edge. To fire a readied arrow, start"
" in the center, drag the stylus out to the edge and then drag it back to the"
" center again.\n"
"\n"
"At the bottom of the screen are buttons for common actions. From left to"
" right, they are: Pick up, Drop, Inventory, Wear, Take off, Use item, Cast"
" spell, Follow stairs, Open door, Close door, Show stats, Show help."
"\n"
"If you are playing a magic user, the first thing you should do is use your"
" spellbook. Later, you can cast spells you have studied by pressing the 'M'"
" button on the button bar.\n"
"\n"
"You start the game in a simple dungeon, so start exploring. Odds are pretty"
" soon, you'll run into a monster, which is represented on the map by a letter"
" which tells you what it is. To attack, simply move onto the monster's"
" square. Your hit points are shown on the status line, at the bottom of the"
" screen.\n"
"\n"
"Your quest is to find and bring back the Amulet of Yendor. Good luck!");
//}}}
#else
//{{{
static const char *help_how_to_play =
gettext("How to Play\n"
"\n"
"At any time, you can press [%s] to get a list of commands and the"
" corresponding keys. This section does not list nearly every possibility. If"
" it occurs to you to do something, check the menu - it's probably there!\n"
"\n"
"Your character moves in each of the cardinal directions, plus diagonals."
" Because of the importance of diagonal movement, the arrow keys are not used;"
" instead, use the number pad. You start the game in a simple dungeon, so start"
" exploring."
"\n"
"Odds are pretty soon, you'll run into a monster, which is represented on the"
" map by a letter which tells you what it is. To attack, simply move onto the"
" monster's square. Your hit points are shown on the status line, at the bottom"
" of the screen. If they get low, run away!\n"
"\n"
"You will see plenty of items lying around, and you start with some useful"
" things as well. Press [%s] to see your current inventory. If you see an item"
" on the map, move onto its square and you"
" will be asked if you want to pick it up. (If you have turned this off, press"
" [%s] to pick up items.) Press [%s] to equip armor and weapons you find, and"
" [%s] to use potions, scrolls, and other items. Be warned that while some "
" items are beneficial, others are enchanted with harmful magic.\n"
"\n"
"If you are playing a magic user, the first thing you should do is use your"
" spellbook. Later, you can cast spells you have studied with [%s].\n"
"\n"
"Your quest is to find and bring back the Amulet of Yendor. Good luck!");
//}}}
#endif
//{{{
static const char *help_classes =
gettext("Classes\n"
"\n"
"Fighter: A simple warrior, skilled with any weapon but not at magic. Fighers"
" are the strongest class.\n"
"\n"
"Wizard: A sorceror, weak with weapons but casting powerful spells. A wizard"
" can't fight well toe-to-toe, but he doesn't need to.\n"
"\n"
"Archer: A marksman, weak in melee but strong at range. An archer moves quickly"
" and shoots accurately.\n"
"\n"
"Priest: A holy warrior, not as well trained in arms as a fighter but with"
" divine powers at his side.\n"
"\n"
"Necromancer: A dark wizard. A necromancer does not often fight, but instead"
" he commands his undead minions to fight for him."
"");
//}}}
//{{{
static const char *help_options =
gettext("Options\n"
"\n"
"Auto-pickup: Controls whether, when moving onto an item, you will"
" automatically pick it up. (default: prompt).\n"
"\n"
"Auto-follow-stairs: If set to yes, when moving onto stairs you will"
" automatically follow them. If set to prompt, you will be asked whether"
" to follow them; if off, you must follow stairs manually (press [%s]"
" (default: prompt).\n"
"\n"
"Tile size (calculator only): Toggles between small (5x5) and large"
" (7x7) tilesets. (default: small).\n"
"\n"
"Font size (calculator only): Toggles between small (4x6) and large"
" (6x8) font. (default: small).\n"
"\n"
"Archive saves (calculator only): If set, saved games and levels will"
" be moved into archive memory. Turn this off if archive memory is full."
" (default: yes).\n"
"\n"
"Archive scores (calculator only): If set, high scores will be moved"
" into archive memory. If this is off, you may lose your high scores"
" when your calculator is reset. (default: yes).\n"
"\n"
"Use grayscale (calculator only): Enables grayscale graphics, which"
" look better but will drain your batteries faster. (default: yes).");
//}}}
//{{{
static const char *help_hints =
gettext("Hints\n"
"\n"
"Some items are useful, some items are harmful, some items are useful if used"
" at the right moment but harmful otherwise. Don't use an item until you have"
" some idea what it is. Try dropping it in a shop, and see how much the"
" shopkeeper offers; that's a big clue to whether the item is good or bad.\n"
"\n"
"When you get into trouble, stop, take a look at your inventory, and think"
" your situation. Most deaths are avoidable, but a scroll of teleportation"
" won't do you any good if you forget you have it!\n"
"\n"
"Never fight a big group all at once. Instead, face them one at a time in a"
" corridor.\n"
"\n"
"Some monsters shouldn't be fought up close, but from a distance with spells or"
" with arrows. In particular, watch out for mimics.\n"
"\n"
"Some monsters can open doors, but some can't. Use this to your advantage.");
//}}}
//{{{
static const char *help_about =
gettext("CalcRogue (" CROGUE_VERSION ")\n"
"by Jim Babcock\n"
"jimmy_b@earthlink.net\n"
"\n"
"This game is postcardware. If you enjoy it, please send the author a"
" postcard at the address below from wherever you live. Feel free to"
" include feature requests and your e-mail address.\n"
"\n"
"  Jim Babcock\n"
"  16 Sweeney Ridge Rd\n"
"  Bedford, Massachusetts\n"
"  01730\n"
"\n"
"This program is released under the GNU General Public License (GPL)."
" Source is available at <http://calcrogue.jimrandomh.org>.\n"
"\n")
#ifdef __TIGCC__
gettext("This build was compiled with ")
	__TIGCC_VERSION_STRING__ gettext(" and ") __TIGCCLIB_VERSION_STRING__ ".\n"
#endif
;
//}}}

#define num_help_menu_tab_stops 2
static void show_help_page(int page);
//{{{
/// Display a menu of manual pages
void help(void)
{
	sint page;
	
	while(1) {
		page = UI_Menu_Pick(help_menu_rect, NUM_HELP_PAGES, &helptitlebynum);
		if(page==-1) break;
		setTabStops(help_menu_tabs);
		show_help_page(page);
	}
}
//}}}
//{{{
static void show_help_page(int page)
{
#ifdef CONSERVE_STACK
	char *buf = debug_malloc(4096);
#else
	char buf[4096];
#endif
	const char *str = buf;
	
	switch(page)
	{
		case 0: // How to play
#ifndef PALMOS
			sprintf(buf, help_how_to_play,
				get_keyname(KEY_ACT_MENU),
				get_keyname(KEY_INVENTORY),
				get_keyname(KEY_PICKUP),
				get_keyname(KEY_WEAR),
				get_keyname(KEY_USE),
				get_keyname(KEY_CAST) );
#else
			str = help_palmos;
#endif
			break;
		case 1: // Classes
			sprintf(buf, help_options,
				get_keyname(KEY_STAIR));
			break;
		case 2: // Options 
			str = help_classes;
			break;
		case 3: // Hints
			str = help_hints;
			break;
		case 4: // About
			str = help_about;
			break;
	}
	UI_Dialog_Display(default_dialog_rect, str);
#ifdef CONSERVE_STACK
	free(buf);
#endif
}
//}}}
