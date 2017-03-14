// Draw Line: A monochrome screen is stored as a single array of bytes, allowing eight consecutive
// pixels to be stored in one byte. The screen has width w, where w is divisible by 8 (that is, no byte will
// be split across rows). The height of the screen, of course, can be derived from the length of the array
// and the width. Implement a function that draws a horizontal line from (x1, y) to (x2, y).
// The method signature should look something like:
// drawLine(byte[] screen, int width, int x1, int x2, int y)

#include <vector>
#include <cstdint>
#include <iostream>
#include "bitutils.hpp"

void drawLine(std::vector<uint8_t> &screen, int width, int x1, int x2, int y)
{
    if (y < 0 || static_cast<decltype(screen.size())>(y) > screen.size() / (width / 8))
        return;
    if (width < 0 || width % 8 || static_cast<decltype(screen.size())>(width) > screen.size())
        return;

    if (x1 > x2)
        std::swap(x1, x2);
    x1 = std::min(std::max(x1, 0), width - 1);
    x2 = std::min(std::max(x2, 0), width - 1);

    int lineStart = width / 8 * y + x1 / 8;
    int lineEnd = width / 8 * y + x2 / 8;

    if (lineStart == lineEnd) // x1 and x2 are in one byte
    {
        screen[lineStart] |= (0xFF >> x1 % 8) & (0xFF << (8 - x2 % 8 - 1));
    }
    else
    {
        screen[lineStart] |= 0xFF >> x1 % 8;
        screen[lineEnd] |= 0xFF << (8 - x2 % 8 - 1);
        std::fill(&screen[lineStart + 1], &screen[lineEnd], 0xFF);
    }
}

void outScreen(const std::vector<uint8_t> &screen, int width)
{
    if (width < 0 || width % 8 || static_cast<decltype(screen.size())>(width) > screen.size())
        return;

    for (int i = 0; i < width; i += 10)
    {
        std::cout << i / 10 << "         ";
    }
    std::cout << '\n';

    auto row = 0;
    for (const auto &pxls : screen)
    {
        std::cout << bits(pxls);
        row += 8;
        if (row == width)
        {
            row = 0;
            std::cout << '\n';
        }
    }
}

int main()
{
    std::vector<uint8_t> screen(5 * 16); // 40 x 16

    drawLine(screen, 40,  8, 31, 1);
    drawLine(screen, 40, 10, 35, 3);
    drawLine(screen, 40, 25, 29, 5);
    drawLine(screen, 40, 45, -5, 7);
    drawLine(screen, 40, 32, 32, 9);
    drawLine(screen, 40, 33, 33, 11);
    drawLine(screen, 40,  0, 39, 13);
    outScreen(screen, 40);
}
