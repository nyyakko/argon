#pragma once

#include <libc/string.hpp>

class StringView
{
public:
    // cppcheck-suppress noExplicitConstructor
    constexpr StringView(char const* string):
        data_m(string),
        size_m(strlen(string))
    {
    }

    constexpr auto const* data() const { return this->data_m; }
    constexpr auto size() const { return this->size_m; }

    constexpr auto operator==(StringView toCompare) const
    {
        return strcmp(this->data(), toCompare.data());
    }

private:
    char const* data_m = nullptr;
    size_t size_m = 0;
};

constexpr StringView operator""_sv(char const* data, size_t)
{
    return StringView(data);
}

