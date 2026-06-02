#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define tileSize 80

typedef uint64_t ui64;

typedef enum pieceName { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING } pieceName_t;

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

void drawPieces(SDL_Renderer *renderer, ui64 bitboard, pieceName_t pieceName) {

  SDL_Color White = {255, 255, 255};
  while (bitboard) {
    int square = __builtin_ctzll(bitboard);
    int x = square % 8;
    int y = square / 8;

    SDL_Rect messageRect = {x * tileSize, y * tileSize, tileSize, tileSize};
    char *name = "";
    switch (pieceName) {
    case PAWN:
      name = "PAWN";
      // printf("Drew a pawn");
      break;
    case BISHOP:
      name = "BISHOP";
      break;

    case KNIGHT:

      name = "KNIGHT";

      break;

    case ROOK:
      name = "ROOK";

      break;

    case QUEEN:
      name = "QUEEN";

      break;

    case KING:
      name = "KING";
      break;
    }

    SDL_Surface *surfaceMessage = TTF_RenderText_Solid(Sans, name, White);

    SDL_Texture *Message =
        SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_RenderCopy(renderer, Message, NULL, &messageRect);
    bitboard &= bitboard - 1;
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
  }
}

int renderBoard(SDL_Renderer *renderer) {

  drawBase(renderer);

  drawPieces(renderer, white_pawns, PAWN);
  drawPieces(renderer, white_knights, KNIGHT);
  drawPieces(renderer, white_bishops, BISHOP);
  drawPieces(renderer, white_rooks, ROOK);
  drawPieces(renderer, white_queens, QUEEN);
  drawPieces(renderer, white_king, KING);

  drawPieces(renderer, black_pawns, PAWN);
  drawPieces(renderer, black_knights, KNIGHT);
  drawPieces(renderer, black_bishops, BISHOP);
  drawPieces(renderer, black_rooks, ROOK);
  drawPieces(renderer, black_queens, QUEEN);
  drawPieces(renderer, black_king, KING);

  return 0;
}
