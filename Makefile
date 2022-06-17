CC=g++
OUT=pogvm
MAIN=src/mainframe.cpp
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror -Wshadow -Wpedantic -pedantic -pedantic-errors
EXTRACPPFLAGS=-time -B ./src -pthread -ffunction-sections -fdata-sections -Ofast -ftree-vectorize -flto
FILE=./src/tests/elf/helloworld
VMFLAG=--compiled

.PHONY: all clearscr clear compile run audit


all: clearscr debug

clearscr:
	@clear

clear:
	@rm -rf $(OUT)

compile:
	@$(CC) $(CPPFLAGS) $(EXTRACPPFLAGS) $(MAIN) -o $(OUT)

debug: clear
	@$(CC) $(CPPFLAGS) -Og -g $(MAIN) -o $(OUT)
	./$(OUT) $(FILE)

run: clear compile
	./$(OUT)

elf:
	readelf -i $(FILE)