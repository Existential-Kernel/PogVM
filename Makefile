CC=g++
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror
FILE=./src/tests/intel-assembly/helloworld.asm
OUT=pogvm

.PHONY: all clearscr clear compile run audit


all: clearscr run

clearscr:
	@clear

clear:
	@rm -rf *.o

compile:
	@$(CC) $(CPPFLAGS) src/mainframe.cpp -o $(OUT)

run: compile
	./$(OUT) $(FILE)

audit: compile
	@./$(OUT) --audit