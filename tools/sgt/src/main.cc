#include <unistd.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sgt.h"
using namespace std;

#define VERSION_NUMBER "1.0.2"

void show_help_text(const char *invocation);
int sgt_compile(const char **opts, int num_opts, const char *output_filename);
void parse_option(const char *option);
void set_option(const char *key, const char *value);
bool looks_like_parameter(const char *str);

int quiet_mode = 1;
int debug_mode = 0;

const char *compiler_name = NULL;
const char *preprocessor_name = NULL;
const char *gettext_keyword = "gettext";
const char *preprocess_options = "-E";
const char *compile_options = "";
const char *output_compile = "-o ";
const char *output_preprocessor = "-o ";

//{{{
int main(int argc, const char **argv)
{
	int ii;
	const char *output_filename = NULL;
	const char **opts = NULL;
	FILE *fout, *fin;
	int num_opts = 0;
	int filter_mode = 0;
	
	for(ii=1; ii<argc; ii++)
	{
		if( !strcmp(argv[ii], "-h") || !strcmp(argv[ii], "--help") ) {
			show_help_text(argv[0]);
			exit(0);
		} else if( !strcmp(argv[ii], "--version") ) {
			printf("sgt v" VERSION_NUMBER ". Copyright (C) 2004 Jim Babcock.\n"
			"This is free software; see the source for copying conditions.\n");
			exit(0);
		} else if( !strcmp(argv[ii], "-v") || !strcmp(argv[ii], "--verbose") ) {
			quiet_mode = 0;
		} else if( !strcmp(argv[ii], "-l") || !strcmp(argv[ii], "--locale")
		         || !strcmp(argv[ii], "--language") ) {
			ii++;
			if(ii >= argc) {
				error("-c option requires an argument.");
				exit(1);
			}
			if( !gettext_open(argv[ii]) )
				exit(1);
		} else if( !strcmp(argv[ii], "-f") || !strcmp(argv[ii], "--filter") ) {
			filter_mode = 1;
		} else if( !strcmp(argv[ii], "-g") ) {
			debug_mode = 1;
		} else if( !strcmp(argv[ii], "-o") ) {
			ii++;
			if(ii >= argc) {
				error("-c option requires an argument.");
				exit(1);
			}
			output_filename = argv[ii];
		} else if( argv[ii][0] == '-' ) { // Option in -OPTION=VALUE form
			parse_option(argv[ii]+1);
		} else if(filter_mode) {
			// The first argument NOT beginning with '-' is a filename, as
			// are all subsequent arguments.
			opts = argv + ii + 1;
			num_opts = argc - ii -1;
		} else {
			// The first argument NOT beginning with '-' is a compiler name
			// the remaining arguments are options to the compiler
			if(compiler_name == NULL)
				compiler_name = argv[ii];
			if(preprocessor_name == NULL)
				preprocessor_name = argv[ii];
			opts = argv + ii + 1;
			num_opts = argc - ii - 1;
			break;
		}
	}
	
	if( !compiler_name )
		filter_mode = 1;
	
	if( filter_mode )
	{
		if( output_filename ) {
			fout = fopen(output_filename, "w");
			if(!fout) {
				error("Unable to open output file.");
				exit(1);
			}
		} else {
			fout = stdout;
		}
		
		for(ii=0; ii<num_opts; ii++)
		{
			fin = fopen(opts[ii], "r");
			printf("Filtering from %s", opts[ii]);
			if(!fin) {
				error("Unable to open input file '%s'.", opts[ii]);
				continue;
			}
			sgt_filter(fin, fout, "gettext");
			fclose(fin);
		}
		if(!num_opts) {
			sgt_filter(stdin, fout, "gettext");
		}
	}
	else
	{
		if(!output_filename) {
			error("Must specify an output file.");
			exit(1);
		}
		return !!sgt_compile(opts, num_opts, output_filename);
	}
	
	return 0;
}
//}}}

