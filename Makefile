CC=g++
OUT=pogvm
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror -pedantic -pedantic-errors
EXTRACPPFLAG=-time -B ./src -pthread -ffunction-sections -fdata-sections -Ofast -ftree-vectorize -flto
FILE=./src/tests/elf/helloworld
VMFLAG=--compiled

.PHONY: all clearscr clear compile run audit


all: clearscr debug

clearscr:
	@clear

clear:
	@rm -rf $(OUT)

compile:
	@$(CC) $(CPPFLAGS) $(EXTRACPPFLAGS) src/mainframe.cpp -o $(OUT)

debug: clear
	@$(CC) $(CPPFLAGS) -Og -g src/mainframe.cpp -o $(OUT)
	./$(OUT) $(FILE)

run: clear compile
	./$(OUT)

elf:
	readelf -$(VMFLAG) ./src/tests/elf/helloworld