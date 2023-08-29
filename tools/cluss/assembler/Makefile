PROJECT=cluss_asm
SOURCES := $(wildcard src/*.c)
OBJECTS := $(foreach file, $(SOURCES), $(basename $(notdir $(file))).o)
INCLUDEPATH := -Iinclude
Q  ?= @
echo ?= @echo
CC ?= gcc
CCOPTS = -O2 -Wall -Iinclude -g -c
LD := $(CC)
CPROTO=cproto
vpath %.c src

$(PROJECT): $(OBJECTS)
	$(echo) "  LD " $^
	$(Q)$(LD) -o $@ $^

%.o: %.c
	$(echo) "  CC " $^
	$(Q)$(CC) $(CCOPTS) -o $@ $^

clean:
	$(Q)rm -f *.o *.exe
tidy: clean

proto: include/proto.h
include/proto.h: $(SOURCES)
	$(echo) "cproto " $^
	$(Q)$(CPROTO) $(INCLUDEPATH) -DCPROTO -o include/proto.h $(SOURCES)

