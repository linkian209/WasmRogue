#ifndef CLUSS_H
#define CLUSS_H

#include <stdio.h>
#include <stdarg.h>

#define TOK_EOF        0
#define TOK_IDENTIFIER 1
#define TOK_INTEGER    2
#define TOK_GROUP      3

#define FMT_BINARY  0
#define FMT_TEXTUAL 1
#define FMT_PALMOS  2
#define FMT_MULTI   3
#define FMT_TICALC  4
extern int output_format;

#define ENDIAN_BIG    0
#define ENDIAN_LITTLE 1

//{{{
typedef struct code_object
{
	unsigned num_segments;
	struct segment **data;
	struct segment *current_seg;
	unsigned max_seg_size;
	
	unsigned ident_num, ident_alloc;
	struct identifier_info *ident_hash;
} code_object;
//}}}
//{{{
typedef struct identifier_info
{
	unsigned hash_key;
	char *key;
	unsigned value;
} identifier_info;
//}}}
//{{{
typedef struct relocation_data
{
	short type;
	short flags;
	unsigned identifier;
	unsigned offset;
	signed target_offset;
} relocation_data;
#define RELOCATION_TARGET    0
#define RELOCATION_FORCE     1
#define RELOCATION_SOURCE    2
#define RELOCATION_REL_BYTE  3
#define RELOCATION_REL_SHORT 4
#define RELOCATION_ABS_SHORT 5
#define RELOCATION_REL_LONG  6
#define RELOCATION_ABS_3BYTE 7
//}}}
//{{{
typedef struct segment
{
	unsigned size, alloc;
	unsigned last_splitpoint;
	unsigned last_reloc_split;
	char *data;
	
	struct relocation_data *labels;
	unsigned num_labels, labels_alloc;
	
	unsigned tail_segment;
} segment;
#define segment_default_size 64
//}}}

extern int host_endianness;
extern int target_endianness;
extern int short_alignment;
extern int long_alignment;
extern int reference_alignment;
extern int reference_size;
extern int target_max_size;
extern int error_count;
extern int lineno;

#include "ticalc.h"
#include "proto.h"

#endif

