#include <iostream>
#include <SDL.h>

#include "display.hpp"

int main()
{
    {
        pong::Display display(960, 720, 16);
        while (display.Cycle()) {}
    }
}
