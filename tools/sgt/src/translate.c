#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include "sgt.h"

//{{{
int have_translation(const char *key)
{
	const char *ret = static_gettext(key);
	
	if(ret == key)
		return 0;
	else
		return 1;
}
//}}}
//{{{
const char *get_translation(const char *key)
{
	return static_gettext(key);
}
//}}}

//{{{
typedef struct translation {
	char *key;
	char *value;
} translation;
//}}}

static int gettext_read_entry(FILE *fin);
static void append_line(const char *text, char **target);
static int gettext_compare_trans(const void *A, const void *B);
static void gettext_sort_entries(void);
static void gettext_add_entry(translation *trans);

static translation *gettext_table = NULL;
static unsigned num_translations=0, allocated_translations=0;

//{{{
/// Localize a string
///
/// gettext takes an English-language string and finds a matching string
/// in the appropriate language. If the current language is English, or if
/// no translation is available, it returns @a key. Otherwise, it returns
/// a statically-allocated string. The return value must not be modified
/// or freed.
/// @sa gettext_open gettext_cleanup
const char *static_gettext(const char *key)
{
	// Binary search for correct string
	int low=0, high=num_translations-1, mid=0, result;
	
	if(!gettext_table)
		return key;
	if(*key == '\0') // Zero-length string
		return key;
	
	while(high>low)
	{
		mid = (high+low)/2;
		result = strcmp(gettext_table[mid].key, key);
		if(result == 0) {
			if(gettext_table[mid].value[0] == '\0')
				return key;
			else
				return gettext_table[mid].value;
		} else if(result > 0) {
			if(mid == 0) return key;
			else high = mid-1;
		} else {
			low = mid+1;
		}
	}
	
	if( strcmp(gettext_table[high].key, key) == 0 ) {
		if( gettext_table[high].value[0] == '\0' ) // Empty string
			return key;
		else
			return gettext_table[high].value;
	} else
		return key;
}
//}}}
//{{{
/// Frees locale data
void gettext_cleanup(void)
{
	unsigned ii;
	
	if(gettext_table)
	{
		for(ii=0; ii<num_translations; ii++) {
			if(gettext_table[ii].key) free(gettext_table[ii].key);
			if(gettext_table[ii].value) free(gettext_table[ii].value);
		}
		free(gettext_table);
		gettext_table = NULL;
	}
}
//}}}

//{{{
static void gettext_sort_entries(void)
{
	qsort(gettext_table, num_translations, sizeof(translation),
	      gettext_compare_trans);
}
//}}}
//{{{
static void gettext_add_entry(translation *trans)
{
	if( num_translations+1 > allocated_translations ) {
		if(allocated_translations) allocated_translations *= 2;
		else allocated_translations += 8;
		gettext_table = (translation*)realloc(
			gettext_table, allocated_translations * sizeof(translation));
	}
	
	gettext_table[num_translations++] = *trans;
}
//}}}
//{{{
static int gettext_compare_trans(const void *A, const void *B)
{
	return strcmp(((translation*)A)->key, ((translation*)B)->key);
}
//}}}

#if 1
//{{{
/// Specifies the current language
///
/// Returns 1 if the file name given is present and corresponds to locale
/// data, 0 otherwise.
int gettext_open(const char *filename)
{
	FILE *fin;
	
	fin = fopen(filename, "r");
	if(!fin) {
		error("Gettext couldn't open file %s.", filename);
		goto error_return;
	}
	
	while( !feof(fin) )
	{
		if(gettext_read_entry(fin)==0)
			break;
	}
	
	gettext_sort_entries();
	
	fclose(fin);
	return 1;
	
error_return:
	if(fin) fclose(fin);
	return 0;
}
//}}}
//{{{
/// @brief Read an entry from a PO file
///
/// A description of the PO format for GNU gettext is at
/// <http://www.gnu.org/software/gettext/manual/html_node/gettext_9.html>.
/// This function complies, at least loosely, with that format.
static int gettext_read_entry(FILE *fin)
{
	static int lineno = 0;
	char in[1024];
	char *readpos;
	char **target = NULL;
	translation e;
	
	// Skip comments and whitespace
	do {
		skip_whitespace(fin);
	} while(skip_comment(fin));
	skip_whitespace(fin);
	
	e.key = e.value = NULL;
	
	do
	{
		if( fgets(in, 1024, fin) == NULL ) // EOF found
			break;
		lineno++;
		
		readpos = in;
		
		while(*readpos==' ' || *readpos=='\t')
			readpos++;
		
		// The line was ALL whitespace (terminator for an entry)
		if(*readpos=='\n' || *readpos=='\0') // EOF!
			break;
		
		if(*readpos=='\"') { // Continuation
			append_line(readpos, target);
		} else if(match_str(readpos, "msgid")) {
			target = &e.key;
			readpos += strlen("msgid");
			append_line(readpos, target);
		} else if(match_str(readpos, "msgstr")) {
			target = &e.value;
			readpos += strlen("msgstr");
			append_line(readpos, target);
		} else {
			error("Gettext didn't understand line %i:\'%s\' (readpos was '%s').", lineno, in, readpos);
			return 1;
		}
	} while(1);
	
	// This string hasn't been translated, or for some reason, no string was
	// read
	if(e.value == NULL || e.key == NULL)
		return 1;
	
	gettext_add_entry(&e);
	
	return 1;
}
//}}}
//{{{
static void append_line(const char *text, char **target)
{
	char addition[1024]; // FIXMEFIXME @bug Buffer overflow reading from
	                     // locale files.
	const char *source = text;
	char *pos = addition;
	int len;
	
	// Skip over leading whitespace and quote
	while(isspace(*source)) source++;
	if(*source=='\"') source++;
	
	while(*source != '\0')
	{
		switch(*source) {
			case '\"': // End of string section
				goto done;
			case '\n': // Newline in string is not allowed
				error("Error: newline found in string.");
				break;
			case '\\': // Start of escape sequence
				source++;
				switch( *source ) {
					case '\n': // \\\n maps to space
						*(pos++) = ' ';
						source++;
						break;
					default: // Anything else should be included as-is
						*(pos++) = '\\';
						*(pos++) = *(source++);
						break;
				}
				break;
			default:
				*(pos++) = *(source++);
				break;
		}
	}
	
done:
	*pos = '\0';
	
	len = strlen(addition) + 1;
	if(*target) {
		len += strlen(*target);
		*target = (char*)realloc( *target, len );
		strcat(*target, addition);
	} else {
		*target = (char*)malloc( len );
		strcpy(*target, addition);
	}
}
//}}}
#else
//{{{
int gettext_open(const char *filename)
{
	po_file_t fin;
	po_message_iterator_t iterator;
	po_message_t message;
	translation trans;
	const char *str;
	
	fin = po_file_read(filename);
	
	if(fin == NULL) {
		error("Couldn't open file %s.", filename);
		goto error_return;
	}
	iterator = po_message_iterator(fin, NULL);
	
	for(;;)
	{
		message = po_next_message(iterator);
		if(message==NULL) break;
		str = po_message_msgid(message);
		trans.key = strdup(str);
		str = po_message_msgstr(message);
		if(strlen(str)>0) {
			trans.value = strdup(str);
		} else {
			trans.value = strdup(trans.key);
		}
		gettext_add_entry(&trans);
	}
	po_message_iterator_free(iterator);
	gettext_sort_entries();
	
	po_file_free(fin);
	return 1;
	
error_return:
	if(fin) po_file_free(fin);
	return 0;
}
//}}}
#endif


