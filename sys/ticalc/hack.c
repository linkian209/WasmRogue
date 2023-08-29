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
/* {{{
 * Evil, evil, bastardized, disgusting, vomit-inducing hack ...
 * In response to how the linking system produces larger outputs when code is
 * split into multiple files. Only use when compiling for a calculator. Rather
 * that compile as separate object files and then link, this compiles
 * everything as a single compilation unit.
 * }}} */

#include "main.c"
#include "sysutil.c"
#include "menu.c"
#include "graph.c"

#include "crogue.c"
#include "actions.c"
#include "construct.c"
#include "draw.c"
#include "items.c"
#include "magic.c"
#include "throw.c"
#include "use.c"
#include "monst.c"
#include "pet.c"
#include "player.c"
#include "skill.c"
#include "tiles.c"
#include "files.c"
#include "util.c"
#include "spell.c"
#include "interpret_aux.c"
#include "score.c"
#include "timer.c"
#include "facing.c"
#include "calls.c"
#include "ai.c"
#include "tilefield.c"
#include "messagefield.c"
#include "options.c"
#include "prompt.c"

#include "dll_import.c"
