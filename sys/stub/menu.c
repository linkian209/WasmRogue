// menu.c
/// @file
/// @brief System-specific code to display a menu and get the user's selection

#include "crogue.h"

/// @brief Set persistent menu option
///
/// Sets whether the menu should keep the same selection the next time it is
/// opened (for use when the user picks multiple choices from the same menu.)
void UI_Menu_Set_Persist(ushort p) { }

/// @brief Display a menu
///
/// Displays a menu and wait for the user to choose something. @a r is the
/// rectangle in which the menu will be displayed, @a getchoice is a callback
/// for the string representing the Nth choice.
int UI_Menu_Pick( rect r, int numchoices, void (*getchoice)(int N, char *buf)){}

