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
	strcat(filename_out, ".huff");
	fout = fopen(filename_out, "wb");
	if(!fout)
	{
		fprintf(stderr, "Couldn't open output file: %s.\n", filename_out);
		return;
	}
	
	printf("Copmressing %s into %s.\n", filename, filename_out);
	
	fhuffmaninit_write();
	while(!feof(fin))
	{
		fhuffmanputc(getc(fin), fout);
		i++;
	}
	fhuffmanflush(fout);
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
