#Makefile for CPem

PROG = ../build/cpem

# Compiler command
CC = gcc
#CC = gcc -DDEBUG=1 -DDEBUGLOG=1

# Flags to pass to the compiler - add "-g" to include debug information
CFLAGS = -Wall -O3 -fPIC -Wno-unused-variable -Wno-stringop-truncation
#CFLAGS = -Wall -O0 -fPIC -Wno-unused-variable -g

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
	rsync -a ../build/ $(HOME)/idun-base/cpm/

.PHONY: clean
clean:
	$(RM) *.o
	$(RM) $(PROG)
