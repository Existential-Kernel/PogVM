CC=g++
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -pedantic-errors
FILE=./src/tests/elf/helloworld
OUT=pogvm

.PHONY: all clearscr clear compile run audit


all: clearscr run

clearscr:
	@clear

clear:
	@rm -rf $(OUT)

compile:
	@$(CC) $(CPPFLAGS) src/mainframe.cpp -o $(OUT)

run: clear compile
	./$(OUT) -i $(FILE)

flag: clear compile
	@./$(OUT) -$(FLAG) $(FILE)

elf:
	readelf -$(OPT) ./src/tests/elf/helloworld