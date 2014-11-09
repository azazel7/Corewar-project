SRCDIR=src
OBJDIR=obj
INCDIR=include
MAINDIR=$(SRCDIR)/main

CC=gcc
SRC = $(shell find $(SRCDIR) -name "*.c" | grep -v  "$(MAINDIR)")
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
OBJSUBDIR = $(dir $(OBJ))
DEBUGFLAG=-O2 -Os
LINK=-lcurses -lm
OPTION=-std=c99
WARNINGFLAG=

ifeq ($(CLANG),1)
CC=clang
endif

ifeq ($(DEBUG),1)
DEBUGFLAG=-g3 -O0 -pg
endif

ifeq ($(WARNING),1)
WARNINGFLAG=-Wall -Wextra
endif

corewar: compile
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)/main.c -o $@ $(LINK) $(DEBUGFLAG) $(WARNINGFLAG)

test: compile
	$(CC) $(OPTION) -I $(INCDIR)  $(OBJ) $(MAINDIR)/tigre.c -o $@ $(LINK) $(DEBUGFLAG) $(WARNINGFLAG)
	./test

compile: directory $(OBJ)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(OPTION) -I $(INCDIR) -c $< -o $@ $(DEBUGFLAG) $(WARNINGFLAG)

directory:
	@mkdir -p $(OBJSUBDIR) 1>/dev/null 2>&1 || ls >/dev/null 2>&1

clean:
	rm -rf $(OBJDIR)

rebuild: clean compile
