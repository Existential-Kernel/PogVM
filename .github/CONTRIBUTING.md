- If you want to add an instruction, make sure to do it with this syntax:
```
/*
 * Instruction: <instruction name>
 * Description: <description>
 * Opcode:      <opcode(s)>
 */

 #include <necessary header(s)>

 <add the instruction function here>
 ```
 `Note:` The opcode should be in all uppercase letters, do not write lowercase letters for the hex value. If there are multiple opcodes in the instruction, make sure to seperate them with a space and a comma, or write them as a sequence with `...`. Ex: `0xC2, 0xC3, 0x08...0x0D`. Also, I left a few useful resources for creating x86 assembly instructions in `docs/Resources.md`

