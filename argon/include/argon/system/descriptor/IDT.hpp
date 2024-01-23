#pragma once

#include <stddef.h>
#include <stdint.h>

namespace {

extern "C" void load_idt(uint32_t address);

}

struct [[gnu::packed]] IDTEntry
{
    uint16_t isrLow {};
    uint16_t kernelCs {};
    uint8_t  reserved {};
    uint8_t  attributes {};
    uint16_t isrHigh {};
};

class IDT
{
    static constexpr auto IDT_MAX_DESCRIPTORS = 256;

    IDT() noexcept;

public:
    static IDT& initialize() noexcept
    {
        static IDT the {};
        load_idt(reinterpret_cast<uint32_t>(&the.table_m));
        return the;
    }

    void set_entry(size_t const index, void(*isr)(), uint8_t const flags) noexcept;

private:
    struct [[gnu::packed]] IDTTable
    {
        uint16_t limit;
        uint32_t base;
    };

    IDTEntry entries_m[IDT_MAX_DESCRIPTORS] {};
    IDTTable table_m {};
};

