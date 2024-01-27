#pragma once

#include <stddef.h>
#include <stdint.h>

namespace port {

static constexpr auto FB_COMMAND   = 0x3D4;
static constexpr auto FB_DATA      = 0x3D5;
static constexpr auto CMOS_COMMAND = 0x70;
static constexpr auto CMOS_DATA    = 0x71;
static constexpr auto BIOS_IO      = 0x60;
static constexpr auto PIC1_COMMAND = 0x20;
static constexpr auto PIC1_DATA    = 0x21;
static constexpr auto PIC2_COMMAND = 0xA0;
static constexpr auto PIC2_DATA    = 0xA1;

    namespace cmos {

    static constexpr auto SECONDS      = 0x00;
    static constexpr auto MINUTES      = 0x02;
    static constexpr auto HOURS        = 0x04;
    static constexpr auto DAY_OF_WEEK  = 0x06;
    static constexpr auto DAY_OF_MONTH = 0x07;
    static constexpr auto MONTH        = 0x08;
    static constexpr auto YEAR         = 0x09;

    }

}

uint8_t inb(uint16_t const port);
void outb(uint16_t const port, uint8_t const value);
