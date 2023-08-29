// graph.c
/// @file
/// @brief System-specific graphics code

#include "crogue.h"

/// Draw a specified tile on the screen.
void Graph_DrawTile(UI_Tilefield *tf, int x, int y, UI_TF_TileInfo tile) { }

/// Clear the screen
void Graph_ClrScr(void) { }

/// Draw a character
void Graph_DrawChar (short x, short y, char c) { }

/// Draw a string
void Graph_DrawStr(short x, short y, const char *str) { }

/// Clear a rectangle (given edge locations)
void Graph_ClearRect(int left, int top, int right, int bottom) { }

