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

typedef uint64_t ui64;

#define get_bit(bitboard, index) (((bitboard >> index)) & 1ULL)

ui64 black_pawns = 0x00FF000000000000ULL;
ui64 black_rooks = 0x8100000000000000ULL;
ui64 black_knights = 0x4200000000000000ULL;
ui64 black_bishops = 0x2400000000000000ULL;
ui64 black_queens = 0x0800000000000000ULL;
ui64 black_king = 0x1000000000000000ULL;

ui64 white_pawns = 0x000000000000FF00ULL;
ui64 white_rooks = 0x0000000000000081ULL;
ui64 white_knights = 0x0000000000000042ULL;
ui64 white_bishops = 0x0000000000000024ULL;
ui64 white_queens = 0x0000000000000008ULL;
ui64 white_king = 0x0000000000000010ULL;

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
  ui64 white_pieces = white_knights | white_bishops | white_pawns |
                      white_queens | white_rooks | white_king;
  ui64 black_pieces = black_knights | black_bishops | black_pawns |
                      black_queens | black_rooks | black_king;

  ui64 occupied = white_pieces | black_pieces;
  ui64 empty = ~occupied;

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
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    renderBoard(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(10);
  }

  return 0;
}
