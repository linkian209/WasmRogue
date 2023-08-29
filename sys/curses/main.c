#include "crogue.h"

static void init_file_prefix(const char *prefix);
static void handle_args(int argc, char **argv);

//{{{
int main(int argc, char **argv)
{
	init_file_prefix(argv[0]);
	handle_args(argc, argv);
	initialize();
	eventloop();
	return 0;
}
//}}}
char *file_prefix;
//{{{
static void init_file_prefix(const char *prefix)
{
	int ii, jj;
	
	for(ii=strlen(prefix)-1; ii>=0; ii--) {
		if(prefix[ii] == '/' || prefix[ii] == '\\')
			break;
	}
	
	file_prefix = (char*)malloc_throw(ii+1);
	for(jj=0; jj<=ii; jj++)
		file_prefix[jj] = prefix[jj];
	file_prefix[jj] = '\0';
}
//}}}

//{{{
static void handle_args(int argc, char **argv)
{
//	int ii;
//	for(ii=1; ii<argc; ii++)
//	{
//		if(!strcmp(argv[ii], "-h")) {
//			printf("Usage: %s [-L language]\n", argv[0]);
//			exit(0);
//		}
//		if(!strcmp(argv[ii], "-L")) {
//			ii++;
//			if(ii>=argc) {
//				fprintf(stderr, "You must specify a language file.\n");
//				exit(1);
//			}
//			if( gettext_open(argv[ii]) == 0 ) // Error opening
//			{
//				fprintf(stderr, "Error opening language file.\n"
//				                "Press ENTER to continue\n");
//				getchar();
//				fflush(stdin);
//			}
//		}
//	}
}
//}}}

//{{{
const char *asciistart[24] =
	{
" +--------------------------------------------------------------------------+   ",
" |                ########                             #####                |   ",
" |              #######                                  #####              |   ",
" |            #######             ###############         #####             |   ",
" |           ######           ######################       #####            |   ",
" |           #####          ########  # #   #  ######       #####           |   ",
" |          ######        ####### CalcRogue ###########      #####          |   ",
" |          #####        #######    by Jim Babcock #####      ####          |   ",
" |         ######        ######    ####+##  #############     #####         |   ",
" |         ######       ######     #.....#  #       #####     #####         |   ",
" |         ######       ############..V.T#  #  }    #####     #####         |   ",
" |         ######       ######     +.D...#  #       ######    #####         |   ",
" |         ######       ############.W..@#  #       #####     #####         |   ",
" |          ######      ######     #####-####+##########     #####          |   ",
" |          ######       ######    #   ...     +   ######   ######          |   ",
" |           ######       ######   ##############################           |   ",
" |            ######       ########              ##############             |   ",
" |             ######         ######################  ########              |   ",
" |              #######         ##################      ####                |   ",
" |                ########         ###########                  ###         |   ",
" |                   ########                                 #####         |   ",
" |                     ##########                          #######          |   ",
" +--------------------------------------------------------------------------+   ",
"                                                                                "
	};
//}}}
//{{{
const char *asciicolors[24] = {
" BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   ",
" B                ########                             #####                B   ",
" B              #######                                  #####              B   ",
" B            #######             ###############         #####             B   ",
" B           ######           ######################       #####            B   ",
" B           #####          ########uuuuuuuuuuu######       #####           B   ",
" B          ######        #######uWWWWWWWWWuuuuuu######      #####          B   ",
" B          #####        #######uuuuWWWWWWWWWWWWWWu#####      ####          B   ",
" B         ######        ######uuuuuuuuuuuuuuuuuuuuu#####     #####         B   ",
" B         ######       ######uuuuuuuuuuuuuuuuuuuuuu#####     #####         B   ",
" B         ######       ######uuuuuuuuuuuuuuuuuuuuuuu####     #####         B   ",
" B         ######       ######uuuuuuuuuuuuuuuuuuuuuu######    #####         B   ",
" B         ######       ######uuuuuuuuuuuuuuuuuuuuuu#####     #####         B   ",
" B          ######      ######uuuuuuuuuuuuuuuuuuuuuu####     #####          B   ",
" B          ######       ######uuuuuuuuuuuuuuuuuuuu######   ######          B   ",
" B           ######       ######uuuuuuuuuuuuuuuuuu###############           B   ",
" B            ######       ########uuuuuuuuuuuuuu##############             B   ",
" B             ######         ######################  ########              B   ",
" B              #######         ##################      ####                B   ",
" B                ########         ###########                  ###         B   ",
" B                   ########                                 #####         B   ",
" B                     ##########                          #######          B   ",
" BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB   ",
"                                                                                "
	};
//}}}

