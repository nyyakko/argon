#include "IDT.hpp"

#include "Exception.hpp"

IDT::IDT() noexcept:
    table_m ({
        .limit = sizeof(entries_m) - 1,
        .base  = reinterpret_cast<uint32_t>(entries_m)
    })
{
    set_entry(0, interrupt_0, 0x8E);
    set_entry(1, interrupt_1, 0x8E);
    set_entry(2, interrupt_2, 0x8E);
    set_entry(3, interrupt_3, 0x8E);
    set_entry(4, interrupt_4, 0x8E);
    set_entry(5, interrupt_5, 0x8E);
    set_entry(6, interrupt_6, 0x8E);
    set_entry(7, interrupt_7, 0x8E);
    set_entry(8, interrupt_8, 0x8E);
    set_entry(9, interrupt_9, 0x8E);
    set_entry(10, interrupt_10, 0x8E);
    set_entry(11, interrupt_11, 0x8E);
    set_entry(12, interrupt_12, 0x8E);
    set_entry(13, interrupt_13, 0x8E);
    set_entry(14, interrupt_14, 0x8E);
    set_entry(15, interrupt_15, 0x8E);
    set_entry(16, interrupt_16, 0x8E);
    set_entry(17, interrupt_17, 0x8E);
    set_entry(18, interrupt_18, 0x8E);
    set_entry(19, interrupt_19, 0x8E);
    set_entry(20, interrupt_20, 0x8E);
    set_entry(21, interrupt_21, 0x8E);

    for (auto index = 22zu; index != IDT_MAX_DESCRIPTORS; index += 1)
    {
        set_entry(index, interrupt_generic, 0x8E);
    }
}

void IDT::set_entry(size_t const index, void(*isr)(), uint8_t const flags) noexcept
{
    auto* entry = &entries_m[index];

    entry->isrLow     = reinterpret_cast<uint32_t>(isr) & 0xFFFF;
    entry->kernelCs   = 0x08;
    entry->attributes = flags;
    entry->isrHigh    = reinterpret_cast<uint32_t>(isr) >> 16;
    entry->reserved   = 0;
}
