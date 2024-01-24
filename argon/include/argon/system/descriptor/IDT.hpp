#pragma once

#include <stddef.h>
#include <stdint.h>

#include "Terminal.hpp"

namespace {

extern "C" void load_idt(uint32_t address);

inline void interrupt_generic()
{
    Terminal::putln("unknown interrupt");
}

}

struct Registers
{
    unsigned int GS, FS, ES, DS;
    unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
    unsigned int interruptID, errorCode;
    unsigned int EIP, CS, eflags, userESP, SS;
};

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

    IDT();

public:
    static IDT& initialize()
    {
        static IDT the {};
        load_idt(reinterpret_cast<uint32_t>(&the.table_m));
        return the;
    }

    void set_entry(size_t const index, void(*isr)(), uint8_t const flags);

private:
    struct [[gnu::packed]] IDTTable
    {
        uint16_t limit;
        uint32_t base;
    };

    IDTEntry entries_m[IDT_MAX_DESCRIPTORS] {};
    IDTTable table_m {};
};

