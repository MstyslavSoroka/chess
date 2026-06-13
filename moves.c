#include "moves.h"
#include <stdio.h>

static int selectedSquare = -1;
static int pieceSelected = 0;

ui64 *bitboards[] = {&white_pawns, &white_knights, &white_bishops,
                     &white_rooks, &white_queens,  &white_king,
                     &black_pawns, &black_knights, &black_bishops,
                     &black_rooks, &black_queens,  &black_king};

static const char boardNotation[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

void movePiece(SDL_Event event) {

  int file = event.button.x / 80;
  int rank = 7 - (event.button.y / 80);

  int bit = rank * 8 + file;

  if (!pieceSelected) {
    selectedSquare = bit;
    pieceSelected = 1;
    return;
  }

  for (int i = 0; i < 12; i++) {
    if (get_bit(*bitboards[i], selectedSquare)) {
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
