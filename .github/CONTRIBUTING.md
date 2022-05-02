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

 `Tip:` You could use [this](https://en.wikipedia.org/wiki/X86_instruction_listings#Added_with_80186/80188) wikipedia article if you want the full list of instructions, If you're going to add any instruction, I think this would be immensely useful. Also, there are other really good x86 instruction listings, so here's a list of really detailed ones I've found:
    - https://www.felixcloutier.com/x86/
    - http://ref.x86asm.net/geek64.html
    - http://www.mathemainzel.info/files/x86asmref.html
    - http://www.c-jump.com/CIS77/CPU/x86/lecture.html