
CXX=c++
PROGNAME=sgt
SOURCES=src/filter.c src/util.c src/translate.c src/main.cc
HEADERS=src/sgt.h
OBJDIR=.

Q=@

$(PROGNAME): $(SOURCES) $(HEADERS)
	$(CXX) -o $(OBJDIR)/$(PROGNAME) -O2 -g -Wall $(SOURCES)

clean:
	$(Q)rm -f *.o sgt *.exe

