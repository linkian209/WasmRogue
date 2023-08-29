#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include "cluss.h"

//{{{
int assemble_file(FILE *input_file, const char *output_filename)
{
	code_object *obj = code_object_new();
	code_object_segment_size(obj, target_max_size);
	
	while(!feof(input_file)) { // Error - Bail out
		if( !assemble_instruction(input_file, obj) )
			return 1;
		if( error_count )
			return 1;
	}
	
	if(!relocate(obj))
		return 1;
	code_object_output(obj, output_filename);
	code_object_delete(obj);
	
	return error_count;
}
//}}}
//{{{
int assemble_instruction(FILE *input_file, code_object *obj)
{
	int token_type;
	const char *token_text;
	
	token_type = get_token(input_file);
	token_text = token_string();
	
	if(token_type == TOK_EOF) {
		return 1;
	} else if(token_type != TOK_IDENTIFIER) {
		error("Parse error.");
		return 0;
	}
	
	if(*token_text == '.')
		return evaluate_directive(token_text, input_file, obj);
	else
		return evaluate_instruction(token_text, input_file, obj);
}
//}}}

//{{{
long get_numeric_argument(FILE *input)
{
	int token_type = get_token(input);
	const char *string = token_string();
	
	if(token_type != TOK_INTEGER) {
		error("Numeric argument expected.");
		return 0;
	}
	
	return atol(string);
}
//}}}
//{{{
void eat_argument(FILE *input)
{
	get_token(input);
}
//}}}

