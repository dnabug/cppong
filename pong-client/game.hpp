#pragma once

#include <SDL.h>

namespace pong
{

class Game
{
public:
    Game(SDL_Renderer* renderer, SDL_Window* window);

    void Logic();
    void Draw();

private:
    void DrawPaddle(SDL_Point position);
    void DrawBall(SDL_Point position);

    SDL_Texture* circle;
    int circle_radius = 10;

    SDL_Renderer* renderer;
    SDL_Window* window;
};

}
