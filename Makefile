CC=g++
CPPFLAGS=-Wall -Wextra -Werror

all: compile run

compile: 
	@$(CC) $(CPPFLAGS) src/mainframe.cpp src/CPU/registers.hpp src/audit.hpp -o src/PogCPU

run:
	@./src/PogCPU

audit:
	@./src/PogCPU --audit