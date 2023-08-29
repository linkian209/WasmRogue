
#define reverse_char_constant(c) \
  (((c&0x000000FF)<<24) | ((c&0x0000FF00)<<16) \
 | ((c&0x00FF0000)<<8)  | ((c&0xFF000000)))

#ifdef BACKWARDS_CHAR_CONSTANTS
#	define CHARCONST(c) reverse_char_constant(c)
#else
#	define CHARCONST(c) c
#endif


int main()
{
	long CCON = '1234';
	char *foo = (char*)(&CCON);
	if(*foo == '1') return 0;
	else if(*foo == '4') return 1;
	else
	{ // Middle-endian system?
		return 0;
	}
	return 0;
}
