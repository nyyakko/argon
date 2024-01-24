.section .note.GNU-stack

.section .text
.global inb
.type inb, @function
inb:
    push   %ebp
    mov    %esp, %ebp

    push   %eax
    mov    8(%ebp) , %dx
    in     (%dx)   , %al
    mov    %al     , (%eax)
    add    $4      , %esp

    pop %ebp

    ret

.section .text
.global outb
.type out, @function
outb:
    push   %ebp
    mov    %esp, %ebp

    mov    12(%ebp) , %al
    mov    8(%ebp)  , %dx
    out    %al      , (%dx)

    pop    %ebp

    ret

