#include "crogue.h"

int high_density_font=0;
int monochrome_screen=0;
int game_running = 0;
int game_repeat = 0;

void use_stack(void *stack, long stacksize, void(*func)(void)) SEG(0);
static void _main(void);

//{{{
UInt32 PilotMain(UInt16 cmd, void *cmdPBP, UInt16 launchFlags)
{
	void *stack;
	
	if(cmd != sysAppLaunchCmdNormalLaunch)
		return 0;
	
	stack = debug_malloc(16384);
	if(stack==NULL)
		return 1;
	use_stack(stack, 16384, _main);
	free(stack);
	
	return 0;
}
//}}}
//{{{
static void _main(void)
{
	do
	{
		game_repeat = 0;
		
		ErrTry
		{
			initialize();
			eventloop();
		}
		ErrCatch(inErr)
		{
			(void)inErr;
		} ErrEndCatch
	} while(game_repeat);
}
//}}}
//{{{
void display_title_screen(void)
{
	MemHandle bitmap_handle = DmGetResource('Tbmp', bitmap_splash);
	BitmapType *bitmap = MemHandleLock(bitmap_handle);
	WinDrawBitmap(bitmap, 0, 0);
	MemHandleUnlock(bitmap_handle);
}
//}}}
//{{{
asm (
".section sec_0\n"
"use_stack:\n"
"	move.l 4(%a7),%a0\n"  // Take parameters
"	add.l  8(%a7),%a0\n"  // a0=stack, a1=func
"	move.l 12(%a7),%a1\n"

"	move.l %a6,-(%a0)\n"  // push a6,a7 onto new stack
"	move.l %a7,-(%a0)\n"
"	move.l %a0,%a6\n"     // Set a6,a7 to point to new stack
"	move.l %a0,%a7\n"

"	jsr (%a1)\n"         // call a1

"	move.l 4(%a7),%a6\n"  // pop -> a6, a7
"	move.l (%a7),%a0\n"
"	move.l %a0,%a7\n"
"	rts\n"
);
//}}}

int color_lit, color_unlit, color_unexplored;
int color_red,     color_lred,
    color_green,   color_lgreen,
    color_yellow,  color_lyellow,
    color_blue,    color_lblue,
    color_magenta, color_lmagenta,
    color_cyan,    color_lcyan,
    color_white,   color_lwhite;
MemHandle *const_file_handle = NULL;

