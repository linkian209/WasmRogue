PROJECT=mki

CXX    := g++
CXXOPT := -O2 -Wall -Iinclude
LD     := g++
LIBS   :=

LDOPT  += -o $(PROJECT)
LDOPT  += $(addprefix -l, $(LIBS))

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(foreach file, $(basename $(notdir $(SOURCES))), obj/$(file).o)

CMD = @echo
Q = @

$(PROJECT): $(OBJECTS)
	$(CMD) "  LD  " $^
	$(Q) $(LD) $(LDOPT) $(OBJECTS)

obj/%.o : src/*.cpp
	$(CMD) "  Cxx " $<
	$(Q) $(CXX) $(CXXOPT) -o $@ -c $<

clean:
	$(Q) rm -f obj/*.o *.exe

