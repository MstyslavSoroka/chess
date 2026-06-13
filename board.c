#include "render.h"

ui64 white_pawns = 0x000000000000FF00ULL;
ui64 white_rooks = 0x0000000000000081ULL;
ui64 white_knights = 0x0000000000000042ULL;
ui64 white_bishops = 0x0000000000000024ULL;
ui64 white_queens = 0x0000000000000008ULL;
ui64 white_king = 0x0000000000000010ULL;

ui64 black_pawns = 0x00FF000000000000ULL;
ui64 black_rooks = 0x8100000000000000ULL;
ui64 black_knights = 0x4200000000000000ULL;
ui64 black_bishops = 0x2400000000000000ULL;
ui64 black_queens = 0x0800000000000000ULL;
ui64 black_king = 0x1000000000000000ULL;

ui64 legalMoves = 0;
