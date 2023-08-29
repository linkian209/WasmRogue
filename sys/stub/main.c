// main.c
/// @file
/// @brief System-specific initialization and cleanup

#include "crogue.h"

/// @brief Display the title screen background
///
/// The title screen should cover the entire screen and include the version
/// number. (If not all of the screen is covered, clear the remainder.)
void display_title_screen(void) { }

/// @brief Arrange widgets
///
/// Arranges the tilefield, message field, status line, and buttonbar according
/// to font/tile sizes, screen size, etc.
void init_layout(void) { }

/// @brief Do system-specific initialization
void sys_init(void) { }

/// @brief Load the data file into memory.
///
/// Preferrably, this should just get a pointer to the data file in
/// memory-mapped storage without actually copying it.  Should leave
/// w->constfileoffset pointing to the start of the data file, wherever it is.
void sys_init_data_file(void) { }

/// Do system-specific cleanup
void sys_cleanup(void) { }
