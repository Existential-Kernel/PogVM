CC=g++
OUT=pogvm
MAIN=src/mainframe
AUXFILES=fetch.o decode.o execute.o
CPPFLAGS=-std=c++20 -O3 -w -Wall -Wextra -Werror -Wshadow -Wpedantic -pedantic -pedantic-errors
EXTRACPPFLAGS=-time -B ./src -pthread -ffunction-sections -fdata-sections -Ofast -ftree-vectorize -flto
FILE=./src/tests/elf/helloworld
VMFLAG=--compiled

.PHONY: all clearscr clear compile run audit


all: clearscr exec

clearscr:
	@clear

clear:
	@rm -rf $(OUT)






mainframe.o: src/mainframe.cpp
	$(CC) -c $(CPPFLAGS) $(EXTRACPPFLAGS) src/mainframe.cpp -o mainframe.o

fetch.o: src/cycle/fetch.cpp src/cycle/fetch.hpp
	$(CC) -c $(CPPFLAGS) $(EXTRACPPFLAGS) src/cycle/fetch.cpp -o fetch.o

decode.o: src/cycle/decode.cpp src/cycle/decode.hpp
	$(CC) -c $(CPPFLAGS) $(EXTRACPPFLAGS) src/cycle/decode.cpp -o decode.o

execute.o: src/cycle/execute.cpp src/cycle/execute.hpp
	$(CC) -c $(CPPFLAGS) $(EXTRACPPFLAGS) src/cycle/execute.cpp -o execute.o


obj: mainframe.o fetch.o decode.o execute.o clear
	@$(CC) $(CPPFLAGS) src/mainframe.cpp mainframe.o fetch.o decode.o execute.o -o $(OUT)



exec: debug 
	./$(OUT) $(FILE)

release:
	@$(CC) $(CPPFLAGS) $(EXTRACPPFLAGS) $(MAIN).cpp -o $(OUT)

debug:
	@#src/cycle/fetch.cpp src/cycle/decode.cpp src/cycle/execute.cpp 
	@$(CC) $(CPPFLAGS) $(MAIN).cpp -o $(OUT)

run: clear compile
	./$(OUT)

elf:
	readelf -i $(FILE)