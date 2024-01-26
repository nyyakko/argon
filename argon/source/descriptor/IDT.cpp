#include "descriptor/IDT.hpp"

#include "descriptor/handling/ISR.hpp"
#include "descriptor/handling/IRQ.hpp"

IDT::IDT():
    table_m ({
        .limit = sizeof(entries_m) - 1,
        .base  = reinterpret_cast<uint32_t>(entries_m)
    })
{
    isr::install(*this);
    irq::install(*this);
}

void IDT::set_entry(size_t const index, void(*isr)(), uint8_t const flags)
{
    auto* entry = &entries_m[index];

    entry->isrLow     = reinterpret_cast<uint32_t>(isr) & 0xFFFF;
    entry->kernelCs   = 0x08;
    entry->attributes = flags;
    entry->isrHigh    = reinterpret_cast<uint32_t>(isr) >> 16;
    entry->reserved   = 0;
}

void IDT::set_irq_handler(const size_t index, irq_handler_t handler)
{
    IDT::handlers_m[index] = handler;
}

IDT::irq_handler_t IDT::get_irq_handler(const size_t index)
{
    return IDT::handlers_m[index];
}

