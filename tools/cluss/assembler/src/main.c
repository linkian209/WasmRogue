#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "cluss.h"

#define VERSION_STRING "0.1"

static int opt_argc;
static char **opt_argv;
//{{{
void init_getopt(int argc, char **argv)
{
	opt_argc = argc;
	opt_argv = argv+1;
}
//}}}
//{{{
const char *getopt(void)
{
	if(--opt_argc <= 0)
		return NULL;
	return *(opt_argv++);
}
//}}}

//{{{
int main(int argc, char **argv)
{
	int ret;
	const char *arg;
	const char *input_filename=NULL, *output_filename=NULL;
	FILE *fin;
	
	initialize();
	init_getopt(argc, argv);
	
	while(( arg = getopt() ))
	{
		if(arg[0] == '-')
			// Argument is of the form "-x" or "--word"
		{
			if(!strcmp(arg, "-o")) {
				arg = getopt();
				if(!arg) {
					error("You must specify a filename with -o.");
					return 1;
				}
				if(output_filename) {
					error("You can only specify one output filename.");
					return 1;
				}
				output_filename = arg;
			}
			else if(!strcmp(arg, "-f")) {
				arg = getopt();
				if(!arg) {
					error("-f option requires another argument.");
					return 1;
				}
				set_output_format(arg);
			}
			else if(!strcmp(arg, "-h") || !strcmp(arg, "--help")) {
				print_help_text(argv[0]);
				return 0;
			}
			else if(!strcmp(arg, "-V") || !strcmp(arg, "--version")) {
				print_version_text();
				return 0;
			}
		}
		else
		{
			if(input_filename) {
				error("You can only specify one input file.");
				return 1;
			}
			input_filename = arg;
		}
	}
	
	if(input_filename)
	{
		fin = fopen(input_filename, "r");
		if(!fin) {
			error("Couldn't open input file %s: %s.", input_filename,
			                                          strerror(errno));
			return 1;
		}
	} else {
		fin = stdin;
	}
	
	ret = assemble_file(fin, output_filename);
	
	fclose(fin);
	return ret;
}
//}}}

//{{{
void initialize(void)
{
	check_endianness();
}
//}}}

//{{{
void print_help_text(const char *progname)
{
	printf(
"Usage: %s [-hV] [-o output-file] [-f format] [--var=value] source-file\n"
"\n"
"    -h, --help       Display help text\n"
"    -V, --version    Display version information\n"
"\n"
	, progname);
}
//}}}
//{{{
void print_version_text(void)
{
	printf(
"C-Like microScripting System (CLUSS)\n"
"Assembler/linker " VERSION_STRING ".\n"
"Copyright (C) Jim Babcock. This program is distributed under the GNU General\n"
"Public License. See the source for details.");
}
//}}}

