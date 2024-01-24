#pragma once

#include "libc/strlen.hpp"
#include "libc/strcmp.hpp"

class StringView
{
public:
    constexpr StringView(char const* string):
        data_m(string),
        size_m(libc::strlen(string))
    {
    }

    constexpr auto const* data(this auto& self) { return self.data_m; }
    constexpr auto size(this auto& self) { return self.size_m; }

    constexpr auto operator==(StringView toCompare)
    {
        return libc::strcmp(this->data(), toCompare.data());
    }

private:
    char const* data_m = nullptr;
    size_t size_m = 0;
};

constexpr StringView operator""_sv(char const* data, size_t)
{
    return StringView(data);
}
