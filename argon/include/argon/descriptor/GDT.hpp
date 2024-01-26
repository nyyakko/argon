#pragma once

#include <stdint.h>
#include <stddef.h>

namespace {

extern "C" void load_gdt(uint32_t address);

}

struct [[gnu::packed]] GDTEntry
{
    uint16_t segmentLimit {};
    uint16_t baseLow {};
    uint8_t  baseMiddle {};
    uint8_t  access {};
    uint8_t  granularity {};
    uint8_t  baseHigh {};
};

class GDT
{
    static constexpr auto GDT_MAX_DESCRIPTORS = 8;

    GDT();

public:
    static GDT& initialize()
    {
        static GDT the {};
        load_gdt(reinterpret_cast<uint32_t>(&the.table_m));
        return the;
    }

private:
    void set_entry(size_t const index, uint32_t const base, uint32_t const limit, uint8_t const access, uint8_t const granularity);

    struct [[gnu::packed]] GDTTable
    {
        uint16_t limit;
        uint32_t base;
    };

    GDTEntry entries_m[GDT_MAX_DESCRIPTORS] {};
    GDTTable table_m {};
};

