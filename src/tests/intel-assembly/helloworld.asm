main:                                   # @main
        push    rax
        mov     edi, offset .L.str
        mov     esi, offset .L.str.1
        xor     eax, eax
        call    printf
        xor     eax, eax
        pop     rcx
        ret
.L.str:
        .asciz  "%s"

.L.str.1:
        .asciz  "hello world!"