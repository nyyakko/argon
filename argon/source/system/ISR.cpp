#include "system/ISR.hpp"

#include "Panic.hpp"

extern "C" void handle_generic_interrupt()
{
    Terminal::putln("unknown interrupt");
}

extern "C" void handle_panicking_interrupt(Registers const* registers)
{
    static constexpr StringView messages[] =
    {
        "DIVIDE BY ZERO"_sv,
        "DEBUG ERROR"_sv,
        "NMI INTERRUPT"_sv,
        "BREAKPOINT"_sv,
        "OVERFLOW"_sv,
        "BOUND RANGE EXCEEDED"_sv,
        "INVALID OPCODE EXCEPTION"_sv,
        "DEVICE NOT AVAILABLE EXCEPTION"_sv,
        "COPROCESSOR SEGMENT OVERRUN"_sv,
        "INVALID TSS EXCEPTION"_sv,
        "SEGMENT NOT PRESENT"_sv,
        "STACK FAULT EXCEPTION"_sv,
        "GENERAL PROTECTION EXCEPTION"_sv,
        "PAGE FAULT EXCEPTION"_sv,
        "FPU FLOAT-POINT ERROR"_sv,
        "", // reserved
        "ALIGNMENT CHECK EXCEPTION"_sv,
        "MACHINE-CHECK EXCEPTION"_sv,
        "SIMD FLOATING-POINT EXCEPTION"_sv,
        "VIRTUALIZATION EXCEPTION"_sv,
        "CONTROL PROTECTION EXCEPTION"_sv
    };

    panic(messages[registers->interruptID]);
}

void isr::install(IDT& idt)
{
// ok. what the actual heck is this.
#define _INTERRUPT_LIST                                                 \
    X(0)  X(1)  X(2)  X(3)  X(4)  X(5)  X(6)                            \
    X(7)  X(8)  X(9)  X(10) X(11) X(12) X(13)                           \
    X(14) X(16) X(17) X(18) X(19) X(20)

#define X(entry)                                                        \
    idt.set_entry(entry, [] () {                                        \
        asm volatile ("pushw $0");                                      \
        asm volatile ("pushw $" #entry);                                \
                                                                        \
        asm volatile ("pusha; push %ds; push %es; push %fs; push %gs"); \
                                                                        \
        asm volatile (                                                  \
            "; mov $0x10, %ax"                                          \
            "; mov %ax, %ds"                                            \
            "; mov %ax, %es"                                            \
            "; mov %ax, %fs"                                            \
            "; mov %ax, %gs"                                            \
                                                                        \
            "; mov %esp, %eax"                                          \
            "; push %eax"                                               \
            "; call handle_panicking_interrupt"                         \
            "; pop %eax");                                              \
                                                                        \
        asm volatile ("pop %gs; pop %fs; pop %es; pop %ds; popa");      \
    }, 0x8E);
    _INTERRUPT_LIST
#undef X

    idt.set_entry(15, handle_generic_interrupt, 0x8E);
}

