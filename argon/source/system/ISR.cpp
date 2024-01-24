#include "system/ISR.hpp"

#include "Panic.hpp"

void isr::install(IDT& idt) noexcept
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
    asm ("cli");
    panic("divide by zero");
    asm ("hlt");
}

void isr::_1()
{
    asm ("cli");
    panic("debug error");
    asm ("hlt");
}

void isr::_2()
{
    asm ("cli");
    panic("nmi interrupt");
    asm ("hlt");
}

void isr::_3()
{
    asm ("cli");
    panic("breakpoint");
    asm ("hlt");
}

void isr::_4()
{
    asm ("cli");
    panic("overflow");
    asm ("hlt");
}

void isr::_5()
{
    asm ("cli");
    panic("bound range exceeded");
    asm ("hlt");
}

void isr::_6()
{
    asm ("cli");
    panic("invalid opcode exception");
    asm ("hlt");
}

void isr::_7()
{
    asm ("cli");
    panic("device not available exception");
    asm ("hlt");
}

void isr::_8()
{
    asm ("cli");
    panic("Double Fault Exception");
    asm ("hlt");
}

void isr::_9()
{
    asm ("cli");
    panic("coprocessor segment overrun");
    asm ("hlt");
}

void isr::_10()
{
    asm ("cli");
    panic("invalid tss exception");
    asm ("hlt");
}

void isr::_11()
{
    asm ("cli");
    panic("segment not present");
    asm ("hlt");
}

void isr::_12()
{
    asm ("cli");
    panic("stack fault exception");
    asm ("hlt");
}

void isr::_13()
{
    asm ("cli");
    panic("general protection exception");
    asm ("hlt");
}

void isr::_14()
{
    asm ("cli");
    panic("page fault exception");
    asm ("hlt");
}

void isr::_16()
{
    asm ("cli");
    panic("fpu float-point error");
    asm ("hlt");
}

void isr::_17()
{
    asm ("cli");
    panic("alignment check exception");
    asm ("hlt");
}

void isr::_18()
{
    asm ("cli");
    panic("machine-check exception");
    asm ("hlt");
}

void isr::_19()
{
    asm ("cli");
    panic("simd floating-point exception");
    asm ("hlt");
}

void isr::_20()
{
    asm ("cli");
    panic("virtualization exception");
    asm ("hlt");
}

void isr::_21()
{
    asm ("cli");
    panic("control protection exception");
    asm ("hlt");
}

