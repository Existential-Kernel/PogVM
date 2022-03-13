CC=g++
CPPFLAGS=-Wall -Wextra -Werror
FILE=./src/cycle/test2.asm

.PHONY: all clear compile run audit


all: clearscr run
#all: clearscr audit

clearscr:
	@clear

clear:
	rm -rf *.o

compile:
	@$(CC) $(CPPFLAGS) src/mainframe.cpp -o PogCPU

run: compile
	@./PogCPU $(FILE)

audit: compile
	@./PogCPU --audit