#include "crogue.h"

int err_pending = 0;
const SCR_RECT fullScreen = (SCR_RECT){{0, 0, 159, 99}};

//{{{
void _main(void)
{
	ERROR_FRAME __errFrame;
	volatile unsigned short errCode;
	saved_screen = alloca(sizeof(LCD_BUFFER));
	LCD_save(saved_screen);
	err_pending = 1;
	errCode=ER_catch(__errFrame);
	if(!errCode)
	{
		clrscr();
		initialize();
		eventloop();
		err_pending = 0;
		ER_success();
	}else{
		register short _ONERR_=1;
#ifdef REGISTERVAR
		w = w_non_reg;
#endif
#ifdef DEBUG_HEAVILY
		clrscr();
		printf_xy(0, 0, "Exception thrown: %i!", errCode);
		ngetchx();
#endif
		cleanup();
		_ONERR_=0;
	}
}
//}}}

//{{{
void display_title_screen(void)
{
	if(GrayCheckRunning())
	{
		GraySetAMSPlane(DARK_PLANE);
		BitmapPut(0, 0, deref_file_ptr(w->desc.titlescreen_dark_plane),
		          &fullScreen, A_REPLACE);
		GraySetAMSPlane(LIGHT_PLANE);
		BitmapPut(0, 0, deref_file_ptr(w->desc.titlescreen_light_plane),
		          &fullScreen, A_REPLACE);
	} else {
		BitmapPut(0, 0, deref_file_ptr(w->desc.titlescreen_dark_plane),
		          &fullScreen, A_REPLACE);
	}
	
	Graph_DrawStr_Reverse(100, 93, CROGUE_VERSION);
}
//}}}
//{{{
void init_layout(void)
{
	uint tilefield_top, tilefield_bottom;
	uint tilefield_height;
	uint tilefield_width;
	uint tile_size;
	uint status_pos;
	const char *tileset;
	
	switch(get_option(OPTION_TILESIZE))
	{
		default:
			tileset = tiles_5x5;
			tile_size = 5;
			break;
		case OPTION_SIZE_LARGE:
			tileset = tiles_7x7;
			tile_size = 7;
			break;
	}

	switch(get_option(OPTION_FONTSIZE))
	{
		default:
			status_pos = SCREEN_HEIGHT - 7;
			tilefield_top = 12;
			break;
		case OPTION_FONT_MEDIUM:
			status_pos = SCREEN_HEIGHT - 8;
			tilefield_top = 14;
			break;
		case OPTION_FONT_LARGE:
			status_pos = SCREEN_HEIGHT - 9;
			tilefield_top = 16;
			break;
	}
	tilefield_bottom = status_pos - 1;
	tilefield_height = tilefield_bottom-tilefield_top + 1;
	
	tilefield_width = SCREEN_WIDTH/tile_size;
	
	UI_MF_Place(0, 2);
	UI_Status_Place(status_pos, SCREEN_HEIGHT-status_pos);
	
	UI_TF_Place(
			COORD(0, tilefield_top),
			COORD(SCREEN_WIDTH, tilefield_height),
			tileset,
			tile_size, tile_size
			);
}
//}}}

LCD_BUFFER *saved_screen;

//{{{
static INT_HANDLER OldInt1;
static int interrupt_installed = 0;
DEFINE_INT_HANDLER(HideStatKeys)
{
	char buffer[5*30]; //the status indicators are five pixels tall
	memcpy(buffer, (char *)LCD_MEM + 30*(SCREEN_HEIGHT-5), 5 * 30); //store five lines, starting five lines up from the bottom.
	ExecuteHandler(OldInt1); //Let the AMS have its day in the sun
	memcpy((char *)LCD_MEM + 30*(SCREEN_HEIGHT-5), buffer, 5 * 30); //copy the lines back
}
//}}}

//{{{
void sys_init(void)
{
	OldInt1 = GetIntVec(AUTO_INT_1);
	
	SetIntVec(AUTO_INT_1, HideStatKeys);
	interrupt_installed = 1;
	if(AMS_2xx)
		SetAlphaStatus(FALSE);
	SetFont(OPTION_FONT_SMALL);
}
//}}}

uchar *const_file[8];
HANDLE const_file_handle[8];

//{{{
void sys_init_data_file(void)
{
	int dllret, ii;
	const ulong *current_segment;
	HSym datfile;
	char data_filename[16] = DATAFILENAME "1";
	unsigned num_segments = 1;
	
	ii=0;
	do
	{
		sprintf(data_filename, DATAFILENAME "%i", ii+1);
		datfile = SymFind(SYMSTR(data_filename));
		const_file_handle[ii] = H_NULL;
		
		if(datfile.folder==0)
			panic("Data file not found.");
		const_file_handle[ii] = DerefSym(datfile)->handle;
		current_segment = HLock(const_file_handle[ii]) + 2;
		if(ii==0)
		{ // First segment has the segment count
			num_segments = *(current_segment++);
		}
		const_file[ii] = (void*)current_segment;
		ii++;
	}
	while(ii < num_segments);
	
	w->const_file = const_file;
	w->num_segments = num_segments;
	
	memcpy(&w->desc, const_file[0], sizeof(struct world_descriptor));
	
	// Load DLL
	dllret = LoadDLL(DLLFILENAME, DLL_IDENTIFICATION_NUMBER, CROGUE_VERSION_MAJOR, CROGUE_VERSION_MINOR);
	switch(dllret)
	{
		case DLL_OK:
			break;
		case DLL_OUTOFMEM:
			panic("Ran out of memory loading DLL.");
			break;
		case DLL_NOTFOUND:
			panic("DLL not found.");
			break;
		case DLL_LOCKFAILED:
			panic("Couldn't lock DLL.");
			break;
		case DLL_WRONGVERSION:
			panic("DLL is wrong version.");
			break;
		default:
			panic(retprintf("Unknown error loading DLL: %i", dllret));
			break;
	}
	
	link_data_file();
}
//}}}
//{{{
void sys_cleanup(void)
{
	int ii;
	
	if(err_pending) {
		ER_success();
		err_pending = 0;
	}
	
	if(w) {
		for(ii=0; ii<w->num_segments; ii++)
			HeapUnlock(const_file_handle[ii]);
		w->num_segments = 0;
	}
	
	UnloadDLL();
	
	GrayOff();
	if(interrupt_installed)
		SetIntVec(AUTO_INT_1, OldInt1);
	LCD_restore(saved_screen);
}
//}}}

