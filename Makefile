CC=g++
CPPFLAGS=-O3 -std=c++20 -Wall -Wextra -Werror -pedantic -pedantic-errors
FILE=./src/tests/elf/helloworld
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
	./$(OUT) --$(FLAG) $(FILE)

flagrun: compile
	@./$(OUT) -$(FLAG)