#ifndef POSITIONS_H
#define POSITIONS_H

#define main_menu_rect   RECT(3,  100, 55,  42)
#define class_menu_rect  RECT(54, 100, 57,  35)
#define debug_rect       RECT(20, 20, 80,  90)
#define debug_item_rect  RECT(10, 20, SCREEN_WIDTH-20, 100)
#define default_dialog_rect RECT(5, 20, 150, 120)
#define inventory_rect   RECT(7,  24, 142, 129)
#define learn_spell_rect RECT(7,  24, 142, 129)
#define cast_spell_rect  RECT(7,  24, 142, 129)
#define options_rect     RECT(10, 20, 120, 80)
#define actions_rect     RECT(7,  24, 142, 129)
#define help_menu_rect   RECT(7,  24, 142, 129)
#define controls_menu_rect options_rect
#define pen_actions_rect RECT(70, 25, 40, 40)
#define button_actions_rect RECT(70, 20, 40, 80)

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
