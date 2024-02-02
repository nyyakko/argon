#pragma once

#include <stddef.h>
#include <stdint.h>

#include <libcpp/Array.hpp>

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

struct [[gnu::packed]] IDTTable
{
    uint16_t limit;
    uint32_t base;
};

class IDT
{
    static constexpr auto IDT_MAX_DESCRIPTORS = 256;

    IDT();

public:
    static IDT& initialize()
    {
        static IDT idt {};
        load_idt(reinterpret_cast<uint32_t>(&idt.table_m));
        return idt;
    }

    static IDT& the() { return IDT::initialize(); }

    using irq_handler_t = void(*)(InterruptStack const*);

    void set_entry(size_t const index, void(*isr)(), uint8_t const flags);
    static void set_irq_handler(size_t const index, irq_handler_t const handler);
    static irq_handler_t get_irq_handler(size_t const index);

private:
    Array<IDTEntry, IDT_MAX_DESCRIPTORS> entries_m {};
    IDTTable table_m {};
    Array<irq_handler_t, 16> handlers_m {};
};

