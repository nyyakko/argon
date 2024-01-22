#pragma once

#include <stdint.h>

struct [[gnu::packed]] GDTEntry
{
    uint16_t segmentLimit {};
    uint16_t baseLow {};
    uint8_t  baseMiddle {};
    uint8_t  access {};
    uint8_t  granularity {};
    uint8_t  baseHigh {};
};

