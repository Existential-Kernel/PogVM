CC=g++
CPPFLAGS=-Wall -Wextra -Werror

.PHONY: all clear compile run audit


all: clearscr compile run

clearscr:
	@clear

clear:
	rm -rf *.o

compile:
	@$(CC) $(CPPFLAGS) src/mainframe.cpp -o PogCPU

run:
	@./PogCPU

audit: compile
	@./PogCPU --audit