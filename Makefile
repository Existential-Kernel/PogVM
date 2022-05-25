CC=g++
OUT=pogvm
CPPFLAG=-std=c++20 -time -B ./src -Wall -Wextra -Werror -pthread -pedantic -pedantic-errors -ffunction-sections -fdata-sections
FILE=./src/tests/elf/helloworld
VMFLAG=--compiled

.PHONY: all clearscr clear compile run audit


all: clearscr run

clearscr:
	@clear

clear:
	@rm -rf $(OUT)

compile:
	@$(CC) $(CPPFLAGS) -Ofast -ftree-vectorize -flto src/mainframe.cpp -o $(OUT)

debug: clear 
	@$(CC) $(CPPFLAGS) -Og -g src/mainframe.cpp -o $(OUT)

run: clear compile
	./$(OUT)

elf:
	readelf -$(VMFLAG) ./src/tests/elf/helloworld