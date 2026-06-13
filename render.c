#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define tileSize 80

int squareToBit(char *square) {
  int file = square[0] - 'a';
  int rank = square[1] - '1';
  return rank * 8 + file;
}

static void drawBase(SDL_Renderer *renderer) {

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {

      SDL_Rect rect = {x * tileSize, y * tileSize, tileSize, tileSize};

      if ((x + y) % 2 == 0)
        SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255);
      else
        SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255);

      SDL_RenderFillRect(renderer, &rect);
    }
  }
}

static void drawPieces(SDL_Renderer *renderer, ui64 bitboard, pieceName_t piece,
                       const char *color) {

  const char *name = "";

  switch (piece) {
  case PAWN:
    name = "PAWN";
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

  while (bitboard) {
    int square = __builtin_ctzll(bitboard);

    int x = square % 8;
    int y = square / 8;

    SDL_Rect dst = {x * tileSize, (7 - y) * tileSize, tileSize, tileSize};

    char path[128];
    snprintf(path, sizeof(path), "./pieces/%s_%s.png", name, color);

    SDL_Texture *tex = IMG_LoadTexture(renderer, path);
    SDL_RenderCopy(renderer, tex, NULL, &dst);
    SDL_DestroyTexture(tex);

    bitboard &= (bitboard - 1);
  }
}

int renderBoard(SDL_Renderer *renderer) {

  drawBase(renderer);

  drawPieces(renderer, white_pawns, PAWN, "white");
  drawPieces(renderer, white_knights, KNIGHT, "white");
  drawPieces(renderer, white_bishops, BISHOP, "white");
  drawPieces(renderer, white_rooks, ROOK, "white");
  drawPieces(renderer, white_queens, QUEEN, "white");
  drawPieces(renderer, white_king, KING, "white");

  drawPieces(renderer, black_pawns, PAWN, "black");
  drawPieces(renderer, black_knights, KNIGHT, "black");
  drawPieces(renderer, black_bishops, BISHOP, "black");
  drawPieces(renderer, black_rooks, ROOK, "black");
  drawPieces(renderer, black_queens, QUEEN, "black");
  drawPieces(renderer, black_king, KING, "black");

  return 0;
}
