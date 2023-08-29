#include "crogue.h"
#include "export.h"

static int menu_key(int selection) SEG(3);

static EventType event_buf;
static short event_queued=0;
//{{{
void UEvtGetEvent(EventType *event, Int32 timeout)
{
	if(event_queued) // Event retrieved with EventUnreadEvent waiting
	{
		*event = event_buf;
		event_queued = 0;
	} else {
		EvtGetEvent(event, timeout);
	}
}
//}}}
//{{{
void UEvtUnreadEvent(EventType *event)
{
	event_buf = *event;
	event_queued = 1;
}
//}}}
//{{{
Boolean UEvtEventAvail(void)
{
	return event_queued || EvtEventAvail();
}
//}}}

//{{{
int retrieve_event(EventType *event)
{
	Err error;
	
	while(EvtEventAvail())
	{
		UEvtGetEvent(event, evtWaitForever);
		if(SysHandleEvent(event)) continue;
		if(MenuHandleEvent(NULL, event, &error)) continue;
		return 1;
	}
	return 0;
}
//}}}
//{{{
void retrieve_event_block(EventType *event)
{
	Err error;
	
	while(1)
	{
		UEvtGetEvent(event, evtWaitForever);
		if(SysHandleEvent(event)) continue;
		if(MenuHandleEvent(NULL, event, &error)) continue;
		break;
	}
}
//}}}
//{{{
Boolean FormEventHandler(EventType *ev)
{
	static FormType *current_form;
	
	switch(ev->eType)
	{
		case frmOpenEvent:
			current_form = FrmGetActiveForm();
			FrmDrawForm(current_form);
			return true;
		case frmCloseEvent:
			FrmEraseForm(current_form);
			FrmDeleteForm(current_form);
			current_form = NULL;
			return true;
			
		default:
			return false;
	}
}
//}}}
//{{{
int default_event_handler(EventType *ev)
{
	UInt16 error;
	FormType *form;
	
	if(SysHandleEvent(ev)) return 1;
	if(MenuHandleEvent(NULL, ev, &error)) return 1;
	
	switch(ev->eType)
	{
		case frmLoadEvent:
			form = FrmInitForm(ev->data.frmLoad.formID);
			FrmSetActiveForm(form);
			FrmSetEventHandler(form, FormEventHandler);
			break;
		case appStopEvent:
			if(game_running)
				save_game();
			cleanup();
			exit(0);
			break;
		default:
			FrmDispatchEvent(ev);
			break;
	}
	return 0;
}
//}}}
//{{{
void handle_events(void)
{
	EventType event;
	
	while(EvtEventAvail())
	{
		UEvtGetEvent(&event, 0);
		default_event_handler(&event);
	}
}
//}}}
//{{{
int read_char(void)
{
	UInt16 error;
	EventType event;
	int ret;
	int button_num;
	
	do {
		UEvtGetEvent(&event, evtWaitForever);
		
		if(event.eType == keyDownEvent)
			// Handle this *before* passing it to the system, to be able to trap
			// hard buttons
		{
			switch (event.data.keyDown.chr) {
				default:          button_num = -1; break;
				
				case hard1Chr:    button_num = 0; break;
				case hard2Chr:    button_num = 1; break;
				case hard3Chr:    button_num = 2; break;
				case hard4Chr:    button_num = 3; break;
				case pageUpChr:   button_num = 4; break;
				case pageDownChr: button_num = 5; break;
				case calcChr:     button_num = 6; break;
				case findChr:     button_num = 7; break;
				
/*				case 0x0503:
					// Something's *very* weird with this keycode (which seems
					// to be used for everything involving the 5-way
					// navigator). I don't know what's going on, but until I
					// figure it out, this hack stands. FIXME.
					if(event.data.keyDown.modifiers == 0x0004) // Rocker *left*
						button_num = 8;
					else if(event.data.keyDown.modifiers == 0x0800)   // *right*
						button_num = 9;
					else { // Somewhere weird
						message("[503 %li]", (long)event.data.keyDown.modifiers);
						button_num = -1;
					}
					break;*/
			}
			if(button_num>=0 && should_trap_button(button_num))
				return hard_button(button_num);
		}
		
		if(SysHandleEvent(&event)) continue;
		if(MenuHandleEvent(NULL, &event, &error)) continue;
		
		switch(event.eType)
		{
			case menuEvent:
				return menu_key(event.data.menu.itemID);
			case keyDownEvent:
				return event.data.keyDown.chr;
			case penDownEvent:
				ret = event_pen_down(event.screenX, event.screenY);
				if(ret) return ret;
				break;
			case penMoveEvent:
				event_pen_move(event.screenX, event.screenY);
				break;
			case penUpEvent:
				ret = event_pen_up(event.screenX, event.screenY);
				if(ret) return ret;
				break;
			default: break;
		}
		default_event_handler(&event);
	} while(1);
}
//}}}
//{{{
int key_pending(void)
{
	EventType ev;
	
	while(UEvtEventAvail())
	{
		UEvtGetEvent(&ev, 0);
		switch(ev.eType)
		{
			case nilEvent:
				break;
			default:
				UEvtUnreadEvent(&ev);
				return 1;
		}
	}
	return 0;
}
//}}}
//{{{
static int menu_key(int selection)
{
	switch(selection)
	{
		case menucmd_options:     return KEY_OPTIONS_MENU;
		case menucmd_help:        return KEY_HELPMENU;
		case menucmd_about:       return KEY_ABOUT;
		case menucmd_debug:       return KEY_DEBUG;
		case menucmd_redraw:      return KEY_REDRAW;
		case menucmd_character:   return KEY_STATS;
		case menucmd_history:     return KEY_MESSAGE_HISTORY;
		case menucmd_discoveries: return KEY_DISCOVERIES;
		case menucmd_quit:        return KEY_ESC;
		case menucmd_wait:        return KEY_WAIT;
		case menucmd_climb:       return KEY_STAIR;
		case menucmd_fire:        return KEY_FIRE;
		case menucmd_spell:       return KEY_CAST;
		case menucmd_search:      return KEY_SEARCH;
		case menucmd_open:        return KEY_OPENDOOR;
		case menucmd_close:       return KEY_CLOSEDOOR;
		case menucmd_inventory:   return KEY_INVENTORY;
		case menucmd_use:         return KEY_USE;
		case menucmd_equip:       return KEY_WEAR;
		case menucmd_takeoff:     return KEY_TAKEOFF;
		case menucmd_drop:        return KEY_DROP;
		case menucmd_pickup:      return KEY_PICKUP;
		case menucmd_throw:       return KEY_THROW;
		default:                  return 0;
	}
}
//}}}

