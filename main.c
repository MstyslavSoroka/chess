#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

typedef uint64_t ui64;

#define get_bit(bitboard, index) (((bitboard >> index)) & 1ULL)

ui64 black_knights = 0x4200000000000000ULL; // init black pieces
ui64 black_rooks = 0x8100000000000000ULL;
ui64 black_pawns = 0x00FF0000000000ULL;
ui64 black_bishops = 0x2400000000000000ULL;
ui64 black_queens = 0x8000000000000000ULL;
ui64 black_king = 0x1000000000000000ULL;

ui64 white_knights = 0x0000000000000042ULL; // init white white pieces
ui64 white_rooks = 0x0000000000000081ULL;
ui64 white_pawns = 0x0000000000FF00ULL;
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

  return 0;
}
