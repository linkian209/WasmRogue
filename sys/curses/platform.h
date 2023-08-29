#ifndef PLATFORM_H
#define PLATFORM_H

extern int use_color;
void init_colors(void);

#define SCREEN_WIDTH   80
#define SCREEN_HEIGHT  25
extern char *file_prefix; // Path to executable, prepended on filenames

#define get_entropy() time(NULL)

// Stuff in TIGCCLIB which we replace for PC
#define clear_line(a) (move((a),0), clrtoeol())
#define clrscr() clear()
#define clrtiles() erase()
void *malloc_throw(size_t size);
void *calloc_throw(size_t N, size_t S);
void *realloc_throw(void *ptr, size_t size);

#endif

