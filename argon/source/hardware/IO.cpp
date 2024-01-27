#include "hardware/IO.hpp"

uint8_t inb(uint16_t const port)
{
    uint8_t result = 0;
    asm volatile ( "inb %1, %0" : "=a"(result) : "Nd"(port) : "memory");
    return result;
}

void outb(uint16_t const port, uint8_t const value)
{
    asm volatile ( "outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

