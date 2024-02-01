#include <stdint.h>

void apply(void(*function)(void*), void* value)
{
    function(value);
}

