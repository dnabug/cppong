#include <iostream>
#include <SDL.h>

#include "display.hpp"

int main()
{
    {
        pong::Display display(640, 480, 16);
        while (display.Cycle()) {}
    }
}
