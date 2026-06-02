#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <stdio.h>

#define tileSize 80

void drawBase(SDL_Renderer *renderer) {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      SDL_Rect rect = {x * tileSize, y * tileSize, tileSize, tileSize};
      SDL_SetRenderDrawColor(renderer, 118, 150, 86,
                             255); // dark color green

      if ((x + y) % 2 == 0) {
        SDL_SetRenderDrawColor(renderer, 238, 238, 210,
                               255); // light color green
      }
      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

int renderBoard(SDL_Renderer *renderer) {

  drawBase(renderer);
  return 0;
}
