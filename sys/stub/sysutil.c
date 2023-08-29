// sysutil.c
/// @file
/// @brief System-specific utility functions

#include "crogue.h"

/// @brief Read a character from input
/// 
/// Input is usually a keyboard, but could include Palm stylus or other input
/// devices.
int read_char(void) { }

/// Check whether a key is waiting to be handled
int key_pending(void) { }

/// @brief Wait so an effect is visible
///
/// @sa DELAY_AMOUNT DELAY_AMOUNT_PC
void delay(void) { }

/// Display a dialog with default size and positioning
void UI_Dialog_Default(const char *content) { }

/// Display a dialog with custom positioning
void UI_Dialog_Display(rect r, const char *content) { }

/// Get the height of the current font
short FontHeight(void) { }

/// Get the width of a character in the current font
short FontWidth(unsigned char c) { }

/// End the program due to a fatal error
void panic(const char *fmt, ...) { }

/// Get a string to represent a key code
const char *get_keyname(short key) { }

