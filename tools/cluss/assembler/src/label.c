#include "cluss.h"
#include <string.h>
#include <stdlib.h>

//{{{
typedef struct label_location {
	unsigned segment;
	unsigned offset;
	short flags;
} label_location;
//}}}
static void fill_relocation(unsigned char *data, label_location *target, signed offset);

//{{{
unsigned read_label(code_object *obj, FILE *input)
{
	int tok_type = get_token(input);
	const char *string = token_string();
	
	if(tok_type != TOK_IDENTIFIER) {
		error("Identifier expected.");
		return 0;
	}
	
	return lookup_label(obj, string);
}
//}}}
//{{{
// Hash table sizes should be prime, and should roughly double with each
// step. Thus, a table of primes close to powers of 2.
const unsigned hash_sizes[] = {
		13, 31, 61, 127, 251, 509, 1021, 2053, 4094, 8191,
		16381, 32771, 65521, 131071, 262139, 524287, 1048576
	};
//}}}
//{{{
unsigned lookup_label(code_object *obj, const char *key)
{
	unsigned hash_key = hash_string(key);
	const unsigned *size_pos;
	unsigned pos, ii;
	unsigned ret;
	identifier_info *new_hash;
	
	if(!obj->ident_alloc) {
		obj->ident_alloc = hash_sizes[0];
		obj->ident_hash = (identifier_info*)calloc(obj->ident_alloc,
		                                           sizeof(identifier_info));
	}
	
	// Search the hash table
	pos = hash_key % obj->ident_alloc;
	while(obj->ident_hash[pos].key)
	{
		if(obj->ident_hash[pos].hash_key == hash_key &&
		   !strcmp(obj->ident_hash[pos].key, key)) {
			return obj->ident_hash[pos].value;
		}
		pos++;
		if(pos >= obj->ident_alloc)
			pos = 0;
	}
	
	// It's not there! Have to add it, then. The search left pos at the spot
	// where it would've been.
	obj->ident_hash[pos].hash_key = hash_key;
	obj->ident_hash[pos].key = strdup(key);
	ret = obj->ident_hash[pos].value = obj->ident_num++;
	
	// If it's getting cramped, enlarge
	if(obj->ident_num*2 < obj->ident_alloc)
		return ret;
	
	size_pos = hash_sizes;
	while(*size_pos <= obj->ident_alloc) size_pos++;
	
	new_hash = (identifier_info*)calloc(*size_pos, sizeof(identifier_info));
	for(ii=0; ii<obj->ident_alloc; ii++) {
		if( obj->ident_hash[ii].key == NULL )
			continue;
		pos = hash_string(obj->ident_hash[ii].key) % *size_pos;
		while(new_hash[pos].key) {
			pos++;
			if(pos >= *size_pos)
				pos = 0;
		}
		new_hash[pos] = obj->ident_hash[ii];
	}
	
	free(obj->ident_hash);
	obj->ident_hash = new_hash;
	obj->ident_alloc = *size_pos;
	
	return ret;
}
//}}}
//{{{
const char *lookup_label_string(code_object *obj, unsigned label)
{
	unsigned pos;
	
	for(pos=0; pos<obj->ident_alloc; pos++) {
		if(obj->ident_hash[pos].value == label)
			return obj->ident_hash[pos].key;
	}
	return NULL;
}
//}}}
//{{{
unsigned num_labels(code_object *obj)
{
	return obj->ident_num;
}
//}}}
//{{{
unsigned hash_string(const char *str)
{
	unsigned ret = 0;
	while(*str)
	{
		ret += ret;
		ret ^= *str;
		ret ^= (ret>>20);
		str++;
	}
	return ret;
}
//}}}

//{{{
int relocate(code_object *_this)
{
	label_location *labels;
	unsigned num = num_labels(_this);
	unsigned ii, jj;
	relocation_data *reloc;
	
	//
	// Collect labels
	//
	labels = calloc(num_labels(_this), sizeof(label_location));
	for(ii=0; ii<num; ii++) {
		// Mark labels as not found first
		labels[ii].segment = -1;
	}
	
	for(ii=0; ii<_this->num_segments; ii++)
	for(jj=0; jj<_this->data[ii]->num_labels; jj++)
	{
		reloc = &_this->data[ii]->labels[jj];
		switch(reloc->type)
		{
			case RELOCATION_TARGET:
				labels[reloc->identifier].segment = ii;
				labels[reloc->identifier].offset = reloc->offset;
				labels[reloc->identifier].flags = reloc->flags;
				break;
			case RELOCATION_FORCE:
				labels[reloc->identifier].segment = 0;
					/* Segment is ignored with special (non-real-link) links */
					/* TODO: But set it to something controllable anyways */
				labels[reloc->identifier].offset = reloc->target_offset;
				labels[reloc->identifier].flags = reloc->flags;
				break;
		}
	}
	
	//
	// Apply relocations
	//
	for(ii=0; ii<_this->num_segments; ii++)
	for(jj=0; jj<_this->data[ii]->num_labels; jj++)
	{
		reloc = &_this->data[ii]->labels[jj];
		
		if(reloc->type == RELOCATION_TARGET || reloc->type == RELOCATION_FORCE)
			continue;
		if(labels[reloc->identifier].segment == -1) {
			error("Undefined external symbol: %s", 
			      lookup_label_string(_this, reloc->identifier));
		}
		
		switch(reloc->type)
		{
			case RELOCATION_SOURCE:
				fill_relocation(_this->data[ii]->data + reloc->offset,
								&labels[reloc->identifier],
				                reloc->target_offset);
				break;
			case RELOCATION_REL_BYTE:
				if(ii != labels[reloc->identifier].segment)
					error("Byte-relative addressing crosses segment boundary.");
				else {
					_this->data[ii]->data[reloc->offset] =
						labels[reloc->identifier].offset - reloc->offset
						+ reloc->target_offset;
				}
				break;
			case RELOCATION_REL_SHORT:
				if(ii != labels[reloc->identifier].segment)
					error("Short-relative addressing crosses segment boundary.");
				else {
					fill_word(_this->data[ii]->data + reloc->offset,
						labels[reloc->identifier].offset - reloc->offset
						+ reloc->target_offset);
				}
				break;
			case RELOCATION_ABS_SHORT:
				if(ii != labels[reloc->identifier].segment)
					error("Incomplete addressing crosses segment boundary.");
				else {
					fill_word(_this->data[ii]->data + reloc->offset,
						labels[reloc->identifier].offset
						+ reloc->target_offset);
				}
				break;
			case RELOCATION_REL_LONG:
				if(ii != labels[reloc->identifier].segment)
					error("Long-relative addressing crosses segment boundary.");
				else {
					fill_long(_this->data[ii]->data + reloc->offset,
						labels[reloc->identifier].offset - reloc->offset
						+ reloc->target_offset);
				}
				break;
			case RELOCATION_ABS_3BYTE:
				fill_word(_this->data[ii]->data + reloc->offset,
					labels[reloc->identifier].offset
					+ reloc->target_offset);
				_this->data[ii]->data[reloc->offset+2] =
					labels[reloc->identifier].segment;
				break;
		}
	}
	
	return 1;
}
//}}}
//{{{
static void fill_relocation(unsigned char *data, label_location *target, signed offset)
{
	data[0] = target->flags;
	data[1] = target->segment;
	fill_word(data+2, target->offset + offset);
}
//}}}

