#Makefile for CPem

PROG = ../build/cpem

# Compiler command
ifdef CROSS
	CC = arm-linux-gnueabihf-gcc
else
	CC = gcc
endif
# Compiler flags
ifdef DEBUG
	CFLAGS = -DDEBUGLOG=1 -Wall -O0 -fPIC -Wno-unused-variable -Wno-stringop-truncation -g
else
	CFLAGS = -Wall -O3 -fPIC -Wno-unused-variable -Wno-stringop-truncation
endif
# Destination for make install
ifndef DESTDIR
	DESTDIR = $(HOME)
endif

# Flags to pass to the linker
LDFLAGS =

# Objects to build
OBJS = main.o

# Clean up program
RM = rm -f

#------------------------------------------------------------------------

all: $(PROG)

$(PROG): main.o
	$(CC) $(OBJS) -o $(PROG) $(LDFLAGS)

main.o: main.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c main.c

rebuild: clean all

install: all
	rsync -a --delete ../build/ $(DESTDIR)/idun-base/cpm/

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) $(PROG)
