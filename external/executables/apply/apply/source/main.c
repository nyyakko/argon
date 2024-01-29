#include <stdint.h>

void apply(void(*function)(char const*), char const* message)
{
    function(message);
}

