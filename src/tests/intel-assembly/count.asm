main:
        push    rbx
        xor     ebx, ebx
.LBB0_1:
        mov     edi, offset .L.str
        mov     esi, ebx
        xor     eax, eax
        call    printf
        inc     ebx
        cmp     ebx, 101
        jne     .LBB0_1
        xor     eax, eax
        pop     rbx
        ret
.L.str:
        .asciz  "%d\n"