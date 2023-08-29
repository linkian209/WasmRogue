#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sgt.h"

#define SIZE_INIT 4096

static int sgt_filter_buf(FILE *out, char *buf, int len, const char *keyword);
static void read_and_translate_strings(FILE *out, int lineno, char *buf, int *pos);
static void pass_whitespace(FILE *out, const char *buf, int *pos);

int current_line = 0;

//{{{
/// Filter (replace gettext() with translations) from file to file
int sgt_filter(FILE *in, FILE *out, const char *keyword)
{
	char *buf = NULL;
	int read_len = 0;
	int alloced_len = SIZE_INIT;
	int ret;
	
	// Read the entire input into a huge buffer before starting
	while(!feof(in))
	{
		alloced_len *= 2;
		buf = (char*)realloc(buf, alloced_len);
		
		ret = fread(buf+read_len, 1, alloced_len-read_len, in);
		read_len += ret;
	}
	buf[read_len] = '\0';
	
	ret = sgt_filter_buf(out, buf, read_len, keyword);
	
	if(buf) free(buf);
	return ret;
}
//}}}
//{{{
/// Open a file, and overwrite it with a translated version
int sgt_rewrite(const char *filename, const char *keyword)
{
	char *buf = NULL;
	int read_len = 0;
	int alloced_len = SIZE_INIT;
	int ret;
	FILE *file;
	
	file = fopen(filename, "r");
	if(!file) {
		error("Unable to open %s for reading.", filename);
		exit(1);
	}
	
	// Read the entire input into a huge buffer before starting
	while(!feof(file))
	{
		alloced_len *= 2;
		buf = (char*)realloc(buf, alloced_len);
		
		ret = fread(buf+read_len, 1, alloced_len-read_len, file);
		read_len += ret;
	}
	buf[read_len] = '\0';
	
	fclose(file);
	file = fopen(filename, "w");
	
	if(!filename) {
		error("Unable to open %s for writing.", filename);
		exit(1);
	}
	
	ret = sgt_filter_buf(file, buf, read_len, keyword);
	
	fclose(file);
	
	if(buf) free(buf);
	return ret;
}
//}}}

