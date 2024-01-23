#include "system/Exception.hpp"

#include "system/Panic.hpp"

void interrupt_0()
{
    asm ("cli");
    panic("divide by zero");
    asm ("hlt");
}

void interrupt_1()
{
    asm ("cli");
    panic("debug error");
    asm ("hlt");
}

void interrupt_2()
{
    asm ("cli");
    panic("nmi interrupt");
    asm ("hlt");
}

void interrupt_3()
{
    asm ("cli");
    panic("breakpoint");
    asm ("hlt");
}

void interrupt_4()
{
    asm ("cli");
    panic("overflow");
    asm ("hlt");
}

void interrupt_5()
{
    asm ("cli");
    panic("bound range exceeded");
    asm ("hlt");
}

void interrupt_6()
{
    asm ("cli");
    panic("invalid opcode exception");
    asm ("hlt");
}

void interrupt_7()
{
    asm ("cli");
    panic("device not available exception");
    asm ("hlt");
}

void interrupt_8()
{
    asm ("cli");
    panic("Double Fault Exception");
    asm ("hlt");
}

void interrupt_9()
{
    asm ("cli");
    panic("coprocessor segment overrun");
    asm ("hlt");
}

void interrupt_10()
{
    asm ("cli");
    panic("invalid tss exception");
    asm ("hlt");
}

void interrupt_11()
{
    asm ("cli");
    panic("segment not present");
    asm ("hlt");
}

void interrupt_12()
{
    asm ("cli");
    panic("stack fault exception");
    asm ("hlt");
}

void interrupt_13()
{
    asm ("cli");
    panic("general protection exception");
    asm ("hlt");
}

void interrupt_14()
{
    asm ("cli");
    panic("page fault exception");
    asm ("hlt");
}

void interrupt_16()
{
    asm ("cli");
    panic("fpu float-point error");
    asm ("hlt");
}

void interrupt_17()
{
    asm ("cli");
    panic("alignment check exception");
    asm ("hlt");
}

void interrupt_18()
{
    asm ("cli");
    panic("machine-check exception");
    asm ("hlt");
}

void interrupt_19()
{
    asm ("cli");
    panic("simd floating-point exception");
    asm ("hlt");
}

void interrupt_20()
{
    asm ("cli");
    panic("virtualization exception");
    asm ("hlt");
}

void interrupt_21()
{
    asm ("cli");
    panic("control protection exception");
    asm ("hlt");
}

