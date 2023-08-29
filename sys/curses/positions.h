#ifndef POSITIONS_H
#define POSITIONS_H

#define default_dialog_rect RECT(5, 0, 70, 23)
#define main_menu_rect   RECT(4,  6,  19, 8)
#define class_menu_rect  RECT(4,  13, 19, 7)
#define inventory_rect   RECT(0,  2,  80, 20)
#define learn_spell_rect RECT(0,  2,  80, 20)
#define cast_spell_rect  RECT(0,  2,  80, 20)
#define options_rect     RECT(10, 5,  60, 13)
#define actions_rect     RECT(3,  3,  70, 20)
#define help_menu_rect   RECT(10, 3,  60, 20)
#define debug_rect       RECT(10, 3,  60, 10)
#define debug_item_rect  RECT(10, 2,  60, 20)

// See drawstring.c for rules on how to define tab stops
#define item_tab_stops             3, 0, 6, 15
#define actions_menu_tab_stops     2, 0, 50
#define discovery_screen_tab_stops 3, 0, 40, 80
#define options_menu_tabs          2, 0, 35
#define player_screen_tabs         3, 0, 20, 25
#define spell_menu_tabs            4, 0, 6, 48, 55
#define help_menu_tabs             2, 0, 50


#endif
