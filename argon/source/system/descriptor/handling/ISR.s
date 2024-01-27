.section .note.GNU-stack

.section .text

.macro make_isr index
    .global isr_\index
    .type isr_\index, @function
    isr_\index:
        cli
        push $0
        push $\index
        jmp handle_panicking_interrupt_stub
.endm

make_isr 0
make_isr 1
make_isr 2
make_isr 3
make_isr 4
make_isr 5
make_isr 6
make_isr 7
make_isr 8
make_isr 9
make_isr 10
make_isr 11
make_isr 12
make_isr 13
make_isr 14
make_isr 15
make_isr 16
make_isr 17
make_isr 18
make_isr 19
make_isr 20

handle_panicking_interrupt_stub:
    pusha

    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10 , %ax
    mov %ax   , %ds
    mov %ax   , %es
    mov %ax   , %fs
    mov %ax   , %gs
    mov %esp  , %eax

    push %eax
    call handle_panicking_interrupt
    pop %eax

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

    add $8, %esp

    iret
