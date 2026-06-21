#include "moves.h"
#include <stdio.h>

static int selectedSquare = -1;
static int pieceSelected = 0;
typedef uint64_t ui64;

ui64 *bitboards[] = {&white_pawns, &white_knights, &white_bishops,
                     &white_rooks, &white_queens,  &white_king,
                     &black_pawns, &black_knights, &black_bishops,
                     &black_rooks, &black_queens,  &black_king};

static const char boardNotation[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

void movePiece(SDL_Event event) {
  ui64 occupied = white_pawns | white_knights | white_bishops | white_rooks |
                  white_queens | white_king | black_bishops | black_knights |
                  black_pawns | black_rooks | black_queens | black_king;

  int file = event.button.x / 80;
  int rank = 7 - (event.button.y / 80);

  int bit = rank * 8 + file;

  if (!pieceSelected) {
    if (!get_bit(occupied, bit)) {
      printf("No piece on selected square\n");
      return;
    }

    selectedSquare = bit;
    pieceSelected = 1;
    return;
  }

  for (int i = 0; i < 12; i++) {
    if (get_bit(*bitboards[i], selectedSquare)) {
      if (i == 1 || i == 7) {
        if (!get_bit(knightMoves[selectedSquare], bit)) {
          pieceSelected = 0;
          selectedSquare = -1;
          return;
        }
      };
      pop_bit(*bitboards[i], selectedSquare);
      set_bit(*bitboards[i], bit);
      break;
    }
  }

  int from = selectedSquare;

  printf("move: %c%d -> %c%d\n", boardNotation[from % 8], from / 8 + 1,
         boardNotation[file], rank + 1);

  selectedSquare = -1;
  pieceSelected = 0;
}