//{{{
code_object *code_object_new(void)
{
	code_object *ret = (code_object*)malloc(sizeof(code_object));
	if(!ret) fatal("Out of memory!");
	ret->num_segments = 1;
	ret->data = (segment**)malloc(ret->num_segments * sizeof(segment*));
	ret->data[0] = ret->current_seg = segment_new();
	ret->max_seg_size = 32768;
	ret->ident_num = ret->ident_alloc = 0;
	ret->ident_hash = NULL;
	if(!ret->data) fatal("Out of memory!");
	return ret;
}
//}}}
//{{{
void code_object_delete(code_object *_this)
{
	int ii;
	for(ii=0; ii<_this->num_segments; ii++)
		segment_delete(_this->data[ii]);
	free(_this->data);
	free(_this);
}
//}}}
//{{{
void code_object_segment_size(code_object *_this, int max_size)
{
	_this -> max_seg_size = max_size;
}
//}}}
//{{{
void write_byte(code_object *_this, unsigned char byte)
{
	segment *current_seg = _this->current_seg;
	
	// If over allocated space, enlarge
	if( current_seg->size >= current_seg->alloc ) {
		current_seg->alloc *= 2;
		current_seg->data = (char*)realloc( current_seg->data,
		                                    current_seg->alloc );
	}
	
	// If over max segment size, split
	if(current_seg->size >= _this->max_seg_size) {
		split_current_seg(_this);
	}
	
	// Write byte
	_this->current_seg->data[_this->current_seg->size++] = byte;
}
//}}}
//{{{
void split_current_seg(code_object *_this)
{
	segment *current_seg = _this->current_seg;
	segment *new_segment;
	unsigned ii;
	
	_this->num_segments++;
	_this->data=(segment**)realloc(_this->data,
								   sizeof(segment*) * _this->num_segments);
	_this->data[_this->num_segments-1] = segment_new_from(current_seg);
	
	new_segment = _this->data[_this->num_segments-1];
	current_seg->tail_segment = _this->num_segments-1;
	_this->current_seg = new_segment;
	
	new_segment->size = current_seg->size - current_seg->last_splitpoint;
	
	// Verify that there is a splitpoint placed appropriately
	if(new_segment->size >= _this->max_seg_size)
	{
		if(current_seg->last_splitpoint == 0)
			error("Segment too big and has no split points.");
		else
			error("Segment too big and split points are too far apart.");
		
		// Continue by forcibly splitting the segment anyways
		current_seg->last_splitpoint = _this->max_seg_size;
		new_segment->size = current_seg->size - current_seg->last_splitpoint;
	}
	
	// Enlarge the new segment up to size
	new_segment->alloc = 8;
	while(new_segment->alloc < new_segment->size)
		new_segment->alloc *= 2;
	new_segment->data=(char*)realloc(new_segment->data, new_segment->alloc);
	
	// Move data from the old segment into the new one
	memcpy( new_segment->data,
			current_seg->data+current_seg->last_splitpoint,
			new_segment->size );
	current_seg->size -= new_segment->size;
	
	// Move relocation entries from the old segment into the new one
	for( ii=current_seg->last_reloc_split;
		 ii<current_seg->num_labels; ii++ ) {
		current_seg->labels[ii].offset -= current_seg->size;
		write_relocation(_this, &current_seg->labels[ii]);
	}
	current_seg->num_labels = current_seg->last_reloc_split;
	_this->current_seg = new_segment;
}
//}}}
//{{{
void write_short(code_object *_this, short data)
{
	data = htots(data);
	write_data(_this, (char*)&data, sizeof(short));
}
//}}}
//{{{
void write_long(code_object *_this, long data)
{
	data = htotl(data);
	write_data(_this, (char*)&data, sizeof(long));
}
//}}}
//{{{
void write_data(code_object *_this, const char *data, unsigned length)
{
	unsigned ii;
	for(ii=0; ii<length; ii++)
		write_byte(_this, data[ii]);
}
//}}}
//{{{
void write_splitpoint(code_object *_this)
{
	_this->current_seg->last_splitpoint = _this->current_seg->size;
	_this->current_seg->last_reloc_split = _this->current_seg->num_labels;
}
//}}}
//{{{
// Write pad_char until position is congruent to offset (mod alignment)
void write_alignment(code_object *_this, int alignment, int pad_char,int offset)
{
	while( (_this->current_seg->size - offset) % alignment )
		write_byte(_this, pad_char);
}
//}}}
//{{{
void write_relocation(code_object *_this, relocation_data *relocation)
{
	segment *seg = _this->current_seg;
	
	if(seg->num_labels >= seg->labels_alloc) {
		if(!seg->labels_alloc) {
			seg->labels_alloc = 8;
			seg->labels=(relocation_data*)malloc(
				sizeof(relocation_data)*seg->labels_alloc);
		} else {
			seg->labels_alloc <<= 1;
			seg->labels = (relocation_data*)realloc( seg->labels,
				sizeof(relocation_data)*seg->labels_alloc);
		}
	}
	seg->labels[seg->num_labels++] = *relocation;
}
//}}}
//{{{
void write_label(code_object *_this, long label, short flags)
{
	relocation_data addition;
	addition.type = RELOCATION_TARGET;
	addition.offset = _this->current_seg->size;
	addition.target_offset = 0;
	addition.identifier = label;
	addition.flags = flags;
	write_relocation(_this, &addition);
}
//}}}
//{{{
void write_extern(code_object *_this, long label, long flags, long offset)
{
	relocation_data addition;
	addition.type = RELOCATION_FORCE;
	addition.offset = offset;
	addition.target_offset = offset;
	addition.identifier = label;
	addition.flags = flags;
	write_relocation(_this, &addition);
}
//}}}
//{{{
void write_reference(code_object *_this, long label, int dest_off)
{
	relocation_data addition;
	int ii;
	
	addition.type = RELOCATION_SOURCE;
	addition.offset = _this->current_seg->size;
	addition.target_offset = dest_off;
	addition.identifier = label;
	addition.flags = 0;
	write_alignment(_this, reference_alignment, 0, 0);
	write_relocation(_this, &addition);
	for(ii=0; ii<reference_size; ii++)
		write_byte(_this, 0);
}
//}}}
//{{{
void write_rel_byte(code_object *_this, long label, int dest_off)
{
	relocation_data addition;
	addition.type = RELOCATION_REL_BYTE;
	addition.offset = _this->current_seg->size;
	addition.target_offset = dest_off;
	addition.identifier = label;
	addition.flags = 0;
	write_relocation(_this, &addition);
	write_byte(_this, 0);
}
//}}}
//{{{
void write_rel_short(code_object *_this, long label, int dest_off)
{
	relocation_data addition;
	addition.type = RELOCATION_REL_SHORT;
	addition.offset = _this->current_seg->size;
	addition.target_offset = dest_off;
	addition.identifier = label;
	addition.flags = 0;
	write_relocation(_this, &addition);
	write_byte(_this, 0);
	write_byte(_this, 0);
}
//}}}
//{{{
void write_abs_short(code_object *_this, long label, int dest_off)
{
	relocation_data addition;
	addition.type = RELOCATION_ABS_SHORT;
	addition.offset = _this->current_seg->size;
	addition.target_offset = dest_off;
	addition.identifier = label;
	addition.flags = 0;
	write_relocation(_this, &addition);
	write_byte(_this, 0);
	write_byte(_this, 0);
}
//}}}
//{{{
void write_rel_long(code_object *_this, long label, int dest_off)
{
	relocation_data addition;
	addition.type = RELOCATION_REL_LONG;
	addition.offset = _this->current_seg->size;
	addition.target_offset = dest_off;
	addition.identifier = label;
	addition.flags = 0;
	write_relocation(_this, &addition);
	write_byte(_this, 0); write_byte(_this, 0);
	write_byte(_this, 0); write_byte(_this, 0);
}
//}}}
//{{{
void write_abs_3byte(code_object *_this, long label, int dest_off)
{
	relocation_data addition;
	addition.type = RELOCATION_ABS_3BYTE;
	addition.offset = _this->current_seg->size;
	addition.target_offset = dest_off;
	addition.identifier = label;
	addition.flags = 0;
	write_relocation(_this, &addition);
	write_byte(_this, 0);
	write_byte(_this, 0);
	write_byte(_this, 0);
}
//}}}

//{{{
segment *segment_new(void)
{
	segment *ret = (segment*)malloc( sizeof(segment) );
	ret->size = 0;
	ret->alloc = segment_default_size;
	ret->data = (char*)malloc(ret->alloc);
	ret->last_splitpoint = 0;
	ret->last_reloc_split = 0;
	ret->labels = NULL;
	ret->num_labels = ret->labels_alloc = 0;
	ret->tail_segment = -1;
	return ret;
}
//}}}
//{{{
void segment_delete(segment *_this)
{
	free(_this->data);
	free(_this);
}
//}}}
//{{{
segment *segment_new_from(segment *seg)
{
	segment *ret = segment_new();
	return ret;
}
//}}}

