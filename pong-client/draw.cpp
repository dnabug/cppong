#include "draw.hpp"

#include <SDL.h>

#include <cstring>

namespace pong
{

SDL_Surface* ReverseSurface(SDL_Surface* src)
{
    SDL_Surface* result =
        SDL_CreateRGBSurface(0, src->w, src->h, 32, 0, 0, 0, 0);

    SDL_LockSurface(result);

    int length = src->w * src->h;
    Uint32* destpixels = (Uint32*) result->pixels;
    Uint32* srcpixels = (Uint32*) src->pixels;

    for (int i = 0; i < length; i++) {
        int offset = length - 1 - i;
        memcpy(destpixels + i, srcpixels + offset, 4);
    }

    SDL_UnlockSurface(result);

    return result;
}

SDL_Surface* DrawCircle(int r)
{
    SDL_Surface* result =
        SDL_CreateRGBSurface(0, 2*r, 2*r, 32, 0, 0, 0, 0);

    // The top half of the circle. The bottom half will just be a vertically
    // flipped version of this surface.
    SDL_Surface* top = SDL_CreateRGBSurface(0, 2*r, r, 32, 0, 0, 0, 0);

    // Fill with transparent background
    SDL_FillRect(top, NULL, SDL_MapRGB(top->format, 0, 0, 0));

    // Split the top semicircle into 'r' rows. We then determine the length of
    // each row and where it should be.
    for (int d = 1; d <= r; d++) {
        Sint32 x = (Sint32) (round(sqrt(2*d*r - d*d)));
        SDL_Rect line = {r - x, d - 1, 2 * x, 1};
        SDL_FillRect(top, &line, SDL_MapRGB(top->format, 255, 255, 255));
    }

    SDL_Surface* bottom = ReverseSurface(top);

    SDL_Rect top_area = SDL_Rect {0, 0, 2*r, r};
    SDL_Rect bot_area = SDL_Rect {0, r-1, 2*r, r};

    SDL_BlitSurface(top, NULL, result, &top_area);
    SDL_BlitSurface(bottom, NULL, result, &bot_area);

    SDL_FreeSurface(top);
    SDL_FreeSurface(bottom);

    return result;
}

}
