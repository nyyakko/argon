#pragma once

#include <stddef.h>
#include <stdint.h>

namespace {

extern "C" void load_idt(uint32_t address);

}

struct [[gnu::packed]] InterruptStack
{
    uint32_t GS, FS, ES, DS;
    uint32_t EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
    uint32_t ID, errorCode;
    uint32_t EIP, CS, eflags, userESP, SS;
};

struct [[gnu::packed]] IDTEntry
{
    uint16_t isrLow;
    uint16_t kernelCs;
    uint8_t  reserved;
    uint8_t  attributes;
    uint16_t isrHigh;
};

class IDT
{
    static constexpr auto IDT_MAX_DESCRIPTORS = 256;

    IDT();

public:
    static IDT& initialize()
    {
        static IDT the {};
        load_idt(reinterpret_cast<uint32_t>(&the.table_m));
        return the;
    }

    using irq_handler_t = void(*)(InterruptStack const*);

    void set_entry(size_t const index, void(*isr)(), uint8_t const flags);
    static void set_irq_handler(size_t const index, irq_handler_t const handler);
    static irq_handler_t get_irq_handler(size_t const index);

private:
    struct [[gnu::packed]] IDTTable
    {
        uint16_t limit;
        uint32_t base;
    };

    IDTEntry entries_m[IDT_MAX_DESCRIPTORS] {};
    IDTTable table_m {};
    static irq_handler_t handlers_m[16];
};

inline IDT::irq_handler_t IDT::handlers_m[16] = {};