//{{{
void delay(void)
{
	SysTaskDelay( (DELAY_AMOUNT_PC*SysTicksPerSecond())/1000 );
}
//}}}
//{{{
void UI_Dialog_Default(const char *content)
{
	UI_Dialog_Display( default_dialog_rect, content );
	UI_MF_clear();
	full_redraw();
}
//}}}
//{{{
void UI_Dialog_Display(rect r, const char *content)
{
	coord pos = r.topleft;
	coord size = r.extent;
	
	Graph_ClearRect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
	
	Graph_DrawLine(pos.x, pos.y, pos.x+size.x, pos.y);
	Graph_DrawLine(pos.x, pos.y, pos.x, pos.y+size.y);
	Graph_DrawLine(pos.x+size.x, pos.y, pos.x+size.x, pos.y+size.y);
	Graph_DrawLine(pos.x, pos.y+size.y, pos.x+size.x, pos.y+size.y);
	
	draw_string(content, NULL, pos.x+2, pos.y+2, size.x-4, (size.y-4), 1);
	read_char();
}
//}}}
//{{{
short FontHeight(void)
{
	return 6;
//	return FntCharHeight();
}
//}}}
//{{{
short FontWidth(unsigned char c)
{
//	if(high_density_font)
//		return 4;
//	else
//		return 5;
	return FntCharWidth(c);
}
//}}}

//{{{
void panic(const char *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	SysFatalAlert(vretprintf(fmt, list));
	exit(1);
}
//}}}

//{{{
const char *get_keyname(short key)
{
	// FIXME STUB
	return "";
}
//}}}

//{{{
#ifndef min
int min(int a, int b)
{
	if(a<b)
		return a;
	else
		return b;
}
#endif
//}}}
//{{{
#ifndef max
int max(int a, int b)
{
	if(a<b)
		return b;
	else
		return a;
}
#endif
//}}}

//{{{
void *memcpy(void *dst, const void *src, size_t sz)
{
	MemMove(dst, src, sz);
	return dst;
}
//}}}
//{{{
void *malloc_throw(size_t N)
{
	void *ret = MemPtrNew(N);
	if(!N) return NULL;
	if(!ret) panic("Out of memory allocating size %i!", (int)N);
	return ret;
}
//}}}
//{{{
void *calloc(size_t N, size_t S)
{
	size_t total = N*S;
	void *ret = debug_malloc(total);
	if(ret) memset(ret, 0, total);
	return ret;
}
//}}}
//{{{
void *realloc(void *data, size_t size)
{
	Err e;
	long copy_size;
	void *ret;
	if(size==0) {
		if(data) debug_free(data);
		return NULL;
	}
	if(data == NULL) {
		return debug_malloc(size);
	}
	e = MemPtrResize(data, size);
	if(!e) return data;
	ret = debug_malloc(size);
	copy_size = MemPtrSize(data);
	if(copy_size > size) copy_size = size;
	memcpy(ret, data, copy_size);
	return ret;
}
//}}}

//{{{
int isqrt(int n)
{
	int ii;
	for(ii=0; ii*ii<n; ii++);
	return ii;
}
//}}}

