#include "game.hpp"

#include <iostream>
#include "draw.hpp"
#include <cmath>

namespace pong
{

Game::Game(SDL_Renderer* r, SDL_Window* w) : renderer(r), window(w)
{
    SDL_Surface* circle_surface = DrawCircle(circle_radius);
    circle = SDL_CreateTextureFromSurface(renderer, circle_surface);
    SDL_FreeSurface(circle_surface);
}

void Game::Logic()
{

}

void Game::Draw()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    DrawPaddle({10, 10});
    DrawPaddle({620, 310});

    int x = (int) (50 * cosf( (SDL_GetTicks() % 720) * (M_PI / 360) ));
    int y = (int) (50 * sinf( (SDL_GetTicks() % 720) * (M_PI / 360) ));

    DrawBall({200 + x, 200 + y});
}

void Game::DrawPaddle(SDL_Point pos)
{
    SDL_Rect r = {pos.x, pos.y, 10, 75};

    SDL_RenderFillRect(renderer, &r);
}

void Game::DrawBall(SDL_Point pos)
{
    SDL_Rect area = {pos.x, pos.y, circle_radius * 2, circle_radius * 2};
    SDL_RenderCopy(renderer, circle, NULL, &area);
}

}
