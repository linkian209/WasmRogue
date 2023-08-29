#include "crogue.h"
#include "export.h"

#define HOLE_SIZE_SQUARED 300

static void stroke_clear_queue(void) SEG(3);
static void stroke_enqueue(int x, int y) SEG(3);
static int stroke_evaluate(void) SEG(3);
static int point_dist_to_line(int xp, int yp, int x1, int y1, int x2, int y2) SEG(3);

static int pen_direction(int type, int x, int y) SEG(3);

enum { pen_nowhere, pen_main_form, pen_buttonbar } pen_target = pen_nowhere;
static int pen_prev_x, pen_prev_y;
//{{{
int event_pen_down(int x, int y)
{
	int buttonnum;
	pen_prev_x=x, pen_prev_y=y;
	if(y >= BUTTONBAR_Y)
	{
		pen_target = pen_buttonbar;
		buttonnum = buttonbar_which_button(x, y);
		buttonbar_xor(buttonnum);
		return 0;
	}
	if(distancesquare(x, y,
		(SCREEN_WIDTH/2), (SCREEN_HEIGHT/2)) > HOLE_SIZE_SQUARED)
	{
		// Far from the center of the screen means immediate move
		return pen_direction(PEN_TAP, x-SCREEN_WIDTH/2,
		                              y-SCREEN_HEIGHT/2);
	}
	
	pen_target = pen_main_form;
	stroke_enqueue(x, y);
	return 0;
}
//}}}
//{{{
void event_pen_move(int x, int y)
{
	if(pen_target == pen_main_form)
		stroke_enqueue(x, y);
	else if(pen_target == pen_buttonbar)
	{
		buttonbar_xor( buttonbar_which_button(pen_prev_x, pen_prev_y) );
		buttonbar_xor( buttonbar_which_button(x, y) );
	}
	pen_prev_x=x, pen_prev_y=y;
}
//}}}
//{{{
int event_pen_up(int x, int y)
{
	int ret;
	int buttonnum;
	if(pen_target == pen_main_form) {
		pen_target = pen_nowhere;
		ret = stroke_evaluate();
		stroke_clear_queue();
		if(ret) return ret;
	}
	else if(pen_target == pen_buttonbar)
	{
		pen_target = pen_nowhere;
		buttonnum = buttonbar_which_button(pen_prev_x, pen_prev_y);
		buttonbar_xor( buttonnum );
		return button_press(buttonnum);
	}
	else
	{
		pen_target = pen_nowhere;
	}
	return 0;
}
//}}}

//{{{
static int pen_direction(int type, int x, int y)
{
	int dx, dy;
	int action;
	if(abs(x) > 2*abs(y)) {
		if(x>0) dx=1, dy=0;
		else    dx=-1, dy=0;
	}
	else if(abs(y) > 2*abs(x)) {
		if(y>0) dx=0, dy=1;
		else    dx=0, dy=-1;
	}
	else if(x>0) {
		if(y>0) dx=1, dy=1;
		else    dx=1, dy=-1;
	} else {
		if(y>0) dx=-1, dy=1;
		else    dx=-1, dy=-1;
	}
	
	action = get_option(type | OPTION_PEN_PREFIX);
	if(action == -1)
		action = type;
	return pen_actions[action](dx, dy);
}
//}}}

