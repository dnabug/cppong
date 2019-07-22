#pragma once

#include <SDL.h>

#include <string>

// Utility surface manipulation & drawing functions

namespace pong
{

#define PONG_NUMBER_WIDTH  40
#define PONG_NUMBER_HEIGHT 100
#define PONG_NUMBER_SPACING 20
#define PONG_CELL_THICKNESS 5

SDL_Surface* ReverseSurface(SDL_Surface* src);

SDL_Surface* DrawCircle(int radius);

void DrawNumber(SDL_Renderer* r, SDL_Point pos, int number);

void DrawDigit(SDL_Renderer* r, SDL_Point pos, char digit);

/* Given a numeric character 0-9, returns the information detailing which
 * 'cells' of the number display should be filled.
 *
 * Numbers are drawn in a LED display style with seven cells, hence the
 * arrangement is in the form '0b0xxxxxxx', where each bit beyond the most
 * significant corresponds to a cell.
 *
 * 55555
 * 6   4
 * 6   4
 * 33333
 * 2   0
 * 2   0
 * 11111
 */
char GetNumberArrangement(char c);

SDL_Rect GetCellArea(char bit);

}
