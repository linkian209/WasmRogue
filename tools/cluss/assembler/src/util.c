#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "cluss.h"

int error_count = 0;
//{{{
void error(const char *fmt, ...)
{
	va_list arguments;
	fprintf(stderr, "Line %i: ", lineno);
	va_start(arguments, fmt);
		vfprintf(stderr, fmt, arguments);
		fputc('\n', stderr);
	va_end(arguments);
	
	error_count++;
}
//}}}
//{{{
void fatal(const char *fmt, ...)
{
	va_list arguments;
	va_start(arguments, fmt);
		vfprintf(stderr, fmt, arguments);
	va_end(arguments);
	exit(1);
}
//}}}

//{{{
void check_endianness(void)
{
	short word = 0x0201;
	long longword = 0x04030201;
	char *testptr;
	
	// Check endianness on a word
	testptr = (char*)(&word);
	if(*testptr == 0x01) // Least-significant byte is first (little endian)
		host_endianness = ENDIAN_LITTLE;
	else if(*testptr == 0x02) // MSB is first (big endian)
		host_endianness = ENDIAN_BIG;
	else
		fatal("Host endianness check failed.");
	
	// Now check it on a long, for sanity's sake, so middle-endian systems
	// can be detected and yelled at.
	testptr = (char*)(&longword);
	while(*testptr == 0) // If a long is bigger than 4 bytes, there might be
		testptr++;       // some leading zeroes introduced
	switch(*testptr) {
		case 0x01: // LSB first would mean little endian
			if(host_endianness != ENDIAN_LITTLE)
				fatal("Endianness on this machine is weird (middle endian?)");
			break;
		case 0x04:
			if(host_endianness != ENDIAN_BIG)
				fatal("Endianness on this machine is weird (middle endian?)");
			break;
		case 0x02:
		case 0x03:
			fatal("Endianness on this machine is weird (middle endian?)");
			break;
	}
}
//}}}
//{{{
static inline void byteswap(char *data, int length)
{
	char *head = data,
	     *tail = data+length-1;
	char tmp;
	length >>= 1;
	do {
		tmp = *head;
		*head = *tail;
		*tail = tmp;
		head++;
		tail--;
	} while(--length);
}
//}}}
//{{{
short htots(short S)
{
	if(host_endianness != target_endianness)
		byteswap((char*)&S, sizeof(short));
	return S;
}
//}}}
//{{{
long htotl(long L)
{
	if(host_endianness != target_endianness) {
		byteswap((char*)&L, sizeof(long));
	}
	return L;
}
//}}}
//{{{
long round_up(long A, long V)
{
	long addition = A - V%A;
	if(addition == A)
		return V;
	else
		return V+addition;
}
//}}}

//{{{
void fill_word(unsigned char *data, unsigned short val)
{
	if(target_endianness == ENDIAN_BIG) {
		data[0] = (val>>8);
		data[1] = (val);
	} else {
		data[0] = (val);
		data[1] = (val>>8);
	}
}
//}}}
//{{{
void fill_long(unsigned char *data, unsigned long val)
{
	if(target_endianness == ENDIAN_BIG) {
		data[0] = (val>>24);
		data[1] = (val>>16);
		data[2] = (val>>8);
		data[3] = (val);
	} else {
		data[0] = (val);
		data[1] = (val>>8);
		data[2] = (val>>16);
		data[3] = (val>>24);
	}
}
//}}}

//{{{
FILE *open_output_filename(const char *filename)
{
	FILE *file;
	
	if(filename) {
		file = fopen(filename, "wb");
		if(!file) {
			error("Couldn't open output file %s: %s.", filename,
			                                           strerror(errno));
			return NULL;
		}
		return file;
	} else {
		return stdout;
	}
}
//}}}

//{{{
/// @brief Print into a string, and return its address.
///
/// @note Return is invalidated by the next call. If you want to still use
/// it after calling retprintf again, you must save a copy.
/// @sa vretprintf
const char *retprintf(const char *format, ...)
{
	va_list varargs;
	const char *ret;
	va_start(varargs, format);
	ret = vretprintf(format, varargs);
	va_end(varargs);
	return ret;
}
//}}}
//{{{
/// @brief Print into a string, and return its address, with a va_list.
/// @sa retprintf
const char *vretprintf(const char *format, va_list args)
{
	static char buf[512];
	vsnprintf(buf, 512, format, args);
	return buf;
}
//}}}

//{{{
char *strnfill(char *DST, const char *STR, unsigned LEN)
{
	unsigned ii;
	for(ii=0; ii<LEN; ii++) {
		if(!STR[ii]) break;
		DST[ii] = STR[ii];
	}
	for(; ii<LEN; ii++) {
		DST[ii] = '\0';
	}
	return DST;
}
//}}}
