all : huffman huffman_compress huffman_decompress

huffman : huffman.c huffman.h
	gcc huffman.c -o huffman -Wall -O

huffman_compress : huffman_encode.c huffman_compress.c huffman.h hufftable.h
	gcc huffman_encode.c huffman_compress.c -o huffman_compress -Wall -O

huffman_decompress : huffman_encode.c huffman_decompress.c huffman.h hufftable.h
	gcc huffman_encode.c huffman_decompress.c -o huffman_decompress -Wall -O

clean :
	rm -f *.exe

