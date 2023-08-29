#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rle.h"

void panic(const char *fmt, ...)
{
	exit(1);
}

typedef struct tile
{
	char t;
//	char rep[63];
	unsigned char rep;
} tile;

void put_ascii(unsigned char c, FILE *f)
{
	fprintf(f, "uchar: %3i; ", (int)c);
}


int main(int argc, char **argv)
{
	FILE *tilefile;
	int data_start = 1;
	tile tiles[128];
	char inbuf[256];
	int i, j, k;
	int numTiles=0;
	int tilerep;
	
	for(i=1; i<argc; i++)
	{
		if(!strcmp(argv[i], "-d"))
			data_start = i+1;
		else if(!strcmp(argv[i], "-h"))
		{
			printf("Usage: fixedmap -d data\n\n");
			return 1;
		}
	}
	
	tilefile = fopen("auto/tiles.dat", "r");
	if(!tilefile) {
		tilefile = fopen("tiles.dat", "r");
		if(!tilefile)
			return 1;
	}
	
	while(!feof(tilefile))
	{
		fgets(inbuf, 256, tilefile);
		sscanf(inbuf, "%c %i", &tiles[numTiles].t, &tilerep);
		tiles[numTiles].rep = tilerep;
		numTiles++;
	}
	
	fclose(tilefile);
	
	frleinit_write_nochecksum(put_ascii);
	
	for(i=data_start; i<argc; i++)
	{
		for(j=0; argv[i][j]; j++)
		{
			for(k=0; k<numTiles; k++)
			{
				if(tiles[k].t == argv[i][j])
				{
					frleputc(tiles[k].rep, stdout);
					break;
				}
			}
		}
	}
	
	frleflush(stdout);
	
	return 0;
}
