#pragma once

#include <iostream>
#include <SDL.h>

#include "game.hpp"

namespace pong
{

class Display
{
public:
    Display(int width, int height, int mspertick);
    ~Display();
    bool Cycle();

private:
    int mspertick = 16;
    int width, height; // Window dimensions
    const int rwidth = 640, rheight = 480; // Width and height of renderer
    Game* game;

public:
    SDL_Renderer* renderer;
    SDL_Window* window;
};

}
