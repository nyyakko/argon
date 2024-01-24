#include "system/ISR.hpp"

#include "Panic.hpp"

void isr::install(IDT& idt)
{
    idt.set_entry(0, isr::_0, 0x8E);
    idt.set_entry(1, isr::_1, 0x8E);
    idt.set_entry(2, isr::_2, 0x8E);
    idt.set_entry(3, isr::_3, 0x8E);
    idt.set_entry(4, isr::_4, 0x8E);
    idt.set_entry(5, isr::_5, 0x8E);
    idt.set_entry(6, isr::_6, 0x8E);
    idt.set_entry(7, isr::_7, 0x8E);
    idt.set_entry(8, isr::_8, 0x8E);
    idt.set_entry(9, isr::_9, 0x8E);
    idt.set_entry(10, isr::_10, 0x8E);
    idt.set_entry(11, isr::_11, 0x8E);
    idt.set_entry(12, isr::_12, 0x8E);
    idt.set_entry(13, isr::_13, 0x8E);
    idt.set_entry(14, isr::_14, 0x8E);
    idt.set_entry(15, interrupt_generic, 0x8E);
    idt.set_entry(16, isr::_16, 0x8E);
    idt.set_entry(17, isr::_17, 0x8E);
    idt.set_entry(18, isr::_18, 0x8E);
    idt.set_entry(19, isr::_19, 0x8E);
    idt.set_entry(20, isr::_20, 0x8E);
    idt.set_entry(21, isr::_21, 0x8E);
}

void isr::_0()
{
    panic("divide by zero");
}

void isr::_1()
{
    panic("debug error");
}

void isr::_2()
{
    panic("nmi interrupt");
}

void isr::_3()
{
    panic("breakpoint");
}

void isr::_4()
{
    panic("overflow");
}

void isr::_5()
{
    panic("bound range exceeded");
}

void isr::_6()
{
    panic("invalid opcode exception");
}

void isr::_7()
{
    panic("device not available exception");
}

void isr::_8()
{
    panic("Double Fault Exception");
}

void isr::_9()
{
    panic("coprocessor segment overrun");
}

void isr::_10()
{
    panic("invalid tss exception");
}

void isr::_11()
{
    panic("segment not present");
}

void isr::_12()
{
    panic("stack fault exception");
}

void isr::_13()
{
    panic("general protection exception");
}

void isr::_14()
{
    panic("page fault exception");
}

void isr::_16()
{
    panic("fpu float-point error");
}

void isr::_17()
{
    panic("alignment check exception");
}

void isr::_18()
{
    panic("machine-check exception");
}

void isr::_19()
{
    panic("simd floating-point exception");
}

void isr::_20()
{
    panic("virtualization exception");
}

void isr::_21()
{
    panic("control protection exception");
}

