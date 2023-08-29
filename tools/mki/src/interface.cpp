/*
 * mkinterface
 * Reads a cproto-generated proto.h and modifies it to accomodate intermodule
 * stuff. In particular:
 *  - Any functions mentioned in <interface file> are made into a struct, and
 *    (if DLL_IMPORT is defined) references are defined to refer to the struct.
 *  - (For platforms requiring segmentation, when supported): Any functions
 *    mentioned in segment lists are marked accordingly
 */
#include <string>
#include <vector>
#include <cstdio>

#define VERSION_STRING "0.2.0"

void show_help_text(const char *invocation);
void show_version_text(void);
void process_file(const char *filename);

int error_count = 0;
int verbose_mode = 0;

//{{{
class FunctionDefinition
{
public:
//{{{
	FunctionDefinition()
	{
		proto = marker = std::string("");
		isfunc = false;
		exported = false;
	}
//}}}
//{{{
	FunctionDefinition(const char *prototype)
	{
		// Parser definition:
		// A function's name is the token immediately preceding the first
		// open-parenthese. Everything prior is the type, and everything
		// after is the parameter list.
		
		const char *pos = prototype;
		const char *pos2;
		
		type = name = paramlist = marker = std::string("");
		proto = std::string(prototype);
		isfunc = true;
		exported = false;
		
		if(prototype[0] == '/') // Hey, this is a comment line, not a proto
		{
			isfunc = false;
			return;
		}
		
		while(*pos != '\0' && *pos != '(')
			pos++;
		if(*pos != '(') // This must not've been a prototype
		{
			isfunc = false;
			return;
		}
		
		// From here to the semicolon is parameters
		for(pos2=pos; *pos2!=';'&&*pos2!='\0'; pos2++)
			paramlist += *pos2;
		
		pos--;
		
		// Back up over whitespace
		while(isspace(*pos) && pos>prototype)
			pos--;
		// Now back up to the start of the name
		while( (isalpha(*pos)||*pos=='_'||isdigit(*pos)) && pos>prototype )
			pos--;
		pos++;
		
		// Anything *before* this is the type
		for(pos2=prototype; pos2<pos; pos2++)
			type += *pos2;
		
		// ...And this is the function name
		while( (isalpha(*pos)||*pos=='_'||isdigit(*pos)) && pos!='\0' ) {
			name += *pos;
			pos++;
		}
	}
//}}}
//{{{
	void emit_prototype(FILE *FP)
	{
		if(isfunc)
		{
			fprintf(FP,"%s%s%s", type.c_str(), name.c_str(),
			                        paramlist.c_str());
			if(marker.size()>0)
				fprintf(FP, " %s;\n", marker.c_str());
			else
				fprintf(FP, ";\n");
		}
		else
			fprintf(FP, "%s", proto.c_str());
	}
//}}}
//{{{
	void emit_pointer(FILE *FP)
	{
		if(isfunc)
			fprintf(FP,"%s(*%s)%s;\n", type.c_str(), name.c_str(),
			                           paramlist.c_str());
		else
			fprintf(FP, "%s", proto.c_str());
	}
//}}}
//{{{
	void emit_define(std::string structure, FILE *FP)
	{
		if(isfunc)
			fprintf(FP,"#define %s (%s->%s)\n", name.c_str(), structure.c_str(),
			                                    name.c_str());
		else
			fprintf(FP, "%s", proto.c_str());
	}
//}}}
//{{{
	void emit_macro(std::string macro, int N, FILE *FP)
	{
		if(isfunc)
			fprintf(FP,"%s(%s, %i)\n", macro.c_str(), name.c_str(), N);
		else
			fprintf(FP, "%s", proto.c_str());
	}
//}}}
//{{{
	void emit_format(const char *format, int N, FILE *FP)
	{
		int ii;
		
		if(!isfunc) {
			fprintf(FP, "%s", proto.c_str());
			return;
		}
		while(*format)
		{
			if(*format != '%')
				putc(*format, FP);
			else {
				format++;
				switch(*format) {
					case 'a': //argument list
						fprintf(FP, "%s", paramlist.c_str()); break;
					case 'c': //argument count
						fprintf(FP, "%i", count_args()); break;
					case 'i': //prototype index
						fprintf(FP, "%i", N); break;
					case 'n': //function name
						fprintf(FP, "%s", name.c_str()); break;
					case 'r': //return-type
						fprintf(FP, "%s", type.c_str()); break;
					case 'S': //sequence
						for(ii=0; ii<count_args(); ii++) {
							if(ii) putc(',', FP);
							if(ii<=26) fputc('a'+ii, FP);
							else fprintf(FP, "a%i", ii);
						}
						break;
				}
			}
			format++;
		}
	}
//}}}
//{{{
	int count_args(void)
	{
		int num_parens = 1;
		int arg_count = 1;
		const char *pos = proto.c_str();
		
			// Advance to the first open-paren
		while(*pos!='(' && *pos) pos++;
		if(!*pos) return 0;
		pos++;
			// Skip whitespace
		while(isspace(*pos) && *pos) pos++;
			// If the args list is () or (void), return 0
		if(*pos==')' || !strncmp(pos,"void",4))
			return 0;
		
		while(*pos) {
			if(*pos == '(') num_parens++;
			else if(*pos == ')') num_parens--;
			else if(*pos == ',' && num_parens == 1) arg_count++;
			pos++;
		}
		return arg_count;
	}
//}}}
	void make_exported(void) { exported=true; }
	void mark(const char *m) { marker = m; }
	bool is_exported(void) { return exported; }
	bool is_function(void) { return isfunc; }
	std::string getName(void) { return name; }
	
private:
	bool isfunc;
	bool exported;
	std::string proto;
	std::string type, name, paramlist, marker;
};
//}}}
//{{{
 // Command documentation
