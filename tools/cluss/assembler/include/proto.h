/* src/bin2oth.c */
unsigned char *DataBuffer2OTHBuffer(int calctype, const char *folder, const char *varname, const char *extension, unsigned int inlength, const unsigned char *indata, unsigned int *outlength);
/* src/directive.c */
int evaluate_directive(const char *directive, FILE *input, code_object *obj);
/* src/format.c */
void set_output_format(const char *format);
int code_object_output(code_object *_this, const char *output_filename);
int output_text(code_object *_this, const char *output_filename);
int output_multi(code_object *_this, const char *output_filename);
int output_binary(code_object *_this, const char *output_filename);
int output_palm(code_object *_this, const char *output_filename);
int output_ticalc(code_object *_this, const char *output_filename);
void segment_output(segment *_this, FILE *fout);
void segment_print(segment *_this, FILE *fout);
/* src/instruction.c */
int evaluate_instruction(const char *instruction, FILE *input, code_object *obj);
/* src/label.c */
unsigned read_label(code_object *obj, FILE *input);
unsigned lookup_label(code_object *obj, const char *key);
const char *lookup_label_string(code_object *obj, unsigned label);
unsigned num_labels(code_object *obj);
unsigned hash_string(const char *str);
int relocate(code_object *_this);
/* src/main.c */
void init_getopt(int argc, char **argv);
const char *getopt(void);
int main(int argc, char **argv);
void initialize(void);
void print_help_text(const char *progname);
void print_version_text(void);
/* src/tokenize.c */
void tokenizer_init(void);
int get_token(FILE *input);
const char *token_string(void);
/* src/util.c */
void error(const char *fmt, ...);
void fatal(const char *fmt, ...);
void check_endianness(void);
short htots(short S);
long htotl(long L);
long round_up(long A, long V);
void fill_word(unsigned char *data, unsigned short val);
void fill_long(unsigned char *data, unsigned long val);
FILE *open_output_filename(const char *filename);
const char *retprintf(const char *format, ...);
const char *vretprintf(const char *format, va_list args);
char *strnfill(char *DST, const char *STR, unsigned LEN);
/* src/write.c */
int assemble_file(FILE *input_file, const char *output_filename);
int assemble_instruction(FILE *input_file, code_object *obj);
long get_numeric_argument(FILE *input);
void eat_argument(FILE *input);
code_object *code_object_new(void);
void code_object_delete(code_object *_this);
void code_object_segment_size(code_object *_this, int max_size);
void write_byte(code_object *_this, unsigned char byte);
void split_current_seg(code_object *_this);
void write_short(code_object *_this, short data);
void write_long(code_object *_this, long data);
void write_data(code_object *_this, const char *data, unsigned length);
void write_splitpoint(code_object *_this);
void write_alignment(code_object *_this, int alignment, int pad_char, int offset);
void write_relocation(code_object *_this, relocation_data *relocation);
void write_label(code_object *_this, long label, short flags);
void write_extern(code_object *_this, long label, long flags, long offset);
void write_reference(code_object *_this, long label, int dest_off);
void write_rel_byte(code_object *_this, long label, int dest_off);
void write_rel_short(code_object *_this, long label, int dest_off);
void write_abs_short(code_object *_this, long label, int dest_off);
void write_rel_long(code_object *_this, long label, int dest_off);
void write_abs_3byte(code_object *_this, long label, int dest_off);
segment *segment_new(void);
void segment_delete(segment *_this);
segment *segment_new_from(segment *seg);
