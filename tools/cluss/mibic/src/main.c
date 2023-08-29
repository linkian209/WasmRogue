#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "compile.h"
#include "namespace.h"
#include "util.h"
#include "hir.h"
#include "lir.h"

#define PROGRAM_NAME "compile"
#define PROGRAM_VERSION "v1.0"

namespace_t global_namespace;
int errors = 0, warnings = 0;
char *input_filename = NULL;
const char *output_filename = NULL;
int should_free_input_filename = 0;
int emit_loader = 1;
int asm_out = 0;
int debug_info = 0;
int debug_mode = 0;
int optimize = 0;
int reverse_endian = 0;
int preprocess_only = 0;

static void init_global_namespace(void);
static void cleanup_namespaces(void);
static void handle_args(int argc, char **argv);

//{{{
int main(int argc, char **argv)
{
	init_global_namespace();
	init_types();
	
	atexit(hir_done);
	atexit(cleanup_namespaces);
	
	handle_args(argc, argv);
	
	if(errors == 0)
	{
		hir_reduce_pointers();
		
		if(debug_mode)
			hir_debug_print_all();
		else
		{
			hir_reduce();
			
			if(optimize)
			{
				lir_opt_constant_size();
				lir_opt_dead_tails();
			}
			
			if(asm_out)
				lir_print();
			else
				lir_assemble();
		}
	}
	
	return 0;
}
//}}}
//{{{
static void init_global_namespace(void)
{
	init_namespace(&global_namespace);
}
//}}}
//{{{
static void cleanup_namespaces(void)
{
	delete_namespace(&global_namespace);
}
//}}}
//{{{
static void handle_args(int argc, char **argv)
{
	int i, j, pos;
	int num_inputs = 0;
	FILE *fin, *fout;
	char *input_names[32];
	const char *preprocessor = "cpp";
	const char *include_directories[32];
	int num_include_dirs = 0;
	char preprocessor_invocation[512];
	char preprocessor_instance[512];
	
	for(i=1; i<argc; i++)
	{
		if( !strcmp(argv[i], "-h") || !strcmp(argv[i], "--help") ) {
			printf(
"Usage: %s [-dehvEO] [input] [-o output] [-i]\n"
"[-P preprocessor]\n"
"\n"
"  -O               Enable optimization\n"
"  -a, --asm        Output assembly instead of binary\n"
"  -d, --debug      Print HIR debug information\n"
"  -e, --endian     Reverse endianness of output literals\n"
"  -E, --preprocess Preprocess only\n"
"  -g               Include debug information in output\n"
"  -h, --help       Show this page\n"
"  -v, --version    Show version information\n"
"  -i               Omit code loading section\n"
"  -P               Specify a preprocessor to use (default is cpp)\n"
"\n",
			       argv[0]);
			exit(0);
		}
		else if( !strcmp(argv[i], "-O") )
		{
			optimize = 1;
		}
		else if( !strcmp(argv[i], "-v") || !strcmp(argv[i], "--version") )
		{
			printf(PROGRAM_NAME ", " PROGRAM_VERSION "\n"
			       "by Jim Babcock. Distributed under GNU Lesser General Public License (LGPL).\n"
			       "See the file COPYING for details.\n");
			exit(0);
		}
		else if( !strcmp(argv[i], "-a") || !strcmp(argv[i], "--asm") )
		{
			asm_out = 1;
		}
		else if( !strcmp(argv[i], "-d") || !strcmp(argv[i], "--debug") )
		{
			debug_mode = 1;
		}
		else if( !strcmp(argv[i], "-e") || !strcmp(argv[i], "--endian") )
		{
			reverse_endian = 1;
		}
		else if( !strcmp(argv[i], "-E") || !strcmp(argv[i], "--preprocess") )
		{
			preprocess_only = 1;
		}
		else if( !strcmp(argv[i], "-g") )
		{
			debug_info = 1;
		}
		else if( !strcmp(argv[i], "-i") )
		{
			emit_loader = 0;
		}
		else if( !strcmp(argv[i], "-o") )
		{
			i++;
			if(i >= argc) {
				fprintf(stderr, "-o option requires an additional argument.\n");
				exit(ERROR_INVOCATION);
			}
			if(output_filename) {
				fprintf(stderr, "Error: Can only have one output location.\n");
				exit(ERROR_INVOCATION);
			}
			output_filename = argv[i];
		}
		else if( !strcmp(argv[i], "-P") )
		{
			i++;
			if(i >= argc) {
				fprintf(stderr, "-P option requires an additional argument.\n");
				exit(ERROR_INVOCATION);
			}
			preprocessor = argv[i];
		}
		else if( argv[i][0]=='-' && argv[i][1]=='I')
		{
			include_directories[num_include_dirs++] = argv[i];
		}
		else
		{
			// Input file
			num_inputs++;
			if(num_inputs>32) {
				fprintf(stderr, "Too many input files (limit 32)");
				exit(ERROR_INVOCATION);
			}
			input_names[num_inputs-1] = argv[i];
		}
	}
	
	if(num_inputs == 0)
	{
		fprintf(stderr, "Error: No inputs specified.\n");
		exit(ERROR_INVOCATION);
	}
	
	// Generate base string to invoke preprocessor with
	// eg: cpp -Iinclude -I...
	pos = snprintf(preprocessor_invocation, 512, "%s ", preprocessor);
	for(j=0; j<num_include_dirs; j++)
		pos += snprintf(preprocessor_invocation+pos, 512-pos, "%s ", include_directories[j]);
	
	if(preprocess_only)
	{
		if(!output_filename) {
			fprintf(stderr, "Error: Output file not specified.\n");
			exit(ERROR_INVOCATION);
		}
		if(num_inputs != 1) {
			fprintf(stderr, "Error: Must have exactly one input with -E.\n");
			exit(ERROR_INVOCATION);
		}
		fout = fopen(output_filename, "w");
		if(!fout) {
			fprintf(stderr, "Error opening output file.\n");
			exit(ERROR_INVOCATION);
		}
		strcpy(preprocessor_instance, preprocessor_invocation);
		strncat(preprocessor_instance, " ", 512);
		strncat(preprocessor_instance, input_names[0], 512);
		fin = popen(preprocessor_instance, "r");
		if(!fin) {
			fprintf(stderr, "Error running preprocessor.\n");
			fclose(fout);
			exit(ERROR_INVOCATION);
		}
		while(!feof(fin)) {
			i = getc(fin);
			if(i==EOF) break;
			putc(i, fout);
		}
		pclose(fin);
		fclose(fout);
		exit(0);
	}
	
	for(i=0; i<num_inputs; i++)
	{
		if(should_free_input_filename)
			free(input_filename);
		input_filename = input_names[i];
		should_free_input_filename = 0;
		strcpy(preprocessor_instance, preprocessor_invocation);
		strncat(preprocessor_instance, " ", 512);
		strncat(preprocessor_instance, input_names[i], 512);
		fin = popen(preprocessor_instance, "r");
		
		if(!fin) {
			fprintf(stderr, "%s: Error running preprocessor.\n", input_filename);
			exit(ERROR_FILES);
		}
		
		if(emit_loader)
			lir_write_inst_label(LIR_JMP, get_identifier(&global_namespace, "main"));
		yyin = fin;
		yyparse();
		
		pclose(fin);
	}
	
	if(output_filename == NULL && debug_mode == 0 && asm_out == 0)
	{
		fprintf(stderr, "Error: No output location specified.\n");
		exit(ERROR_INVOCATION);
	}
}
//}}}