//
//   source <command>
//   file <target>
//
//   echo <text>
//
//   export <symbols>
//   segment <name> <symbols>
//   clear
//   prune
//
//   emit_prototype
//   emit_defines <structure>
//   emit_format
//         %a argument list
//         %c argument count
//         %i prototype index
//         %n function name
//         %r return-type
//         %S A sequence a, b, ... with %c elements
//}}}
//{{{
class ControlFile
{
public:
//{{{
	ControlFile(const char *filename)
	{
		sourcefile = filename;
		out = NULL;
	}
//}}}
//{{{
	int command(char *cmd, int lineno)
	{
		int ii;
		// Remove '#'-style comments
		for(ii=0; cmd[ii] != '\0'; ii++) {
			if(cmd[ii] == '#')
			{
				if(ii>0 && cmd[ii-1]=='\\') {
					memmove(cmd+ii-1, cmd+ii, strlen(cmd+ii)+1);
					ii--;
				} else {
					cmd[ii] = '\n';
					cmd[ii+1] = '\0';
				}
			}
		}
		
		// Check whether only whitespace is left over
		for(ii=0; cmd[ii] != '\0'; ii++) {
			if(!isspace(cmd[ii])) break;
		}
		if(cmd[ii]=='\0') // No non-whitespace here; just return success
			return 1;
		
		try
		{
			if(match_keyword(cmd, "file"))
				return command_file(cmd, lineno);
			else if(match_keyword(cmd, "echo"))
				return command_echo(cmd, lineno);
			else if(match_keyword(cmd, "source"))
				return command_source(cmd, lineno);
			else if(match_keyword(cmd, "emit_prototypes"))
				return command_emit_prototypes(cmd, lineno);
			else if(match_keyword(cmd, "emit_as_macro"))
				return command_emit_as_macro(cmd, lineno);
			else if(match_keyword(cmd, "emit_defines"))
				return command_emit_defines(cmd, lineno);
			else if(match_keyword(cmd, "emit_format"))
				return command_emit_format(cmd, lineno);
			else if(match_keyword(cmd, "clear"))
				return command_clear(cmd, lineno);
			else if(match_keyword(cmd, "export"))
				return command_export(cmd, lineno);
			else if(match_keyword(cmd, "mark"))
				return command_mark(cmd, lineno);
			else if(match_keyword(cmd, "prune"))
				return command_prune(cmd, lineno);
			else
				return command_default(cmd, lineno);
		}
		catch(OutputRequired)
		{
			fprintf(stderr, "%s:%i: No file opened to write to.\n",
							sourcefile, lineno);
			return 0;
		};
	}
//}}}
//{{{
	void require_output(void)
	{
		if(!out)
			throw OutputRequired();
	}
//}}}
	
//{{{
	int command_file(char *cmd, int lineno)
	{
		std::string filename = extract_arg(cmd, 2);
		if(out) std::fclose(out);
		out = std::fopen( filename.c_str(), "w" );
		if(!out) {
			std::fprintf(stderr, "%s:%i: Error opening output file '%s'.\n",
								 sourcefile, lineno, filename.c_str());
			return 0;
		}
		return 1;
	}
//}}}
//{{{
	int command_echo(char *cmd, int lineno)
	{
		advance_arg((const char**)&cmd);
		return echo(cmd, lineno);
	}
//}}}
//{{{
	int command_source(char *cmd, int lineno)
	{
		if(out)
			fflush(out);
		advance_arg((const char**)&cmd);
		FILE *fin = popen(cmd, "r");
		char inbuf[512];
		
		if(verbose_mode)
			std::printf("%s", cmd);
		
		if(!fin) {
			std::fprintf(stderr, "%s:%i: Failed executing command.\n",
								 sourcefile, lineno);
			return 0;
		}
		while(!feof(fin)) {
			if(!std::fgets(inbuf, 512, fin))
				break;
			functions.push_back( FunctionDefinition(inbuf) );
		}
		std::fclose(fin);
		return 1;
	}
//}}}
//{{{
	int command_emit_prototypes(char *cmd, int lineno)
	{
		require_output();
		for(unsigned ii=0; ii<functions.size(); ii++)
			functions[ii].emit_prototype(out);
		return 1;
	}
//}}}
//{{{
	int command_emit_as_macro(char *cmd, int lineno)
	{
		int n=1;
		require_output();
		for(unsigned ii=0; ii<functions.size(); ii++)
		{
			functions[ii].emit_macro(extract_arg(cmd, 2), n, out);
			if(functions[ii].is_function()) n++;
		}
		return 1;
	}
//}}}
//{{{
	int command_emit_defines(char *cmd, int lineno)
	{
		require_output();
		for(unsigned ii=0; ii<functions.size(); ii++)
			functions[ii].emit_define(extract_arg(cmd, 2), out);
		return 1;
	}
//}}}
//{{{
	int command_emit_format(char *cmd, int lineno)
	{
		int N=0;
		require_output();
		advance_arg((const char**)&cmd);
		for(unsigned ii=0; ii<functions.size(); ii++) {
			functions[ii].emit_format(cmd, N, out);
			if(functions[ii].is_function()) N++;
		}
		return 1;
	}
//}}}
//{{{
	int command_clear(char *cmd, int lineno)
	{
		functions.resize(0);
		return 1;
	}
//}}}
//{{{
	int command_export(char *cmd, int lineno)
	{
		bool export_success;
		
		std::string export_name;
		
		while( advance_arg((const char**)&cmd) )
		{
			export_name = std::string(extract_arg(cmd, 1));
			export_success = false;
			for(unsigned ii=0; ii<functions.size(); ii++) {
				if(functions[ii].getName() == export_name) {
					functions[ii].make_exported();
					export_success = true;
					break;
				}
			}
			if(!export_success) {
				fprintf(stderr, "%s:%i: Warning: Symbol '%s' not found.\n",
								sourcefile, lineno, export_name.c_str());
			}
		}
		return 1;
	}
//}}}
//{{{
	int command_mark(char *cmd, int lineno)
	{
		bool mark_success;
		
		std::string mark;
		std::string func_name;
		
		advance_arg((const char**)&cmd);
		mark = extract_arg(cmd, 1);
		
		while( advance_arg((const char**)&cmd) )
		{
			func_name = std::string(extract_arg(cmd, 1));
			mark_success = false;
			for(unsigned ii=0; ii<functions.size(); ii++) {
				if(functions[ii].getName() == func_name) {
					functions[ii].mark(mark.c_str());
					mark_success = true;
					break;
				}
			}
			if(!mark_success) {
				fprintf(stderr, "%s:%i: Warning: Symbol '%s' not found.\n",
								sourcefile, lineno, func_name.c_str());
			}
		}
		return 1;
	}
//}}}
//{{{
	int command_prune(char *cmd, int lineno)
	{
		unsigned outpos = 0;
		for(unsigned ii=0; ii<functions.size(); ii++)
		{
			if(!functions[ii].is_function() || functions[ii].is_exported())
				functions[outpos++] = functions[ii];
		}
		functions.resize(outpos);
		return 1;
	}
//}}}
//{{{
	int command_default(char *cmd, int lineno)
	{
		fprintf(stderr, "%s:%i: Invalid command.\n",
						sourcefile, lineno);
		return 0;
	}
//}}}
	
//{{{
	int echo(const char *str, int lineno)
	{
		require_output();
		fprintf(out, "%s", str);
		return 1;
	}
//}}}
//{{{
	bool match_keyword(const char *cmd, const char *keyword)
	{
		while(isspace(*cmd))
			cmd++;
		if(!strncmp(keyword, cmd, strlen(keyword)))
			return true;
		else
			return false;
	}
//}}}
//{{{
	bool advance_arg(const char **arg)
	{
		// Advance past one token plus any whitespace after it
		while(isspace(**arg)) (*arg)++;
		while(!isspace(**arg) && **arg!='\0') (*arg)++;
		while(isspace(**arg)) (*arg)++;
		if(**arg=='\0') return false;
		else return true;
	}
//}}}
//{{{
	std::string extract_arg(const char *cmd, int argno)
	{
		int ii;
		for(ii=1; ii<argno; ii++)
			advance_arg(&cmd);
		std::string ret("");
		while(isspace(*cmd)) cmd++;
		while(!isspace(*cmd)) ret += *(cmd++);
		return ret;
	}
//}}}
	
private:
	class OutputRequired {};
	
