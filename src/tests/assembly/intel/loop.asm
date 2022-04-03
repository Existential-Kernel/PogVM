main:                                   # @main
        push    rax
        mov     edi, offset .L.str
        mov     esi, 11
        xor     eax, eax
        call    printf
        mov     edi, offset .L.str
        mov     esi, 22
        xor     eax, eax
        call    printf
        mov     edi, offset .L.str
        mov     esi, 33
        xor     eax, eax
        call    printf
        mov     edi, offset .L.str
        mov     esi, 44
        xor     eax, eax
        call    printf
        xor     eax, eax
        pop     rcx
        ret
.L.str:
        .asciz  "%d\n"

.Ldebug_list_header_start0:
        .short  5                               # Version
        .byte   8                               # Address size
        .byte   0                               # Segment selector size
        .long   1                               # Offset entry count
        .long   .Ldebug_loc0-.Lloclists_table_base0
        .byte   4                               # DW_LLE_offset_pair
        .byte   3                               # Loc expr size
        .byte   17                              # DW_OP_consts
        .byte   0                               # 0
        .byte   159                             # DW_OP_stack_value
        .byte   4                               # DW_LLE_offset_pair
        .byte   3                               # Loc expr size
        .byte   17                              # DW_OP_consts
        .byte   1                               # 1
        .byte   159                             # DW_OP_stack_value
        .byte   4                               # DW_LLE_offset_pair
        .byte   3                               # Loc expr size
        .byte   17                              # DW_OP_consts
        .byte   2                               # 2
        .byte   159                             # DW_OP_stack_value
        .byte   4                               # DW_LLE_offset_pair
        .byte   3                               # Loc expr size
        .byte   17                              # DW_OP_consts
        .byte   3                               # 3
        .byte   159                             # DW_OP_stack_value
        .byte   4                               # DW_LLE_offset_pair
        .byte   3                               # Loc expr size
        .byte   17                              # DW_OP_consts
        .byte   4                               # 4
        .byte   159                             # DW_OP_stack_value
        .byte   0                               # DW_LLE_end_of_list
.Ldebug_list_header_end0: