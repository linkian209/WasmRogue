#ifndef POSITIONS_H
#define POSITIONS_H

#define main_menu_rect   RECT(3,  60, 45,  38)
#define class_menu_rect  RECT(44, 60, 52,  35)
#define debug_rect       RECT(20, 20, 60,  50)
#define debug_item_rect  RECT(10, 20, SCREEN_WIDTH-20, 50)

#ifdef USE_TI89
#define default_dialog_rect RECT(5, 5, 150, 90)
#define inventory_rect   RECT(7,  14, 142, 79)
#define learn_spell_rect RECT(7,  14, 142, 79)
#define cast_spell_rect  RECT(7,  14, 142, 79)
#define options_rect     RECT(10, 20, 120, 50)
#define actions_rect     RECT(7,  14, 142, 79)
#define help_menu_rect   RECT(7,  14, 142, 79)
#endif
#ifdef USE_TI92P
#define default_dialog_rect RECT(45, 15, 150, 90)
#define inventory_rect   RECT(27, 19, 162, 82)
#define learn_spell_rect RECT(27, 20, 142, 79)
#define cast_spell_rect  RECT(27, 20, 142, 79)
#define options_rect     RECT(10, 20, 120, 50)
#define actions_rect     RECT(87, 19, 142, 105)
#define help_menu_rect   RECT(47, 19, 142, 79)
#endif

// See drawstring.c for rules on how to define tab stops
// First number is the *number of tab stops*. The remaining numbers are the
// stops themselves. Zero is always the first tab stop.
#define item_tab_stops             3, 0, 6, 15
#define actions_menu_tab_stops     2, 0, 115
#define discovery_screen_tab_stops 3, 0, 70, 100
#define options_menu_tabs          2, 0, 90
#define player_screen_tabs         3, 0, 50, 60
#define spell_menu_tabs            4, 0, 6, 80, 100
#define help_menu_tabs             2, 0, 115

#endif

