CC=g++
CPPFLAGS=-std=c++20 -Wall -Wextra -Werror
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
	./$(OUT) $(FILE) --info

audit: compile
	@./$(OUT) --audit