#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "huffman.h"

// Intermediate form for trees (gets converted to tables)
typedef struct huffman_node
{
	short value;
	long freq;
	struct huffman_node *left, *right;
} huffman_node;

void build_tree(huffman_node *pos, long prefix, short length, hufftable *table);
void print_tree(huffman_node *pos, const char *parent_prefix, const char *postfix);

//{{{
huffman_node *make_tree(long *char_frequencies)
{
	int i, j;
	int num_top_nodes = 256;
	int lowest, lowest2, lowest_val;
	huffman_node *nodes[256];
	huffman_node *node_buf;
	
	for(i=0; i<256; i++)
	{
		nodes[i] = (huffman_node*)malloc(sizeof(huffman_node));
		nodes[i]->value = i;
		nodes[i]->freq = char_frequencies[i];
		nodes[i]->left = NULL;
		nodes[i]->right = NULL;
	}
	
	// Do combinations
	do
	{
		lowest = 0;
		lowest_val = LONG_MAX;
		// Find lowest freq
		for(j=0; j<num_top_nodes; j++)
		{
			if(nodes[j]->freq < lowest_val)
			{
				lowest = j;
				lowest_val = nodes[j]->freq;
			}
		}
		
		lowest2 = 0;
		lowest_val = LONG_MAX;
		// Find second-lowest freq
		for(j=0; j<num_top_nodes; j++)
		{
			if(nodes[j]->freq < lowest_val && j != lowest)
			{
				lowest2 = j;
				lowest_val = nodes[j]->freq;
			}
		}
		
		// Set representations
		node_buf = (huffman_node*)malloc(sizeof(huffman_node));
		node_buf->value = 0;
		node_buf->freq = nodes[lowest]->freq + nodes[lowest2]->freq;
		node_buf->left = nodes[lowest];
		node_buf->right = nodes[lowest2];
		
		nodes[lowest] = node_buf;
		nodes[lowest2] = nodes[--num_top_nodes];
	}
	while(num_top_nodes > 1);
	
	return nodes[0];
}
//}}}
//{{{
void make_table(huffman_node *root, hufftable *table)
{
	build_tree(root->left, 0, 1, table);
	build_tree(root->right, 1, 1, table);
}
//}}}
//{{{
int compare_hufftab_entry(const huffdecompresstable_entry *one, const huffdecompresstable_entry *two)
{
	if(one->binrep > two->binrep)
		return 1;
	else if(one->binrep == two->binrep)
		return 0;
	else
		return -1;
}
//}}}
//{{{
void make_decompress_table(hufftable *table, huffdecompresstable *decompress_table)
{
	int i;
	
	for(i=0; i<256; i++)
	{
		decompress_table->entries[i].binrep = table->rep[i] << (16 - table->replen[i]); // Move data to most significant bits
		decompress_table->entries[i].binreplen = table->replen[i];
		decompress_table->entries[i].byterep = i;
	}
	
	qsort(decompress_table, 256, sizeof(huffdecompresstable_entry), &compare_hufftab_entry);
}
//}}}
//{{{
void build_tree(huffman_node *pos, long prefix, short length, hufftable *table)
{
	if(pos->left && pos->right)
	{
		build_tree(pos->left,  prefix<<1, length+1, table);
		build_tree(pos->right, (prefix<<1)|1, length+1, table);
	}
	else
	{
		table->replen[pos->value] = length;
		table->rep[pos->value] = prefix;
	}
}
//}}}
//{{{
void print_tree(huffman_node *pos, const char *parent_prefix, const char *postfix)
{
	char prefix[32];
	strcpy(prefix, parent_prefix);
	strcat(prefix, postfix);
	if(pos->left && pos->right)
	{
		print_tree(pos->left, prefix, "0");
		print_tree(pos->right, prefix, "1");
	}
	else
	{
		printf("%3i(%3li)=%s\n", pos->value, pos->freq, prefix);
	}
}
//}}}
//{{{
void count_frequencies(long *char_frequencies, unsigned char *buf, int length)
{
	int i;
	
	for(i=0; i<256; i++)
		char_frequencies[i] = 0;
	
	for(i=0; i<length; i++)
		char_frequencies[ buf[i] ]++;
	
	for(i=0; i<256; i++) // Don't allow for zero frequencies
		if(char_frequencies[i] == 0)
			char_frequencies[i]++;
}
//}}}
//{{{
void huffify(char *filename)
{
	unsigned char *buf = malloc(65536); // GENERALIZEME
	int size, i;
	long frequencies[256];
	hufftable table;
	huffdecompresstable decompress_table;
	FILE *fin = fopen(filename, "rb");
	FILE *fout;
	huffman_node *hufftree;
	
	size = fread(buf, 1, 65536, fin);
	count_frequencies(frequencies, buf, size);
	hufftree = make_tree(frequencies);
	make_table(hufftree, &table);
	make_decompress_table(&table, &decompress_table);
	
	// Write tables in C header form to file
	fout = fopen("hufftable.h", "w");
	if(fout)
	{
		fprintf(fout, "/* Generated file - Do not edit. */\n"
				"#include \"huffman.h\"\n");
		
		fprintf(fout,
					"const hufftable huff_compress = {\n"
					"\t{\n"
					"\t\t0x%lX", (long)table.rep[0]);
		for(i=1; i<256; i++)
			fprintf(fout, ", 0x%lX", (long)table.rep[i]);
		
		fprintf(fout, "},\n\t{ %i", (int)table.replen[0]);
		for(i=1; i<256; i++)
			fprintf(fout, ", %i", (int)table.replen[i]);
		fprintf(fout, " }\n};\n\n");
		
		fprintf(fout,
					"const huffdecompresstable huff_decompress = {\n"
					"\t{\n"
					"\t\t{0x%X, %i, 0x%X}",
					(int)decompress_table.entries[0].binrep,
					(int)decompress_table.entries[0].binreplen,
					(int)decompress_table.entries[0].byterep);
		for(i=1; i<256; i++)
			fprintf(fout, ",\n\t\t"
				"{0x%X, %i, 0x%X}",
				(int)decompress_table.entries[i].binrep,
				(int)decompress_table.entries[i].binreplen,
				(int)decompress_table.entries[i].byterep);
		fprintf(fout, "\n\t}\n};\n");
		
		fclose(fout);
	}
}
//}}}

//{{{
int main(int argc, char **argv)
{
	int i;
	for(i=1; i<argc; i++)
		huffify(argv[i]);
	
	return 0;
}
//}}}
