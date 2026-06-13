#include "render.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define tileSize 80

typedef uint64_t ui64;
static int selectedSquare = -1;

bool pieceSelected = false;

typedef enum pieceName { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING } pieceName_t;
char boardNotation[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

ui64 legalMoves = 0x0ULL;
ui64 *bitboards[] = {&white_pawns, &white_knights, &white_bishops,
                     &white_rooks, &white_queens,  &white_king,
                     &black_pawns, &black_knights, &black_bishops,
                     &black_rooks, &black_queens,  &black_king};

ui64 getLegalMoves(int pieceIndex, int curSquare, ui64 occupied) {

  switch (pieceIndex) {
  case 1:
    break;
  }
  return 0;
}

int squareToBit(char *square) {
  char file = square[0];
  char rank = square[1];

  int fileIndex = file - 'a';
  int rankIndex = rank - '1';
  return rankIndex * 8 + fileIndex;
}

void drawBase(SDL_Renderer *renderer) {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      int tile = (7 - y) * 8 + x;
      if (get_bit(legalMoves, tile)) {
        SDL_Rect rect = {x * tileSize, y * tileSize, tileSize - 10,
                         tileSize - 10};
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
      }
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

void movePiece(SDL_Event event) {
  ui64 white_pieces = white_knights | white_bishops | white_pawns |
                      white_queens | white_rooks | white_king;
  ui64 black_pieces = black_knights | black_bishops | black_pawns |
                      black_queens | black_rooks | black_king;
  ui64 occupied = white_pieces | black_pieces;

  char notation[16];
  snprintf(notation, sizeof(notation), "%c%d",
           *(boardNotation + (int)ceil(event.button.x / 80)),
           7 - (int)ceil(event.button.y / 80) + 1);
  int bit = squareToBit(notation);

  if (!pieceSelected) {
    selectedSquare = bit;
    pieceSelected = true;
  } else {
    for (int i = 0; i < 12; i++) {
      if (get_bit(*bitboards[i], selectedSquare)) {
        pop_bit(*bitboards[i], selectedSquare);
        set_bit(*bitboards[i], bit);
        break;
      }
    }

    selectedSquare = -1;
    pieceSelected = false;
  }

  printf("%s\n", notation);

  printf("%d\n", bit);
}

void drawPieces(SDL_Renderer *renderer, ui64 bitboard, pieceName_t pieceName,
                char *color) {

  while (bitboard) {
    int square = __builtin_ctzll(bitboard);
    int x = square % 8;
    int y = square / 8;

    SDL_Rect dst = {x * tileSize, (7 - y) * tileSize, tileSize, tileSize};

    const char *name = "";
    switch (pieceName) {
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

    char path[128];
    snprintf(path, sizeof(path), "./pieces/%s_%s.png", name, color);

    SDL_Texture *tex = IMG_LoadTexture(renderer, path);
    SDL_RenderCopy(renderer, tex, NULL, &dst);

    bitboard &= bitboard - 1;
    SDL_DestroyTexture(tex);
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
