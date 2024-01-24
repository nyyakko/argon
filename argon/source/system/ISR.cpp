#include "system/ISR.hpp"

#include "Panic.hpp"

extern "C" void handle_generic_interrupt()
{
    Terminal::putln("unknown interrupt");
}

extern "C" void handle_panicking_interrupt(Registers const* registers)
{
    constexpr static StringView messages[] =
    {
        "divide by zero"_sv,
        "debug error"_sv,
        "nmi interrupt"_sv,
        "breakpoint"_sv,
        "overflow"_sv,
        "bound range exceeded"_sv,
        "invalid opcode exception"_sv,
        "device not available exception"_sv,
        "coprocessor segment overrun"_sv,
        "invalid tss exception"_sv,
        "segment not present"_sv,
        "stack fault exception"_sv,
        "general protection exception"_sv,
        "page fault exception"_sv,
        "fpu float-point error"_sv,
        "", // reserved
        "alignment check exception"_sv,
        "machine-check exception"_sv,
        "simd floating-point exception"_sv,
        "virtualization exception"_sv,
        "control protection exception"_sv
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
