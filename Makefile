CC=g++
CPPFLAGS=-Wall -Wextra -Werror

all: compile run

compile: 
	@$(CC) $(CPPFLAGS) src/mainframe.cpp -o src/PogCPU

run:
	@./src/PogCPU

audit:
	@./src/PogCPU --audit