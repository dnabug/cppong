#include "draw.hpp"

#include <SDL.h>

#include <cstring>
#include <iostream>
#include <string>

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

char GetNumberArrangement(char c)
{
    switch (c) {
        case 0: return 0b01110111;
        case 1: return 0b00010001;
        case 2: return 0b00111110;
        case 3: return 0b00111011;
        case 4: return 0b01011001;
        case 5: return 0b01101011;
        case 6: return 0b01101111;
        case 7: return 0b00110001;
        case 8: return 0b01111111;
        case 9: return 0b01111011;
        default: return 0b00000000;
    }
}

SDL_Rect GetCellArea(char bit)
{
    int w = PONG_NUMBER_WIDTH;
    int h = PONG_NUMBER_HEIGHT;
    int t = PONG_CELL_THICKNESS;

    SDL_Rect result;

    if (bit > 6) return result;

    // If the bit position is 0 or 4, the cell is on the right. Otherwise,
    // it is on the left.
    if (bit % 4 == 0) {
        result.x = w - 1 - t;
    } else {
        result.x = 0;
    }

    switch (bit) {
    case 1:
        result.y = h - 1 - t;
        break;
    case 0:
    case 2:
        result.y = h/2 - 1;
        break;
    case 3:
        result.y = (h - 1 - t) / 2;
        break;
    case 4:
    case 5:
    case 6:
        result.y = 0;
        break;
    }

    if (bit % 2 == 0) {
        // Even bit positions correspond to a vertical cell, odd to horizontal.
        result.w = t;
        result.h = h/2;
    } else {
        result.w = w - 1;
        result.h = t;
    }

    return result;
}

void DrawDigit(SDL_Renderer* r, SDL_Point pos, char number)
{
    char bits = GetNumberArrangement(number);
    for (int i = 0; i <= 6; i++) {
        if (!((bits >> i) & 1)) continue;

        SDL_Rect area = GetCellArea(i);

        area.x += pos.x;
        area.y += pos.y;

        SDL_RenderFillRect(r, &area);
    }
}

void DrawNumber(SDL_Renderer* r, SDL_Point pos, int number)
{
    std::string str = std::to_string(number);

    for (char c : str) {
        int digit = std::stoul(std::string(1, c));
        DrawDigit(r, pos, digit);
        pos.x += PONG_NUMBER_WIDTH + PONG_NUMBER_SPACING;
    }
}

}