//{{{
void display_title_screen(void)
{
	int ii, jj, color;
	for(ii=0; ii<24; ii++)
	for(jj=0; jj<80; jj++)
	{
		switch(toupper(asciicolors[ii][jj])) {
			case 'Y': color = YELLOW; break;
			case 'U': color = BLUE;   break;
			case 'R': color = RED;    break;
			case 'B': color = BLACK;  break;
			default:  color = WHITE;  break;
		}
		attroff(COLOR_PAIR(DEFAULT_COLOR));
		if(isupper(asciicolors[ii][jj]))
			attron(A_BOLD);
		if(use_color) attron(COLOR_PAIR(color+1));
		mvaddch(ii, jj, asciistart[ii][jj]);
		if(use_color) attroff(COLOR_PAIR(color+1));
		if(isupper(asciicolors[ii][jj]))
			attroff(A_BOLD);
	}
	attron(A_BOLD);
	mvaddstr(20, 50, CROGUE_VERSION);
	attroff(A_BOLD);
}
//}}}
//{{{
void init_layout(void)
{
	uint tilefield_top, tilefield_bottom;
	uint tilefield_height;
	uint tilefield_width;
	uint status_pos;
	const char *tileset;
	
	tileset = tiles;
	
	status_pos = SCREEN_HEIGHT - 2;
	tilefield_top = 2;
	tilefield_bottom = status_pos - 1;
	tilefield_height = tilefield_bottom-tilefield_top+1;
	
	tilefield_width = SCREEN_WIDTH;
	
	UI_MF_Place(0, 2);
	UI_Status_Place(status_pos, 2);
	
	UI_TF_Place(
			COORD(0, tilefield_top),
			COORD(tilefield_width, tilefield_height),
			tileset, 1, 1
			);
}
//}}}

//{{{
void sys_init(void)
{
	(void)initscr();
	if(attroff(A_BOLD) == ERR)
		panic("attroff() returned ERR");
	noecho();
	cbreak();
	if(notimeout(stdscr, TRUE) == ERR)
		panic("notimeout() returned ERR");
	if(keypad(stdscr, TRUE) == ERR)
		panic("keypad() returned ERR");
#	if CURSES_TYPE == CURSES_NCURSES
		ESCDELAY=0;
#	endif
}
//}}}
int use_color = 0;
//{{{
void init_colors(void)
{
	use_color = (get_option(OPTION_COLOR) == OPTION_YES);
	
	if(use_color)
	{
		if(has_colors())
		{
			if(start_color() == ERR)
				use_color = 0;
			init_pair(1, COLOR_BLACK,   COLOR_BLACK);
			init_pair(2, COLOR_RED,     COLOR_BLACK);
			init_pair(3, COLOR_GREEN,   COLOR_BLACK);
			init_pair(4, COLOR_YELLOW,  COLOR_BLACK);
			init_pair(5, COLOR_BLUE,    COLOR_BLACK);
			init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
			init_pair(7, COLOR_CYAN,    COLOR_BLACK);
			init_pair(8, COLOR_WHITE,   COLOR_BLACK);
		}
		if(attron(COLOR_PAIR(DEFAULT_COLOR)) == ERR)
			use_color = 0;
	}
}
//}}}
//{{{
void sys_init_data_file(void)
{
	FILE *constfile;
	char header[4];
	unsigned long num_segs, size, ii;
	
	// Load constant-data file
	constfile = fopen(retprintf("%s%s", file_prefix, DATAFILENAME_PC), "rb");
	if(!constfile)
		panic("Couldn't open constant data file.");
	
	// Skip magic bytes (should probably check here that they are 'CLuS' as
	// expected)
	fread(header, 1, 4, constfile);
	
	// Read number of segments and allocate space
	fread(&num_segs, sizeof(num_segs), 1, constfile);
	w->num_segments = num_segs;
	w->const_file = (unsigned char**)malloc(sizeof(unsigned char*) * num_segs);
	
	// Read the segments themselves (each is a size followed by data)
	for(ii=0; ii<num_segs; ii++)
	{
		fread(&size, sizeof(num_segs), 1, constfile);
		w->const_file[ii] = (unsigned char*)malloc(size);
		fread(w->const_file[ii], 1, size, constfile);
	}
	
	memcpy(&w->desc, w->const_file[0], sizeof(struct world_descriptor));
	fclose(constfile);
	link_data_file();
}
//}}}
//{{{
void sys_cleanup(void)
{
	unsigned ii;
	if(w && w->const_file) {
		for(ii=0; ii<w->num_segments; ii++)
			if(w->const_file[ii])
				free(w->const_file[ii]);
		free(w->const_file);
	}
	clrscr();
	move(0, 0);
	endwin();
}
//}}}

//{{{
int curses_title_screen(void)
{
	int choice;
	clrscr();
	
	display_title_screen();
	
	do {
		choice = read_char();
	} while(choice < 'a' || choice > 'e');
	choice -= 'a';
	return choice;
}
//}}}

