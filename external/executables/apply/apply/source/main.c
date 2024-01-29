#include <stdint.h>

void apply(void const*(*function)(void*), void* value)
{
    function(value);
}

