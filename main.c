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
ui64 knightMoves[64];

void initKnight(ui64 knightMoves[64]) {
  int offsets[8][2] = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                       {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

  for (int sq = 0; sq < 64; sq++) {
    ui64 attacks = 0ULL;

    int rank = sq / 8;
    int file = sq % 8;

    for (int k = 0; k < 8; k++) {
      int r = rank + offsets[k][1];
      int f = file + offsets[k][0];

      if (r >= 0 && r < 8 && f >= 0 && f < 8) {
        set_bit(attacks, r * 8 + f);
      }
    }

    knightMoves[sq] = attacks;
  }
}

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
  initKnight(knightMoves);
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