//{{{
void sys_init(void)
{
	Err error;
	UInt32 density;
	UInt32 version;
	UInt32 winVersion;
	UInt32 depths;
	UInt32 use_depth, width, height;
	Boolean use_color;
	int ii;
	MemHandle fontHandle;
	FontType *fontPtr = NULL;
	
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &version);
	
	// Set the highest-available color depth
	if(version >= 0x3503000UL) // PalmOS 3.5 with color support
	{
		WinScreenMode(winScreenModeGetDefaults, &width, &height, &use_depth, &use_color);
		WinScreenMode(winScreenModeGetSupportedDepths, NULL, NULL, &depths, NULL);
		for(ii=15; ii>=0; ii--) {
			if(depths & (1U<<ii)) {
				use_depth = ii+1;
				break;
			}
		}
		WinScreenMode(winScreenModeSet, &width, &height, &use_depth, &use_color);
	}
	
	// Load fonts, either in high- or regular-density versions depending on
	// the hardware.
	error = FtrGet(sysFtrCreator, sysFtrNumWinVersion, &winVersion);
	if(!error && winVersion>=4) {
		error = WinScreenGetAttribute(winScreenDensity, &density);
		if(!error && density != kDensityLow) {
			high_density_font = 1;
			
			// Load itsy font
			fontHandle = DmGetResource('nfnt', FONT_8_12);
			fontPtr = MemHandleLock(fontHandle);
			FntDefineFont(TextFont, fontPtr);
			
			// Load tile font
			fontHandle = DmGetResource('nfnt', TILE_5_5);
			fontPtr = MemHandleLock(fontHandle);
			FntDefineFont(TileFont, fontPtr);
		}
	}
	if(!fontPtr) {
		if (version >= 0x03000000L) {
			high_density_font = 0;
			
			// Load itsy font (low-density)
			fontHandle = DmGetResource('NFNT', FONT_5_6);
			fontPtr = MemHandleLock(fontHandle);
			FntDefineFont(TextFont, fontPtr);
			
			// Load tile font (low-density)
			fontHandle = DmGetResource('NFNT', TILE_5_5S);
			fontPtr = MemHandleLock(fontHandle);
			FntDefineFont(TileFont, fontPtr);
		}
	}
	FntSetFont(TextFont);
	
	init_colors();
	
	FrmGotoForm(MainForm);
	handle_events();
}
//}}}
//{{{
void init_colors(void)
{
	int white, lgray, dgray, black;
	
	// First, check that this device has an OS new enough to support color
	UInt32 version = 0;
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &version);
	if(version < 0x3503000UL) { // PalmOS 3.5 with color support
		monochrome_screen = 1;
		return;
	}
	
	white = getColor(0xFF, 0xFF, 0xFF);
	lgray = getColor(0x99, 0x99, 0x99);
	dgray = getColor(0x55, 0x55, 0x55);
	black = getColor(0x00, 0x00, 0x00);
	
	if(black == dgray || white == lgray)
		// Suspiciously few colors...
	{
		monochrome_screen = 1;
		return;
	}
	
	// Set up colors
	if(get_option(OPTION_INVERSE) != OPTION_YES)
	{
		color_lit = white;
		color_unlit = lgray;
		color_unexplored = dgray;
		
		color_red      = getColor(0x99, 0x00, 0x00);
		color_lred     = getColor(0x99, 0x00, 0x00);
		color_green    = getColor(0x00, 0x99, 0x00);
		color_lgreen   = getColor(0x00, 0x99, 0x00);
		color_yellow   = getColor(0x66, 0x44, 0x00);
		color_lyellow  = getColor(0x99, 0x66, 0x00);
		color_blue     = getColor(0x00, 0x00, 0x99);
		color_lblue    = getColor(0x00, 0x00, 0x99);
		color_magenta  = getColor(0x99, 0x00, 0x99);
		color_lmagenta = getColor(0x99, 0x00, 0x99);
		color_cyan     = getColor(0x00, 0x99, 0x99);
		color_lcyan    = getColor(0x00, 0x99, 0x99);
		color_white    = getColor(0x00, 0x00, 0x00);
		color_lwhite   = getColor(0x22, 0x22, 0x22);
		
		WinSetTextColor(black);
		WinSetForeColor(black);
		WinSetBackColor(white);
	}
	else
	{
		color_lit        = getColor(0x22, 0x22, 0x22);
		color_unlit      = getColor(0x00, 0x00, 0x00);
		color_unexplored = getColor(0x33, 0x33, 0x33);
		
		color_red      = getColor(0x99, 0x00, 0x00);
		color_lred     = getColor(0xFF, 0x00, 0x00);
		color_green    = getColor(0x00, 0x99, 0x00);
		color_lgreen   = getColor(0x00, 0xFF, 0x00);
		color_yellow   = getColor(0x99, 0x66, 0x00);
		color_lyellow  = getColor(0xFF, 0xFF, 0x33);
		color_blue     = getColor(0x00, 0x00, 0x99);
		color_lblue    = getColor(0x00, 0x00, 0xFF);
		color_magenta  = getColor(0xCC, 0x00, 0xCC);
		color_lmagenta = getColor(0xFF, 0x44, 0xFF);
		color_cyan     = getColor(0x00, 0x99, 0x99);
		color_lcyan    = getColor(0x00, 0xFF, 0xFF);
		color_white    = getColor(0x99, 0x99, 0x99);
		color_lwhite   = getColor(0xFF, 0xFF, 0xFF);
		
		WinSetTextColor(getColor(0xAA, 0xAA, 0xAA));
		WinSetForeColor(getColor(0xAA, 0xAA, 0xAA));
		WinSetBackColor(black);
	}
}
//}}}
//{{{
void sys_cleanup(void)
{
	MemHandle fontHandle;
	int ii;
	
	if(high_density_font) {
		fontHandle = DmGetResource('nfnt', FONT_8_12);
		MemHandleUnlock(fontHandle);
		fontHandle = DmGetResource('nfnt', TILE_5_5);
		MemHandleUnlock(fontHandle);
	} else {
		fontHandle = DmGetResource('NFNT', FONT_5_6);
		MemHandleUnlock(fontHandle);
		fontHandle = DmGetResource('NFNT', TILE_5_5S);
		MemHandleUnlock(fontHandle);
	}
	
	if(const_file_handle) {
		for(ii=0; ii<w->num_segments; ii++) {
			MemHandleUnlock(const_file_handle[ii]);
			DmReleaseResource(const_file_handle[ii]);
		}
		free(const_file_handle);
		const_file_handle = NULL;
	}
	if(w->const_file)
		free(w->const_file);
	
	FrmCloseAllForms();
}
//}}}
//{{{
void init_layout(void)
{
	uint tile_width = 5,
	     tile_height = 5;
	uint message_rows = 3;
	const char *tileset = tiles;
	
	int screen_top = 0;
	int screen_bottom = SCREEN_HEIGHT;
	
	screen_bottom -= 10; // Make room for bottonbar
	
	UI_MF_Place(0, message_rows);
	screen_top += message_rows * FontHeight();
	
	screen_bottom -= FontHeight();
	UI_Status_Place(screen_bottom, FontHeight());
	
	UI_TF_Place( COORD(0, screen_top),
	             COORD(SCREEN_WIDTH, screen_bottom-screen_top-1),
	             tileset, tile_height, tile_width );
}
//}}}
//{{{
void sys_init_data_file(void)
{
//	data_file_handle = DmGetResource('CRdt', DataFile);
//	if(!data_file_handle) panic("Couldn't fetch data file");
//	w->constfileoffset = MemHandleLock(data_file_handle);
//	if(!w->constfileoffset) panic("Couldn't lock data file");
//	memcpy(&w->desc, w->constfileoffset, sizeof(struct world_descriptor));
	
	MemHandle segment;
	ulong *segment_data;
	ulong num_segments;
	unsigned ii;
	
	// Load the first segment, which has the segment count at the beginning
	segment = DmGetResource('CRdt', DataFile);
	if(!segment) panic("Couldn't fetch data file's first segment");
	segment_data = MemHandleLock(segment);
	if(!segment_data) panic("Couldn't lock data file's first segment");
	
	// Read the segment count
	num_segments = *segment_data;
	segment_data++;  // Skip over the segment count
	w->num_segments = num_segments;
	
	// Allocate space for segment information
	w->const_file = (uchar**)calloc( num_segments, sizeof(uchar*) );
	const_file_handle = (MemHandle*)calloc( num_segments, sizeof(MemHandle) );
	
	// Fill in the first (already-read) segment
	w->const_file[0] = (uchar*)segment_data;
	const_file_handle[0] = segment;
	
	// Load the other segments
	for(ii=1; ii<num_segments; ii++)
	{
		segment = DmGetResource('CRdt', DataFile+ii);
		if(!segment) panic("Couldn't fetch data file");
		segment_data = MemHandleLock(segment);
		if(!segment_data) panic("Couldn't lock data file");
		
		w->const_file[ii] = (uchar*)segment_data;
		const_file_handle[ii] = segment;
	}
	
	memcpy(&w->desc, w->const_file[0], sizeof(struct world_descriptor));
	link_data_file();
}
//}}}

//{{{
void PalmExit(int ret)
{
	ErrThrow(0);
}
//}}}

