#include "GDT.hpp"

GDT::GDT() noexcept:
    table_m ({
        .limit = sizeof(entries_m) - 1,
        .base  = reinterpret_cast<uint32_t>(entries_m)
    })
{
    this->set_entry(0, 0, 0, 0, 0);
    this->set_entry(1, 0, 0xFFFF'FFFF, 0x9A, 0xCF);
    this->set_entry(2, 0, 0xFFFF'FFFF, 0x92, 0xCF);
    this->set_entry(3, 0, 0xFFFF'FFFF, 0xFA, 0xCF);
    this->set_entry(4, 0, 0xFFFF'FFFF, 0xF2, 0xCF);
}

void GDT::set_entry(size_t const index, uint32_t const base, uint32_t const limit, uint8_t const access, uint8_t const granularity) noexcept
{
    auto* entry = &entries_m[index];

    entry->segmentLimit = limit & 0xFFFF;
    entry->baseLow      = base & 0xFFFF;
    entry->baseMiddle   = (base >> 16) & 0xFF;
    entry->access       = access;
    entry->granularity  = (limit >> 16) & 0x0F;
    entry->granularity  = entry->granularity | (granularity & 0xF0);
    entry->baseHigh     = (base >> 24 & 0xFF);
}
