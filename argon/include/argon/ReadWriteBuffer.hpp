#pragma once

#include <stddef.h>

#include "libc/memset.hpp"

template <size_t _size = 256>
class ReadWriteBuffer
{
public:
    constexpr ReadWriteBuffer()
    {
        libc::memset(data_m, '\0', _size);
    }

    constexpr auto data(this auto& self) { return self.data_m; }
    constexpr auto size(this auto&) { return _size; }

private:
    char data_m[_size];
};

