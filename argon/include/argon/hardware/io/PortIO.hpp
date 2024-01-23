#pragma once

#include <stddef.h>
#include <stdint.h>

namespace io {

    namespace ports {

    static constexpr auto FB_COMMAND_PORT = 0x3D4;
    static constexpr auto FB_DATA_PORT    = 0x3D5;
    static constexpr auto BIOS_IO_PORT    = 0x60;

    }

inline auto inb(uint16_t const port) noexcept
{
    uint8_t result = 0;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port) : "memory");
    return result;
}

inline void outb(uint16_t const port, uint8_t const value) noexcept
{
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

}
