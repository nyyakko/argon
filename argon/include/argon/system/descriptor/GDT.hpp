#pragma once

#include <stdint.h>
#include <stddef.h>

#include <libcpp/Array.hpp>

namespace {

extern "C" void load_gdt(uint32_t address);

}

enum class Ring : uint8_t
{
    _0, _1, _2, _3, _4, _5, _6, _7
};

enum class Kind : uint8_t
{
    _0, _1
};

class Access
{
public:
    constexpr Access() {};
    // cppcheck-suppress noExplicitConstructor
    constexpr Access(uint8_t const value): value_m(value) { }

    constexpr auto present() const { return (*this & 0x80) != 0; }
    constexpr Ring ring() const { return Ring((~(*this & 0x80) & *this) >> 4); }
    constexpr Kind kind() const { return (*this & 0x8) ? Kind::_1 : Kind::_0; }

    constexpr operator uint8_t() const
    {
        return value_m;
    }

private:
    uint8_t value_m {};
};

class Granularity
{
public:
    constexpr Granularity() {};
    // cppcheck-suppress noExplicitConstructor
    constexpr Granularity(uint8_t const value): value_m(value) { }

    constexpr auto size_in_bytes() const { return (*this & 0x80) ? 1 : 4096; }
    constexpr auto operand_size_in_bits() const { return (*this & 0x40) ? 16 : 32; }

    constexpr operator uint8_t() const
    {
        return value_m;
    }

private:
    uint8_t value_m {};
};

struct [[gnu::packed]] GDTEntry
{
    uint16_t segmentLimit {};
    uint16_t baseLow {};
    uint8_t  baseMiddle {};
    Access   access {};
    Granularity granularity {};
    uint8_t  baseHigh {};
};

struct [[gnu::packed]] GDTTable
{
    uint16_t limit;
    uint32_t base;
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

    static GDT& the() { return GDT::initialize(); }

private:
    void set_entry(size_t const index, uint32_t const base, uint32_t const limit, Access const access, uint8_t const granularity);

    Array<GDTEntry, GDT_MAX_DESCRIPTORS> entries_m {};
    GDTTable table_m {};
};

