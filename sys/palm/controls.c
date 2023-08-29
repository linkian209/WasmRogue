#include "crogue.h"

directional_action pen_actions[NUM_DIRECTIONAL_ACTIONS] =
	{ direction_walk, direction_run, direction_fire, direction_scroll };
const char *pen_action_names[NUM_DIRECTIONAL_ACTIONS] =
	{ "Walk", "Run", "Fire", "Scroll" };

#define NUM_BUTTON_ACTIONS 19
int button_actions[NUM_BUTTON_ACTIONS] =
	{ 0,
	  KEY_RUN, KEY_FIRE, KEY_SCROLL_PROMPT,
	  KEY_SEARCH, KEY_PICKUP, KEY_DROP, KEY_CAST, KEY_USE,
	  KEY_INVENTORY, KEY_WEAR, KEY_TAKEOFF, KEY_THROW, KEY_INVENTORY,
	  KEY_SOUTH, KEY_WEST, KEY_EAST, KEY_NORTH, KEY_STAIR
	};
const char *button_action_names[NUM_BUTTON_ACTIONS] =
	{ "Ignore",
	  "Run", "Fire", "Scroll",
	  "Search", "Pickup", "Drop", "Spell", "Use",
	  "Inventory", "Wear", "Take off", "Throw", "Inventory",
	  "South", "West", "East", "North", "Up/Down"
	  };

const char *pen_stroke_names[4] =
	{ "Tap pen", "Drag pen", "Drag and return", "Squiggle pen" };

#define NUM_HARDBUTTONS 8
const char *hardbutton_names[NUM_HARDBUTTONS] =
	{ "Datebook", "Address", "Todo", "Memos",
	  "Page Up", "Page Down", "Calculator", "Find",
//	  "Rocker Left", "Rocker Right", "Rocker Center"
	};

//{{{
static void pen_config_menu(int N, char *buf)
{
	const char *action="", *value="";
	int actionid;
	
	if(N < NUM_DIRECTIONAL_ACTIONS) {
		actionid = get_option(N|OPTION_PEN_PREFIX);
		if(actionid == -1) actionid = N;
		
		action = pen_stroke_names[N];
		value = pen_action_names[actionid];
		
		sprintf(buf, "%s\t%s", action, value);
	} else {
		actionid = get_option(N|OPTION_PEN_PREFIX);
		if(actionid == -1) actionid = TAP_CENTER_DEFAULT;
		value = button_action_names[actionid];
		
		switch(N)
		{
			default:
				sprintf(buf, "Tap center\t%s", value);
				break;
		}
	}
}
//}}}
//{{{
static void pen_action_menu(int N, char *buf)
{
	strcpy(buf, pen_action_names[N]);
}
//}}}
//{{{
static void button_config_menu(int N, char *buf)
{
	const char *value="";
	int actionid;
	
	actionid = get_option(-(N+1) & 0xFFFF);
	if(actionid == -1) actionid = 0;
	value = button_action_names[actionid];
	
	sprintf(buf, "%s\t%s", hardbutton_names[N], value);
}
//}}}
//{{{
static void button_actions_menu(int N, char *buf)
{
	strcpy(buf, button_action_names[N]);
}
//}}}
//{{{
void configure_pen(void)
{
	int ret;
	int new_val;
	do {
		ret = UI_Menu_Pick(controls_menu_rect, NUM_DIRECTIONAL_ACTIONS+1,
			&pen_config_menu);
		
		if(ret==-1) break;
		
		switch(ret)
		{
			default:
				new_val=UI_Menu_Pick(pen_actions_rect, NUM_DIRECTIONAL_ACTIONS,
					&pen_action_menu);
				break;
			case 4:
				new_val = UI_Menu_Pick(button_actions_rect, NUM_BUTTON_ACTIONS,
					&button_actions_menu);
				break;
		}
		if(new_val != -1)
			set_option(ret|OPTION_PEN_PREFIX, new_val);
	}
	while(1);
}
//}}}
//{{{
void configure_buttons(void)
{
	int ret;
	int new_val;
	do {
		ret = UI_Menu_Pick(controls_menu_rect, NUM_HARDBUTTONS,
			&button_config_menu);
		
		if(ret==-1) break;
		
		new_val = UI_Menu_Pick(button_actions_rect, NUM_BUTTON_ACTIONS,
			&button_actions_menu);
		if(new_val != -1)
			set_option(-(ret+1) & 0xFFFF, new_val);
	}
	while(1);
}
//}}}

