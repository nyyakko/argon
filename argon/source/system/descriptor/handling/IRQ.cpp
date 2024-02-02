#include "system/descriptor/handling/IRQ.hpp"

#include "Terminal.hpp"
#include "hardware/IO.hpp"

static void pic_remap();

#define IRQ_LIST                              \
X(0) X(1) X(2)  X(3)  X(4)  X(5)  X(6)  X(7)  \
X(8) X(9) X(10) X(11) X(12) X(13) X(14) X(15)

#define X(index) extern "C" void irq_##index();
IRQ_LIST
#undef X

extern "C" void interrupt_handler_dispatcher(InterruptStack const* interruptStack)
{
    if (auto const handler = IDT::get_irq_handler(interruptStack->ID))
    {
        handler(interruptStack);
    }
    else
    {
        Terminal::putf("interrupt request id {} was left unhandled.\n", interruptStack->ID);
    }

    if (interruptStack->ID >= 8)
    {
        port::outb(port::PIC2_COMMAND, 0x20);
    }

    port::outb(port::PIC1_COMMAND, 0x20);
}

void irq::install(IDT& idt)
{
    pic_remap();

#define X(index) \
    idt.set_entry(32 + index, irq_##index, 0x8E);
    IRQ_LIST
#undef X
}

static void pic_remap()
{
    port::outb(port::PIC1_COMMAND , 0x11);
    port::outb(port::PIC2_COMMAND , 0x11);
    port::outb(port::PIC1_DATA    , 0x20);
    port::outb(port::PIC1_DATA    , 0x04);
    port::outb(port::PIC1_DATA    , 0x01);
    port::outb(port::PIC1_DATA    , 0x00);
    port::outb(port::PIC2_DATA    , 0x28);
    port::outb(port::PIC2_DATA    , 0x02);
    port::outb(port::PIC2_DATA    , 0x01);
    port::outb(port::PIC2_DATA    , 0x00);
}

