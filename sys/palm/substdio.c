#include "crogue.h"

//{{{
FILE *fopen(const char *name, const char *mode)
{
	Err err;
	FILE *ret = debug_malloc(sizeof(FILE));
	long parsed_mode = 0;
	
	while(*mode != '\0')
	{
		switch(*mode) {
			case 'r': parsed_mode = fileModeReadOnly; break;
			case 'w': parsed_mode = fileModeReadWrite; break;
			case 'a': parsed_mode = fileModeAppend; break;
			case '+': parsed_mode = fileModeUpdate; break;
		}
		mode++;
	}
	
	ret->handle = FileOpen(0, name, 0, 0, parsed_mode, &err);
	if(err) {
		free(ret);
		return NULL;
	}
	return ret;
}
//}}}
//{{{
int fclose(FILE *FP)
{
	Err e;
	
	if(!FP) return EOF;
	
	e = FileClose(FP->handle);
	free(FP);
	
	if(e) return EOF;
	return 0;
}
//}}}
//{{{
size_t fread(void *BUF, size_t SIZE, size_t COUNT, FILE *FP)
{
	return FileRead(FP->handle, BUF, SIZE, COUNT, NULL);
}
//}}}
//{{{
size_t fwrite(void *BUF, size_t SIZE, size_t COUNT, FILE *FP)
{
	return FileWrite(FP->handle, BUF, SIZE, COUNT, NULL);
}
//}}}
//{{{
int feof(FILE *FP)
{
	Err e = FileEOF(FP->handle);
	if(e == fileErrEOF) return 1;
	else return 0;
}
//}}}
//{{{
int fgetc(FILE *FP)
{
	unsigned char ch;
	if(fread((void*)&ch, 1, 1, FP)) {
		return ch;
	} else {
		return EOF;
	}
}
//}}}
//{{{
int fputc(int CH, FILE *FP)
{
	char ch = CH;
	if(fwrite(&ch, 1, 1, FP))
		return CH;
	else
		return EOF;
}
//}}}
//{{{
int fseek(FILE *FP, long offset, int whence)
{
	if(FileSeek(FP->handle, offset, whence))
	     return EOF;
	else return 0;
}
//}}}
//{{{
void rewind(FILE *FP)
{
	FileRewind(FP->handle);
}
//}}}
//{{{
int remove(const char *pathname)
{
	if(FileDelete(0, pathname))
	     return -1;
	else return 0;
}
//}}}
//{{{
int rename(const char *OLD, const char *NEW)
{
	LocalID dbID = DmFindDatabase(0, OLD);
	
	if(dbID == 0) return -1;
	
	if(DmSetDatabaseInfo(0, dbID, NEW,
	   NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL) != errNone)
		return -1;
	
	return 0;
}
//}}}

