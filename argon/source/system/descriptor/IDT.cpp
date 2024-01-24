#include "system/descriptor/IDT.hpp"

#include "system/ISR.hpp"
#include "system/IRQ.hpp"

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
