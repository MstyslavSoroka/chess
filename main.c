#include "moves.h"
#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define W 1000
#define H 640
bool app_running = true;
TTF_Font *Sans = NULL;

void print_bitboard(ui64 bitboard) {
  for (int y = 7; y >= 0; y--) {
    for (int x = 0; x < 8; x++) {
      int tile = (7 - y) * 8 + x;
      printf("%d", get_bit(bitboard, tile) ? 1 : 0);
    }
    printf("\n");
  }
}

int main() {

  print_bitboard(white_king);

  if (TTF_Init() == -1) {
    printf("TTF_Init failed: %s\n", TTF_GetError());
  }
  Sans = TTF_OpenFont("opensans.ttf", 24);
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow = SDL_CreateWindow("Chess", SDL_WINDOWPOS_CENTERED,
                                         SDL_WINDOWPOS_CENTERED, W, H, 0);

  SDL_Renderer *renderer =
      SDL_CreateRenderer(pwindow, -1, SDL_RENDERER_ACCELERATED);

  while (app_running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        app_running = false;
        break;
      case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == 1 && event.button.x < 640) {
          movePiece(event);
        }

        break;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderBoard(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(50);
  }

  return 0;
}
