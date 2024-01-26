.section .note.GNU-stack

.section .text

.macro make_irq index
    .global irq_\index
    .type irq_\index, @function
    irq_\index:
        cli
        push $0
        push $\index
        jmp handle_requested_interrupt_stub
.endm

make_irq 0
make_irq 1
make_irq 2
make_irq 3
make_irq 4
make_irq 5
make_irq 6
make_irq 7
make_irq 8
make_irq 9
make_irq 10
make_irq 11
make_irq 12
make_irq 13
make_irq 14
make_irq 15

handle_requested_interrupt_stub:
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
    call interrupt_handler_dispatcher
    pop %eax

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa

    add $8, %esp

    iret
