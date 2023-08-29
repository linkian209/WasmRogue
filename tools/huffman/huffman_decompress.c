#include <stdio.h>
#include <string.h>
#include "huffman.h"

void huffify(const char *filename)
{
	char filename_out[256];
	FILE *fin = fopen(filename, "rb");
	FILE *fout;
	unsigned i=0;
	
	if(!fin)
	{
		fprintf(stderr, "Couldn't open input file: %s.\n", filename);
		return;
	}
	
	strcpy(filename_out, filename);
	strcat(filename_out, ".unhuff");
	fout = fopen(filename_out, "wb");
	if(!fout)
	{
		fprintf(stderr, "Couldn't open output file: %s.\n", filename_out);
		return;
	}
	
	printf("Decompressing %s into %s.\n", filename, filename_out);
	
	fhuffmaninit_read();
	while(!feof(fin))
	{
		fputc(fhuffmangetc(fin), fout);
		i++;
	}
	printf("Wrote %i bytes.\n", i);
	fclose(fout);
}

int main(int argc, char **argv)
{
	int i;
	
	// Compress files
	for(i=1; i<argc; i++)
		huffify(argv[i]);
	
	return 0;
}