	const char *sourcefile;
	FILE *out;
	
	std::vector<FunctionDefinition> functions;
};
//}}}

//{{{
int main(int argc, char **argv)
{
	int ii;
	
	if(argc < 2) {
		show_help_text(argv[0]);
		return 0;
	}
	
	for(ii=1; ii<argc; ii++)
	{
		if(!strcmp(argv[ii], "-h") || !strcmp(argv[ii], "--help")) {
			show_help_text(argv[0]);
			return 0;
		} else if(!strcmp(argv[ii], "-v") || !strcmp(argv[ii], "--verbose")) {
			verbose_mode = 1;
		} else if(!strcmp(argv[ii], "-V") || !strcmp(argv[ii], "--version")) {
			show_version_text();
			return 0;
		} else {
			process_file(argv[ii]);
		}
	}
	
	return error_count;
}
//}}}

//{{{
void show_help_text(const char *invocation)
{
	printf(
	"Usage: %s [options] control-file\n"
	"\n"
	"  -v Verbose mode\n"
	"  -h Show help text\n"
	"  -V Show version information\n",
		invocation);
}
//}}}
//{{{
void show_version_text(void)
{
	printf(
"mkinterface " VERSION_STRING ", copyright (C) 2004 by Jim Babcock.\n"
"This is free software; see the source for copying conditions. There is NO\n"
"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
		);
}
//}}}

//{{{
void process_file(const char *filename)
{
	FILE *fin = fopen(filename, "r");
	ControlFile file(filename);
	char inbuf[4096];
	int lineno = 0;
	
	if(!fin) {
		fprintf(stderr, "%s: Couldn't open file.\n", filename);
		error_count++;
		return;
	}
	
	while(!feof(fin))
	{
		if(fgets(inbuf, 4096, fin) == NULL)
			break;
		
		if(!file.command(inbuf, ++lineno)) {
			error_count++;
			break;
		}
	}
	
	fclose(fin);
}
//}}}
