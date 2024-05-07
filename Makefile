CC=gcc
CFLAGS=-Wall -std=c11 -Iinclude
OBJDIR=bin
SRCDIR=src

# Chess_V1.0 directory and contents
USERDIR = ../Chess_V1.0
USER_TAR_CONTENTS = $(USERDIR)/README.md $(USERDIR)/COPYRIGHT $(USERDIR)/INSTALL.md $(USERDIR)/bin/ $(USERDIR)/doc/

# Chess_V1.0_src directory
DEVDIR = ../Chess_V1.0_src
DEV_TAR_CONTENTS = $(DEVDIR)/README.md $(DEVDIR)/COPYRIGHT $(DEVDIR)/INSTALL.md $(DEVDIR)/bin/ $(DEVDIR)/doc/ $(DEVDIR)/src/ $(DEVDIR)/Makefile

OBJ=$(SRCDIR)/main.o $(SRCDIR)/chess.o $(SRCDIR)/chess_ai.o $(SRCDIR)/log.o $(SRCDIR)/evalhelper.o $(SRCDIR)/evaluate.o $(SRCDIR)/midgame.o $(SRCDIR)/boardControl.o $(SRCDIR)/earlygame.o $(SRCDIR)/endgame.o $(SRCDIR)/GUI.o $(SRCDIR)/game.o

# Target to create the chess program
chess_program: $(OBJ)
	$(CC) $(CFLAGS) -o $(OBJDIR)/chess_program $(OBJ) -lSDL
	./$(OBJDIR)/chess_program

all: chess_program

# Test targets
test_rulecheck.o: $(SRCDIR)/test_rulecheck.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/test_rulecheck.c -o $(SRCDIR)/test_rulecheck.o

test_boarddisplay.o: $(SRCDIR)/test_boarddisplay.c
	$(CC) $(CFLAGS) -c $(SRCDIR)/test_boarddisplay.c -o $(SRCDIR)/test_boarddisplay.o

testBoard: test_boarddisplay.o
	$(CC) $(CFLAGS) -o $(SRCDIR)/testBoard $(SRCDIR)/test_boarddisplay.o
	./$(SRCDIR)/testBoard

testRule: test_rulecheck.o
	$(CC) $(CFLAGS) -o $(SRCDIR)/testRule $(SRCDIR)/test_rulecheck.o
	./$(SRCDIR)/testRule

test: testBoard testRule

tar:
	tar cvzf Chess_V1.0.tar.gz $(USER_TAR_CONTENTS)
	tar cvzf Chess_V1.0_src.tar.gz $(DEV_TAR_CONTENTS)
	
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean the build directory
clean:
	rm -f $(SRCDIR)/*.o $(OBJDIR)/chess_program $(SRCDIR)/testBoard $(SRCDIR)/testRule

# Phony targets
.PHONY: clean all