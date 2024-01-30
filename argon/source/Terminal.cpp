#include "Terminal.hpp"

void Terminal::set_cursor_color(Pair<VGAColor, VGAColor> const color)
{
    Terminal::the().cursorColor_m = color;
}

Pair<VGAColor, VGAColor> Terminal::get_cursor_color()
{
    return Terminal::the().cursorColor_m;
}

void Terminal::put(char const data, VGAColor const foreground, VGAColor const background)
{
    if (auto color = Terminal::the().cursorColor_m; color != Terminal::DEFAULT_CURSOR_COLOR)
        VGA::put_entry(VGAEntry(data, color.first, color.second));
    else
        VGA::put_entry(VGAEntry(data, foreground, background));
}

void Terminal::put(StringView const data, VGAColor const foreground, VGAColor const background)
{
    for (auto index = 0lu; index < data.size(); index++)
    {
        put(data.data()[index], foreground, background);
    }
}

void Terminal::putln(StringView const data, VGAColor const foreground, VGAColor const background)
{
    put(data, foreground, background);
    put("\n"_sv, foreground, background);
}

