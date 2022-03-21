- This directory will focus on the fetch decode execute cycle to run the specific instruction:
    - **Fetch.cpp**: 
        Get the instruction whether it's an assembly mnemonic from an asm file, or an opcode from an executable file while also getting the necessary operands that are designated to the opcode.
    - **Decode.cpp**:
        Convert the assembly mnemonic instruction and arguments into hexadecimal opcodes and operands. If it's already just a hex format, ignore this step.
    - **Execute.cpp**:
        Run the specific instruction based on its opcode hex value. If no such instruction exists, exit the program.
