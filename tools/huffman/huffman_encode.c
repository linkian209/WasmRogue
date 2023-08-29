#include <stdio.h>
#include "hufftable.h"
#include "huffman.h"

static unsigned long _hp_pending=0;
static unsigned short _hp_pending_length=0;

void fhuffmaninit_write(void)
{
	_hp_pending = 0;
	_hp_pending_length = 0;
}

void fhuffmanputc(unsigned char c, FILE *f)
{
	_hp_pending_length += huff_compress.replen[c];
	_hp_pending |= huff_compress.rep[c] << (32 - _hp_pending_length);
	if(_hp_pending_length >= 16)
		fhuffmanflush(f);
}

void fhuffmanflush(FILE *f)
{
	fputc((char)(_hp_pending>>24), f);
	fputc((char)(_hp_pending>>16), f);
	_hp_pending <<= 16;
	_hp_pending_length -= 16;
}

static unsigned long _hg_pending=0;
static unsigned short _hg_pending_length=0;

void fhuffmaninit_read(void)
{
	_hg_pending = 0;
	_hg_pending_length = 0;
}

char fhuffmangetc(FILE *f)
{
	short high, low, mid;
	unsigned short searchtarget;
	while(_hg_pending_length < 24)
	{
		_hg_pending <<= 8;
		_hg_pending_length += 8;
		if(!feof(f))
			_hg_pending |= fgetc(f);
	}
	searchtarget = _hg_pending >> (_hg_pending_length - 16);
	low = 0;
	high = 255;
	
	do
	{
		mid = (low+high+1)/2;
		if(huff_decompress.entries[mid].binrep > searchtarget)
			high = mid-1;
		else
			low = mid;
	} while(high>low);
	
	_hg_pending <<= (32 + huff_decompress.entries[low].binreplen - _hg_pending_length);
	_hg_pending_length -= huff_decompress.entries[low].binreplen;
	_hg_pending >>= (32 - _hg_pending_length);
	return huff_decompress.entries[low].byterep;
}


