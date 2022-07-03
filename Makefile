CC=g++
OUT=pogvm
MAIN=src/mainframe.cpp
CPPFLAGS=-std=c++20 -w -Wall -Wextra -Werror -Wshadow -Wpedantic -pedantic -pedantic-errors
EXTRACPPFLAGS=-time -B ./src -pthread -ffunction-sections -fdata-sections -Ofast -ftree-vectorize -flto
FILE=./src/tests/elf/helloworld
VMFLAG=--compiled

.PHONY: all clearscr clear compile run audit


all: clearscr exec

clearscr:
	@clear

clear:
	@rm -rf $(OUT)

exec: debug
	./$(OUT) $(FILE)

release:
	@$(CC) $(CPPFLAGS) $(EXTRACPPFLAGS) $(MAIN) -o $(OUT)

debug: clear
	@$(CC) $(CPPFLAGS) $(MAIN) -o $(OUT)

run: clear compile
	./$(OUT)

elf:
	readelf -i $(FILE)