#include "cluss.h"
#include <string.h>
#include <stdlib.h>

int output_format = FMT_BINARY;

int host_endianness;
int target_endianness = ENDIAN_BIG;
int short_alignment = 2;
int long_alignment = 2;
int reference_alignment = 2;
int reference_size = 4;
int target_max_size = 65000;

//{{{
void set_output_format(const char *format)
{
	if(!strcasecmp(format, "bigendian")) {
		target_endianness = ENDIAN_BIG;
		output_format = FMT_BINARY;
	}
	else if(!strcasecmp(format, "littleendian")) {
		target_endianness = ENDIAN_LITTLE;
		output_format = FMT_BINARY;
	}
	else if(!strcasecmp(format, "reverse")) {
		target_endianness = !host_endianness;
		output_format = FMT_BINARY;
	}
	else if(!strcasecmp(format, "text")) { // Mostly for debugging
		target_endianness = host_endianness;
		output_format = FMT_TEXTUAL;
		target_max_size = 32;
	}
	
	else if(!strcasecmp(format, "native")) {
		target_endianness = host_endianness;
		output_format = FMT_MULTI;
		target_max_size = 32768;
	}
	else if(!strcasecmp(format, "palmos")) {
		target_endianness = ENDIAN_BIG;
		output_format = FMT_PALMOS;
		target_max_size = 32768;
	}
	else if(!strcasecmp(format, "ticalc")) {
		target_endianness = ENDIAN_BIG;
		output_format = FMT_TICALC;
		target_max_size = 65300;
	}
}
//}}}

//{{{
int code_object_output(code_object *_this, const char *output_filename)
{
	if(output_format == FMT_TEXTUAL)
		return output_text(_this, output_filename);
	else if(output_format == FMT_BINARY)
		return output_binary(_this, output_filename);
	else if(output_format == FMT_MULTI)
		return output_multi(_this, output_filename);
	else if(output_format == FMT_PALMOS)
		return output_palm(_this, output_filename);
	else if(output_format == FMT_TICALC)
		return output_ticalc(_this, output_filename);
	else
		fatal("Invalid output format.");
	return 0;
}
//}}}
//{{{
int output_text(code_object *_this, const char *output_filename)
{
	FILE *fout;
	int ii;
	
	if( !( fout=open_output_filename(output_filename) ) )
		return 0;
	
	printf("%i total segments\n", (int)_this->num_segments);
	
	for(ii=0; ii<_this->num_segments; ii++)
	{
		printf("Segment %i:\n", ii);
		segment_print(_this->data[ii], fout);
	}
	
	fclose(fout);
	return 1;
}
//}}}
//{{{
int output_multi(code_object *_this, const char *output_filename)
{
	FILE *fout;
	unsigned ii;
	const char *magic = "CLuS";
	unsigned long out;
	
	if( !(fout=open_output_filename( retprintf("%s",output_filename) )))
		return 0;
	
		// Write header
	fwrite(magic, 4, 1, fout);
		// Write segment count
	out=_this->num_segments; fwrite(&out, sizeof(out), 1, fout);
	
		// Write segments
	for(ii=0; ii<_this->num_segments; ii++) {
			// Write size, rounded up to the nearest multiple of 4 (for
			// alignment purposes)
		out = round_up(4, _this->data[ii]->size);
		fwrite(&out, sizeof(out), 1, fout);
			// Write content
		segment_output(_this->data[ii], fout);
	}
	
	fclose(fout);
	return 1;
}
//}}}
//{{{
int output_binary(code_object *_this, const char *output_filename)
{
	FILE *fout;
	unsigned ii;
	if( !( fout=open_output_filename(output_filename) ) )
		return 0;
	for(ii=0; ii<_this->num_segments; ii++)
		segment_output(_this->data[ii], fout);
	fclose(fout);
	return 1;
}
//}}}
//{{{
int output_palm(code_object *_this, const char *output_filename)
{
	int ii;
	FILE *fout;
	unsigned long count;
	
	if( !(fout=open_output_filename( retprintf("%s.rcp",output_filename) )))
		return 0;
	
	for(ii=0; ii<_this->num_segments; ii++) {
		fprintf(fout, "DATA \"CRdt\" ID %i \"%s_%i.dat\"\n",
			900+ii, output_filename, ii);
	}
	fclose(fout);
	
	for(ii=0; ii<_this->num_segments; ii++)
	{
		fout=open_output_filename(
				 retprintf("%s_%i.dat", output_filename, ii) );
		if(!fout)
			return 0;
		
		// The first segment begins with a segment count
		if(ii==0) {
			count = htotl(_this->num_segments);
			fwrite(&count, sizeof(count), 1, fout);
		}
		
		segment_output(_this->data[ii], fout);
		fclose(fout);
	}
	return 1;
}
//}}}
//{{{
int output_ticalc(code_object *_this, const char *output_filename)
{
	unsigned long out_size;
	long *buf;
	int ii;
	char oncalc_name[32];
	char full_filename[32];
	char suffix;
	char *data;
	unsigned outlength;
	FILE *fout;
	
	for(ii=0; ii<_this->num_segments; ii++)
	{
		out_size = _this->data[ii]->size;
		if(ii==0) out_size += 4;
		out_size = round_up(4, out_size);
		
		buf = (long*)calloc(out_size, 1);
		
		if(ii==0) { // The first segment begins with a segment count
			*buf = htotl(_this->num_segments);
			memcpy(buf+1, _this->data[ii]->data, _this->data[ii]->size);
		} else {
			memcpy(buf, _this->data[ii]->data, _this->data[ii]->size);
		}
		
		if(ii < 9) suffix = '1' + ii;
		else suffix = ii - 10 + 'A';
		snprintf(oncalc_name, 32, "%s%c", output_filename, suffix);
		snprintf(full_filename, 32, "%s%c.89y", output_filename, suffix);
		
		data = DataBuffer2OTHBuffer( 0, /* calctype */
		                             NULL,
		                             oncalc_name,
		                             "DAT",
		                             out_size,
		                             (unsigned char*)buf,
		                             &outlength);
		fout = fopen(full_filename, "wb");
		fwrite(data, outlength, 1, fout);
		
		free(buf);
		free(data);
		fclose(fout);
	}
	return 1;
}
//}}}

