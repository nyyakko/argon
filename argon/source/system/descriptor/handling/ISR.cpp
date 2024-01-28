#include "system/descriptor/handling/ISR.hpp"

#include "system/Panic.hpp"

#define ISR_LIST              \
X(0)  X(1)  X(2)  X(3)  X(4)  \
X(5)  X(6)  X(7)  X(8)  X(9)  \
X(10) X(11) X(12) X(13) X(14) \
X(16) X(17) X(18) X(19) X(20)

#define X(index) extern "C" void isr_##index();
ISR_LIST
#undef X

extern "C" void handle_panicking_interrupt(InterruptStack const* interruptStack)
{
    static constexpr auto RESERVED_INTERRUPT = 15;

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
        "", // RESERVED INTERRUPT
        "ALIGNMENT CHECK EXCEPTION"_sv,
        "MACHINE-CHECK EXCEPTION"_sv,
        "SIMD FLOATING-POINT EXCEPTION"_sv,
        "VIRTUALIZATION EXCEPTION"_sv,
        "CONTROL PROTECTION EXCEPTION"_sv
    };

    if (interruptStack->ID != RESERVED_INTERRUPT)
        panic(interruptStack, messages[interruptStack->ID]);
}

void isr::install(IDT& idt)
{
#define X(index) \
    idt.set_entry(index, isr_##index, 0x8E);
    ISR_LIST
#undef X
}

