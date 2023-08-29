#ifndef TICALC_H
#define TICALC_H

//{{{
typedef struct ticalc_header {
	char           signature[8]; // "**TI92P*" or "**TI89**"
	unsigned char  fill1[2];     // 01 00
	char           folder[8];    // folder name
	char           desc[40];     // ---- not used ----
	unsigned short numvars;     // 1
	unsigned char  fill2[4];     // 52 00 00 00 Address of first data byte
	char           name[8];      // varname
	unsigned char  type[4];      // 0C 00 00 00
	unsigned long  size;         // complete file size (including checksum)
	unsigned char  fill3[6];     // A5 5A 00 00 00 00
	unsigned short datasize;     // data size
} ticalc_header;
//}}}

extern const ticalc_header default_header;

#endif

