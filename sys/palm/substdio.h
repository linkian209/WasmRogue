// Substandard I/O
//
// stdio.h replacement/wrapper, since some target platforms have I/O not quite
// rising to the level of "standard".
//
// For platforms with working stdio, this should just include it. For other
// platforms, this should prototype a custom implementation.
#ifndef SUBSTDIO_H
#define SUBSTDIO_H

#include <PalmOS.h>
#include <stdarg.h>

#ifndef SEG
#define SEG(n) __attribute__((section("sec_" #n)))
#endif

typedef struct
{
	FileHand handle;
} FILE;

#ifndef __size_t__
#define __size_t__
typedef unsigned long size_t;
#endif

// None of this stuff works (it's all stubs), but at least it compiles
FILE *fopen(const char *name, const char *mode) SEG(3);
int fclose(FILE *FP) SEG(3);
size_t fread(void *BUF, size_t SIZE, size_t COUNT, FILE *FP) SEG(3);
size_t fwrite(void *BUF, size_t SIZE, size_t COUNT, FILE *FP) SEG(3);
int feof(FILE *FP) SEG(3);
int fgetc(FILE *FP) SEG(3);
int fputc(int CH, FILE *FP) SEG(3);
#define getc(fp) fgetc(fp)
#define putc(ch,fp) fputc(ch,fp)

#define sprintf StrPrintF
#define vsprintf StrVPrintF

int remove(const char *pathname) SEG(3);
int rename(const char *OLD, const char *NEW) SEG(3);
int fseek(FILE *FP, long distance, int whence) SEG(3);
#define SEEK_SET fileOriginBeginning
#define SEEK_END fileOriginEnd
#define SEEK_CUR fileOriginCurrent
void rewind(FILE *FP) SEG(3);


#endif

