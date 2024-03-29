.section .note.GNU-stack

.section .text
.global load_gdt
.type load_gdt, @function
load_gdt:
    mov 4(%esp) , %eax
    lgdt (%eax)

    mov $0x10   , %ax
    mov %ax     , %ds
    mov %ax     , %es
    mov %ax     , %fs
    mov %ax     , %gs
    mov %ax     , %ss

    jmp $0x08   , $flush_and_return

flush_and_return:
    ret