//{{{
void segment_output(segment *_this, FILE *fout)
{
	int ii;
	
	// Write data
	for(ii=0; ii<_this->size; ii++)
		fputc(_this->data[ii]&0xFF, fout);
	
	// Write padding to make this size a multiple of four
	for(ii=0; ii < round_up(4,_this->size)-_this->size; ii++)
		fputc(0, fout);
}
//}}}
//{{{
void segment_print(segment *_this, FILE *fout)
{
	int ii;
	fprintf(fout, "size %i, last split at %i\n",
	       _this->size, _this->last_splitpoint);
	for(ii=0; ii<_this->num_labels; ii++) {
		switch(_this->labels[ii].type) {
			case RELOCATION_TARGET: fprintf(fout, "label"); break;
			case RELOCATION_FORCE: fprintf(fout, "extern"); break;
			case RELOCATION_SOURCE: fprintf(fout, "link "); break;
			case RELOCATION_REL_BYTE: fprintf(fout, "rel8link "); break;
			case RELOCATION_REL_SHORT: fprintf(fout, "rel16link "); break;
			case RELOCATION_ABS_SHORT: fprintf(fout, "abs16link "); break;
			case RELOCATION_REL_LONG: fprintf(fout, "rel32link "); break;
			case RELOCATION_ABS_3BYTE: fprintf(fout, "abs24link "); break;
		}
		fprintf(fout, " @%i: %i\n", (int)_this->labels[ii].offset,
		                         (int)_this->labels[ii].identifier);
	}
	for(ii=0; ii<_this->size; ii++) {
		if(ii && !(ii%16)) putc('\n', fout);
		fprintf(fout, "%2x ", _this->data[ii]&0xFF);
	}
	putc('\n', fout);
}
//}}}
