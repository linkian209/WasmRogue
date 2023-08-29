CC   := gcc
LD   := gcc
YACC ?= yacc
LEX  ?= lex
Q    ?= @
echo ?= @echo
DEL  ?= rm -f


CFILES=src/main.c src/namespace.c src/util.c src/hir.c src/type.c \
       src/hir_print.c src/hir_reduce.c src/hir_pointers.c src/hir_constant.c \
	   src/hir_struct.c src/lir.c src/lir_assemble.c opt/lir_dead_tail.c \
	   opt/lir_constant_size.c
HFILES=include/compile.h include/namespace.h include/util.h include/hir.h \
       include/lir.h include/type.h include/hir_struct.h
YFILE=src/compile.y
LFILE=src/compile.l
CCOPTS=-Wall -O2 -Iinclude -c
CCOPTS_NOWARN=-O2 -Iinclude -c
OBJECTS=$(foreach file, $(CFILES), $(basename $(notdir $(file))).o)

vpath %.c src opt
vpath %.h include

#mkdat: lex.yy.c y.tab.c $(CFILES) $(HFILES)
#	$(echo) "  CC " $^
#	$(Q)$(CC) $(CCOPTS) lex.yy.c y.tab.c $(CFILES) -o mkdat

mkdat: lex.yy.o y.tab.o $(OBJECTS)
	$(echo) "  LD " $@
	$(Q)$(LD) -o $@ $^

lex.yy.o: lex.yy.c
	$(echo) "  CC " $<
	$(Q)$(CC) $(CCOPTS_NOWARN) $< -o $@
y.tab.o: y.tab.c
	$(echo) "  CC " $<
	$(Q)$(CC) $(CCOPTS_NOWARN) $< -o $@
%.o: %.c $(HFILES)
	$(echo) "  CC " $<
	$(Q)$(CC) -o $@ $(CCOPTS) $<

lex.yy.c : $(LFILE)
	$(LEX) $(LFILE)

y.tab.c : $(YFILE)
	$(YACC) -d $(YFILE)

clean:
	$(Q)$(DEL) mkdat.exe mkdat *.o

tidy: clean

