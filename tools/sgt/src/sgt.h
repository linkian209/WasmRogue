#ifndef SGT_H
#define SGT_H

#include <stdio.h>

#ifdef __cplusplus__
extern "C" {
#endif

int sgt_filter(FILE *in, FILE *out, const char *keyword);
int sgt_rewrite(const char *filename, const char *keyword);

int have_translation(const char *key);
const char *get_translation(const char *key);

int gettext_open(const char *filename);
void gettext_cleanup(void);
const char *static_gettext(const char *key);

int error(const char *format, ...);
char parse_escape(const char *str, int *pos);
void skip_whitespace(FILE *F);
int skip_comment(FILE *F);
int isident(int C);
int match_str(const char *str1, const char *expected);
const char *strip_path(const char *str);
const char *stem(const char *str);

#ifdef __cplusplus__
}
#endif

#endif

