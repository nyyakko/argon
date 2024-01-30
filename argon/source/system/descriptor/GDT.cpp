#include "system/descriptor/GDT.hpp"

/*
    https://cdrdv2-public.intel.com/812392/325462-sdm-vol-1-2abcd-3abcd-4.pdf @ figure 3-8.

    L     — 64-bit code segment (IA-32e mode only)
    AVL   — Available for use by system software
    BASE  — Segment base address
    D/B   — Default operation size (O = 16-bit segment; 1 = 32-bit segment)
    DPL   — Descriptor privilege level
    G     — Granularity
    LIMIT — Segment Limit
    P     — Segment present
    S     — Descriptor type (0 = system; 1 = code or data)
    TYPE  — Segment type
*/

GDT::GDT():
    table_m ({
        .limit = sizeof(entries_m) - 1,
        .base  = reinterpret_cast<uint32_t>(entries_m.data())
    })
{
    this->set_entry(0, 0, 0, 0, 0);
    this->set_entry(1, 0, 0xFFFF'FFFF, 0x9A, 0xCF);
    this->set_entry(2, 0, 0xFFFF'FFFF, 0x92, 0xCF);
    this->set_entry(3, 0, 0xFFFF'FFFF, 0xFA, 0xCF);
    this->set_entry(4, 0, 0xFFFF'FFFF, 0xF2, 0xCF);
}

void GDT::set_entry(size_t const index, uint32_t const base, uint32_t const limit, Access const access, uint8_t const granularity)
{
    auto* entry = &entries_m[index];

    entry->segmentLimit = limit        & 0xFFFF;
    entry->baseLow      = base         & 0xFFFF;
    entry->baseMiddle   = (base >> 16) & 0xFF;
    entry->access       = access;
    entry->granularity  = (limit >> 16) & 0x0F;
    entry->granularity  = entry->granularity | (granularity & 0xF0);
    entry->baseHigh     = (base >> 24 & 0xFF);
}

