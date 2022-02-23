all: compile run

compile: 
	g++ -Wall -Wextra -Werror src/mainframe.cpp src/CPU/registers.hpp src/audit.hpp -o src/PogCPU

run:
	@./src/PogCPU