//{{{
int direction_walk(int dx, int dy)
{
	if(dy < 0) {
		if(dx > 0)     return KEY_NORTHEAST;
		else if(dx==0) return KEY_NORTH;
		else           return KEY_NORTHWEST;
	}
	else if(dy == 0) {
		if(dx > 0)     return KEY_EAST;
		else if(dx==0) return KEY_WAIT;
		else           return KEY_WEST;
	}
	else {
		if(dx > 0)     return KEY_SOUTHEAST;
		else if(dx==0) return KEY_SOUTH;
		else           return KEY_SOUTHWEST;
	}
}
//}}}
//{{{
int direction_run(int dx, int dy)
{
	if(dy < 0) {
		if(dx > 0)     return KEY_RUN_NORTHEAST;
		else if(dx==0) return KEY_RUN_NORTH;
		else           return KEY_RUN_NORTHWEST;
	}
	else if(dy == 0) {
		if(dx > 0)     return KEY_RUN_EAST;
		else if(dx==0) return KEY_WAIT;
		else           return KEY_RUN_WEST;
	}
	else {
		if(dx > 0)     return KEY_RUN_SOUTHEAST;
		else if(dx==0) return KEY_RUN_SOUTH;
		else           return KEY_RUN_SOUTHWEST;
	}
}
//}}}
//{{{
int direction_fire(int dx, int dy)
{
	if(dy < 0) {
		if(dx > 0)     return KEY_FIRE_NORTHEAST;
		else if(dx==0) return KEY_FIRE_NORTH;
		else           return KEY_FIRE_NORTHWEST;
	}
	else if(dy == 0) {
		if(dx > 0)     return KEY_FIRE_EAST;
		else if(dx==0) return KEY_WAIT;
		else           return KEY_FIRE_WEST;
	}
	else {
		if(dx > 0)     return KEY_FIRE_SOUTHEAST;
		else if(dx==0) return KEY_FIRE_SOUTH;
		else           return KEY_FIRE_SOUTHWEST;
	}
}
//}}}
//{{{
int direction_scroll(int dx, int dy)
{
	if(dy < 0) {
		if(dx > 0)     return KEY_SCROLL_UPRIGHT;
		else if(dx==0) return KEY_SCROLL_UP;
		else           return KEY_SCROLL_UPLEFT;
	}
	else if(dy == 0) {
		if(dx > 0)     return KEY_SCROLL_RIGHT;
		else if(dx==0) return 0;
		else           return KEY_SCROLL_LEFT;
	}
	else {
		if(dx > 0)     return KEY_SCROLL_DOWNRIGHT;
		else if(dx==0) return KEY_SCROLL_DOWN;
		else           return KEY_SCROLL_DOWNLEFT;
	}
}
//}}}

//{{{
int pen_tap_center(void)
{
	int actionid = get_option(NUM_DIRECTIONAL_ACTIONS|OPTION_PEN_PREFIX);
	if(actionid == -1)
		actionid = TAP_CENTER_DEFAULT;
	return button_actions[actionid];
}
//}}}
//{{{
int hard_button(int button)
{
	int action;
	action = get_option(-(button+1) & 0xFFFF);
	return button_actions[action];
}
//}}}
//{{{
int should_trap_button(int button)
{
	int action;
	action = get_option(-(button+1) & 0xFFFF);
	return action > 0;
}
//}}}

//{{{
void options_submenu(int n, char *buf)
{
	switch(n)
	{
		default:
		case 0: strcpy(buf, "Configure pen\t..."); break;
		case 1: strcpy(buf, "Configure buttons\t..."); break;
	}
}
//}}}
//{{{
void pick_submenu(int choice)
{
	if(choice==0) {
		configure_pen();
	} else if(choice==1) {
		configure_buttons();
	}
}
//}}}