//{{{
void show_help_text(const char *invocation)
{
	printf(
	"Usage: %s [FLAG]... [OPTION=Value]... [compiler] [compiler-option]...\n"
	"\n"
	"FLAGS\n"
	"   -h             Show help\n"
	"   -v             Verbose mode\n"
	"   -f             Operate as a filter\n"
	"   -l [file]      Load locale strings from specified file\n"
	"   -o [file]      Send output to <file>\n"
	"   -OPTION=VALUE  Set option controlling invocation\n"
	"   -g             Debug (don't remove intermediate files)\n"
	"\n"
	"OPTIONS\n"
	"   keyword        Keyword to translate (default: gettext)\n"
	"   ppopts         Option to pass when preprocessing (default: -E)\n"
	"   compileopts    Option to pass when compiling (default: none)\n"
	"   outputopt      Option to indicate output file (default: -o)\n"
	"   compiler       Override compiler command (default: none)\n"
	"   preprocessor   Override preprocessor command (default: none)\n"
	"\n",
		
		invocation
		);
	printf("sgt v" VERSION_NUMBER ". Copyright (C) 2004 Jim Babcock.\n"
	"This is free software; see the source for copying conditions.\n"
	"\n");
	
}
//}}}
//{{{
int sgt_compile(const char **opts, int num_opts, const char *output_filename)
{
	string intermediate_filename;
	string preprocess_command;
	string compile_command;
	int ii;
	int ret;
	
	// Generate intermediate_filename
	intermediate_filename = string(stem(output_filename))+string(".i");
	
	// Generate preprocess_command
	preprocess_command = string(preprocessor_name) + ' ' +
		preprocess_options + ' ' + output_preprocessor +
		intermediate_filename;
	for(ii=0; ii<num_opts; ii++) {
		preprocess_command += ' ';
		preprocess_command += opts[ii];
	}
	
	// Generate compile_command
	compile_command = string(compiler_name) + ' ' + compile_options
		+ ' ' + output_compile + output_filename;
	for(ii=0; ii<num_opts; ii++) {
		if(looks_like_parameter(opts[ii]))
		{
			compile_command += ' ';
			compile_command += opts[ii];
		}
	}
	compile_command += ' ';
	compile_command += intermediate_filename.c_str();
	
	// Preprocess
	if(!quiet_mode)
		printf("%s\n", preprocess_command.c_str());
	ret = system( preprocess_command.c_str() );
	
	if(!quiet_mode)
		printf("preprocessor exit status: %i\n", ret);
	
	if(ret) // Error during preprocessing!
		return ret;
	
	// Filter
	if(!quiet_mode)
		printf("filter %s\n", intermediate_filename.c_str());
	sgt_rewrite(intermediate_filename.c_str(), "gettext");
	
	// Compile
	if(!quiet_mode)
		printf("%s\n", compile_command.c_str());
	fflush(stdout);
	ret = system(compile_command.c_str());
	
	if(!quiet_mode)
		printf("compiler exit status: %i\n", ret);
	
	if(ret) // Error during compiling!
		return ret;
	
	// Clean up temporary files
	if(!debug_mode)
	{
		if(!quiet_mode)
			printf("unlink %s\n", intermediate_filename.c_str());
		unlink(intermediate_filename.c_str());
	}
	
	return 0;
}
//}}}
//{{{
void parse_option(const char *option)
{
	int ii;
	char key[128];
	for(ii=0; option[ii]!='\0'; ii++) {
		if(option[ii] == '=') {
			key[ii] = '\0';
			set_option(key, option+ii+1);
			break;
		} else {
			key[ii] = option[ii];
		}
	}
}
//}}}
//{{{
void set_option(const char *key, const char *value)
{
	if(!strcmp(key, "keyword")) gettext_keyword = value;
	else if(!strcmp(key, "ppopts")) preprocess_options = value;
	else if(!strcmp(key, "compileopts")) compile_options = value;
	else if(!strcmp(key, "outputopt")) {
		output_compile = output_preprocessor = value;
	}
	else if(!strcmp(key, "outputcomp")) output_compile = value;
	else if(!strcmp(key, "outputpp")) output_preprocessor = value;
	else if(!strcmp(key, "compiler")) compiler_name = value;
	else if(!strcmp(key, "preprocessor")) preprocessor_name = value;
}
//}}}

//{{{
/// @brief Guess whether a string is a filename or a parameter
///
/// Rather crude heuristic: '-' means parameter, '.' means filename. Ambiguous
/// results go to 'parameter'.
bool looks_like_parameter(const char *str)
{
	int ii;
	if(str[0] == '-') return true;
	for(ii=0; str[ii]!='\0'; ii++) {
		if(str[ii]=='.') // This looks like a FILENAME to me!
			return false;
	}
	return true;
}
//}}}