static coord *stroke_queue;
static int stroke_length = 0, stroke_alloc = 0;
//{{{
static void stroke_clear_queue(void)
{
	stroke_length = stroke_alloc = 0;
	if(stroke_queue) free(stroke_queue);
	stroke_queue = NULL;
}
//}}}
//{{{
static void stroke_enqueue(int x, int y)
{
	if(stroke_length+1 > stroke_alloc) {
		stroke_alloc += 16;
		stroke_queue=(coord*)realloc(stroke_queue, sizeof(coord)*stroke_alloc);
	}
	stroke_queue[stroke_length++] = COORD(x, y);
}
//}}}
//{{{
static int stroke_evaluate(void)
{
	int dx, dy;
	int ii;
	coord *start, *end, *farthest;
	int farthest_distance_square = 0;
	int max_distance, distance;
	
	if(!stroke_length) return 0;
	
	start = &stroke_queue[0];
	end = &stroke_queue[stroke_length-1];
	farthest = end;
	for(ii=0; ii<stroke_length; ii++)
	{
		if(distancesquare(stroke_queue[ii].x, stroke_queue[ii].y,
		                  start->x, start->y) > farthest_distance_square)
		{
			farthest_distance_square = 
				distancesquare(stroke_queue[ii].x, stroke_queue[ii].y,
		    	               start->x, start->y);
			farthest = &stroke_queue[ii];
		}
	}
	dx = end->x - start->x;
	dy = end->y - start->y;
	
		// This was a screen-center tap
	if(farthest_distance_square < 100) {
		return pen_tap_center();
	}
	
	// Check for return stroke
	if( (dx*dx+dy*dy)*4 < farthest_distance_square
	                                    // Returns to about the same spot
	 && farthest_distance_square > 100) // Goes out somewhere on the screen
	{
		return pen_direction(PEN_RETURN, farthest->x-start->x,
		                     farthest->y-start->y);
	}
	
	// Check for straight stroke
	if( (dx*dx+dy*dy) > 100 )           // Goes out somewhere on the screen
	{
		max_distance = 0;
		for(ii=0; ii<stroke_length; ii++)
		{
			distance=point_dist_to_line( stroke_queue[ii].x, stroke_queue[ii].y,
		                                 start->x, start->y, end->x, end->y );
			if(distance > max_distance) {
				max_distance = distance;
			}
		}
		if(max_distance*max_distance*8 < farthest_distance_square)
			return pen_direction(PEN_DRAG, dx, dy);
		else
			return pen_direction(PEN_SQUIGGLE, dx, dy);
	}
	
	// A simple tap?
	if( (dx*dx+dy*dy) < 50 && farthest_distance_square<50 ) {
		return pen_direction(PEN_TAP, end->x - SCREEN_WIDTH/2,
		                              end->y - SCREEN_HEIGHT/2);
	}
		
	return 0;
}
//}}}
//{{{
static int point_dist_to_line(int xp, int yp, int x1, int y1, int x2, int y2)
{
	long dx1p = x1-xp,
	    dx21 = x2-x1,
	    dy1p = y1-yp,
	    dy21 = y2-y1,
	    frac = dx21*dx21 + dy21*dy21;
	long lambda = (-(dx1p*dx21 + dy1p*dy21)<<8) / frac;
	long xsep, ysep;
	if(lambda < 0) lambda=0;
	if(lambda > (1<<8)) lambda = 1<<8;
	
	xsep = (dx1p<<8) + lambda*dx21;
	ysep = (dy1p<<8) + lambda*dy21;
	
	return isqrt((xsep*xsep+ysep*ysep) >> 16);
}
//}}}


typedef struct {
	char label;
	int effect;
} button_desc;
button_desc button_data[] = {
	{ 'P', KEY_PICKUP },
	{ 'D', KEY_DROP },
	{ ' ', 0 },
	{ 'I', KEY_INVENTORY },
	{ 'W', KEY_WEAR },
	{ 'T', KEY_TAKEOFF },
	{ 'U', KEY_USE },
	{ ' ', 0 },
	{ 'M', KEY_CAST },
	{ '>', KEY_STAIR },
	{ '-', KEY_OPENDOOR },
	{ '+', KEY_CLOSEDOOR },
	{ '@', KEY_STATS },
	{ '?', KEY_HELPMENU }
	};
//{{{
static int count_buttons(void)
{
	int ii;
	for(ii=0; button_data[ii].label !=0; ii++)
		;
	return ii;
}
//}}}
//{{{
void buttonbar_draw(void)
{
	int ii;
	int num_buttons = count_buttons();
	Graph_ClearRect(0, BUTTONBAR_Y-1, SCREEN_WIDTH-1, SCREEN_HEIGHT-1);
	for(ii=0; ii<num_buttons; ii++)
	{
		if(button_data[ii].label == ' ') continue;
		Graph_DrawRect( BUTTONBAR_X + (ii*(BUTTON_WIDTH+2)),
		                BUTTONBAR_Y,
		                BUTTONBAR_X + (ii*(BUTTON_WIDTH+2) + BUTTON_WIDTH),
		                BUTTONBAR_Y+BUTTON_HEIGHT );
		Graph_DrawChar( BUTTONBAR_X + (ii*(BUTTON_WIDTH+2))+2, BUTTONBAR_Y+1,
		                button_data[ii].label );
	}
}
//}}}
//{{{
int buttonbar_which_button(int x, int y)
{
	if(y < BUTTONBAR_Y) return -1;
	return x/(BUTTON_WIDTH+2);
}
//}}}
//{{{
void buttonbar_xor(int buttonnum)
{
	if(buttonnum<0 || buttonnum >= count_buttons())
		return;
	if(button_data[buttonnum].label == ' ')
		return;
	Graph_ScrRectXor( BUTTONBAR_X + (buttonnum*(BUTTON_WIDTH+2)) + 1,
					BUTTONBAR_Y + 1,
					BUTTON_WIDTH-1, BUTTON_HEIGHT-1 );
}
//}}}
//{{{
int button_press(int buttonnum)
{
	if(buttonnum<0 || buttonnum >= count_buttons())
		return 0;
	return button_data[buttonnum].effect;
}
//}}}