//{{{
/// Translate and write a string to file
static int sgt_filter_buf(FILE *out, char *buf, int len, const char *keyword)
{
	int ii, saved_spot;
	int strlen_gettext = strlen(keyword);
	
	// Note assumption: gettext can never be the very first thing in a file.
	// Since that couldn't possibly be valid C, this is a valid performance
	// optimization.
	putc(buf[0], out);
	
	// Scan for replacements
	for(ii=1; ii<len; ii++) 
	{
		saved_spot = ii;
		
		if(buf[ii] != 'g'    // Quick check to throw out most non-matches
		   || !match_str(buf+ii, keyword) // The keyword has to match
		   || isident(buf[ii-1])  // Can't be embedded in the end of a token
		   || isident(buf[ii+strlen_gettext]) // Can't have more after it
		   )
		{
			if(buf[ii] == '\n') current_line++;
			putc(buf[ii], out);
		}
		else
		{
			// Skip gettext identifier
			ii += strlen_gettext;
			
			pass_whitespace(out, buf, &ii);
			
			if( buf[ii++] != '(' ) {
				// Next character's not a parenthese? Oh well, guess this
				// wasn't really the macro after all. Now some backtracking
				// is needed.
				ii = saved_spot;
				putc(buf[ii], out);
				continue;
			}
			
			pass_whitespace(out, buf, &ii);
			
			// Do the actual translation/output on the strings
			// This also advances the cursor past them.
			read_and_translate_strings(out, current_line, buf, &ii);
			
			pass_whitespace(out, buf, &ii);
			
			// Now eat the remaining whitespace and closing parenthese
			if( buf[ii] != ')' ) { // Uh-oh, that was unexpected
				fprintf(stderr, "Warning: found %c in gettext macro.", buf[ii]);
			}
		}
	}
	return 0;
}
//}}}
//{{{
/// Translate a strings or grouping of strings
static void read_and_translate_strings(FILE *out, int lineno, char *buf, int *pos)
{
	// (1) Collect a series of fragments. Fragments which were not quoted
	//     are marked as untranslateable. All other fragments are attempted
	//     with gettext.
	// (2) Try catenating all the fragments together, and see if what comes
	//     out is translateable. (If so, output it.). Otherwise:
	// (3) Try translating each fragment individually. Whether translated
	//     or not, output whatever the result is.
	//
	// NOTE: This function allocates a bunch of memory and never frees it.
	// Since it's meant for short runs, the effect is proportional to the
	// size of the input file and not cumulative between files. It's faster
	// this way, and it gets freed when the process dies anyways.
	
	typedef struct fragment_info
	{
		char *str;
		short quoted;
	} fragment_info;
	
	fragment_info *fragments = NULL;
	fragment_info cur_fragment;
	int num_fragments   =0, num_fragments_alloc=0;
	int cur_fragment_len=0, cur_fragment_alloc =0;
	int ii;
	int len;
	char *aggregate_text;
	
	do
	{
		if(num_fragments+1 > num_fragments_alloc) {
			num_fragments_alloc += 8;
			fragments = (fragment_info*)realloc( fragments, 
				sizeof(fragment_info)*num_fragments_alloc );
		}
		
		if( buf[*pos] == '\"' )
		{
			cur_fragment.quoted = 1;
			(*pos)++;
			
			cur_fragment_len = 0;
			cur_fragment_alloc = 16;
			cur_fragment.str = (char*)malloc(16);
			
			while( buf[*pos] != '\"' && buf[*pos] != '\0' )
			{
				if(cur_fragment_len+2 > cur_fragment_alloc) {
					cur_fragment_alloc += 32;
					cur_fragment.str = (char*)realloc(
						cur_fragment.str, cur_fragment_alloc );
				}
				
				switch( buf[*pos] )
				{
					case '\\':
						// Escapes get mostly left as-is, except for \\n
						(*pos)++;
						switch(buf[*pos]) {
							case '\n':
								cur_fragment.str[cur_fragment_len++] = ' ';
								(*pos)++;
								break;
							default:
								cur_fragment.str[cur_fragment_len++] = '\\';
								cur_fragment.str[cur_fragment_len++] =
									buf[*pos];
								(*pos)++;
								break;
						}
						break;
					case '\n':
						// Hey, that's not allowed!
						// But regardless, keep the linecount the same
						(*pos)++;
						putc('\n', out);
						cur_fragment.str[cur_fragment_len++] = '\n';
						break;
					default:
						cur_fragment.str[cur_fragment_len++] = buf[(*pos)++];
						break;
				}
			}
			
			cur_fragment.str[cur_fragment_len] = '\0';
			
			if( buf[*pos] == '\"' ) // Pass over closing quote
				(*pos)++;
		}
		else if(buf[*pos]==')' || buf[*pos]=='\0')
		{
			break;
		}
		else
		{
			// These shouldn't be showing up post-preprocessor, but leaving
			// them in will make diagnostics more useful.
			cur_fragment.quoted = 0;
			cur_fragment_len = 0;
			cur_fragment_alloc = 0;
			cur_fragment.str = NULL;
			
			do {
				if(cur_fragment_len+2 > cur_fragment_alloc) {
					cur_fragment_alloc += 32;
					cur_fragment.str = (char*)realloc(
						cur_fragment.str, cur_fragment_alloc );
				}
				
				cur_fragment.str[cur_fragment_len++] = buf[*pos];
				
				(*pos)++;
				if( buf[*pos]=='\0' || !isident(buf[*pos]) )
					break;
			} while(1);
			
			cur_fragment.str[cur_fragment_len] = '\0';
			
			fprintf(stderr, "Warning: %i: non-quoted string '%s' inside"
			                " gettext.\n",
				lineno, cur_fragment.str );
		}
		
		pass_whitespace(out, buf, pos);
		
		fragments[num_fragments++] = cur_fragment;
		
	} while(1);
	
	// Make a big aggregate string
	len = 0;
	for(ii=0; ii<num_fragments; ii++)
		len += strlen( fragments[ii].str );
	aggregate_text = (char*)malloc(len+1);
	aggregate_text[0] = '\0';
	for(ii=0; ii<num_fragments; ii++)
		strcat(aggregate_text, fragments[ii].str);
	
	if(have_translation(aggregate_text)) {
		fprintf(out, "\"%s\" ", get_translation(aggregate_text));
		return;
	}
	
	for(ii=0; ii<num_fragments; ii++)
	{
		putc(' ', out);
		if(fragments[ii].quoted) putc('\"', out);
		fprintf(out, "%s", get_translation(fragments[ii].str));
		if(fragments[ii].quoted) putc('\"', out);
		putc(' ', out);
	}
}
//}}}

//{{{
static void pass_whitespace(FILE *out, const char *buf, int *pos)
{
	while(isspace(buf[*pos])) {
		if(buf[*pos] == '\n') {
			putc('\n', out);
			current_line++;
		}
		(*pos)++;
	}
}
//}}}

