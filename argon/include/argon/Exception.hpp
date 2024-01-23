#pragma once

#include "VGA.hpp"
#include "Terminal.hpp"
#include "Panic.hpp"

inline void interrupt_generic()
{
    Terminal::putln("unknown interrupt");
}

inline void interrupt_0()
{
    asm ("cli");
    panic("divide by zero");
    asm ("hlt");
}

inline void interrupt_1()
{
    asm ("cli");
    panic("debug error");
    asm ("hlt");
}

inline void interrupt_2()
{
    asm ("cli");
    panic("nmi interrupt");
    asm ("hlt");
}

inline void interrupt_3()
{
    asm ("cli");
    panic("breakpoint");
    asm ("hlt");
}

inline void interrupt_4()
{
    asm ("cli");
    panic("overflow");
    asm ("hlt");
}

inline void interrupt_5()
{
    asm ("cli");
    panic("bound range exceeded");
    asm ("hlt");
}

inline void interrupt_6()
{
    asm ("cli");
    panic("invalid opcode exception");
    asm ("hlt");
}

inline void interrupt_7()
{
    asm ("cli");

    VGA::clear_buffer();
    panic("device not available exception");

    asm ("hlt");
}

inline void interrupt_8()
{
    asm ("cli");
    panic("Double Fault Exception");
    asm ("hlt");
}

inline void interrupt_9()
{
    asm ("cli");
    panic("coprocessor segment overrun");
    asm ("hlt");
}

inline void interrupt_10()
{
    asm ("cli");
    panic("invalid tss exception");
    asm ("hlt");
}

inline void interrupt_11()
{
    asm ("cli");
    panic("segment not present");
    asm ("hlt");
}

inline void interrupt_12()
{
    asm ("cli");
    panic("stack fault exception");
    asm ("hlt");
}

inline void interrupt_13()
{
    asm ("cli");
    panic("general protection exception");
    asm ("hlt");
}

inline void interrupt_14()
{
    asm ("cli");
    panic("page fault exception");
    asm ("hlt");
}

inline void interrupt_15()
{
    interrupt_generic();
}

inline void interrupt_16()
{
    asm ("cli");
    panic("fpu float-point error");
    asm ("hlt");
}

inline void interrupt_17()
{
    asm ("cli");
    panic("alignment check exception");
    asm ("hlt");
}

inline void interrupt_18()
{
    asm ("cli");
    panic("machine-check exception");
    asm ("hlt");
}

inline void interrupt_19()
{
    asm ("cli");
    panic("simd floating-point exception");
    asm ("hlt");
}

inline void interrupt_20()
{
    asm ("cli");
    panic("virtualization exception");
    asm ("hlt");
}

inline void interrupt_21()
{
    asm ("cli");
    panic("control protection exception");
    asm ("hlt");
}

