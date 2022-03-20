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
 `Note:` The opcode should be in all uppercase letters, do not write lowercase letters for the hex value. If there are multiple opcodes in the instruction, make sure to seperate them with a space and a comma, or write them as a sequence with `...`. Ex: `0xC2, 0xC3, 0x08...0x0D`.

 `Tip:` You could use [this](https://en.wikipedia.org/wiki/X86_instruction_listings#Added_with_80186/80188) wikipedia article if you want the full list of instructions, just adding this as I think this would be immensely useful to anybody wanting to contribute to this project.