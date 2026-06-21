#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <stdint.h>

typedef uint64_t ui64;

typedef enum pieceName { PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING } pieceName_t;

extern ui64 white_pawns;
extern ui64 white_knights;
extern ui64 white_bishops;
extern ui64 white_rooks;
extern ui64 white_queens;
extern ui64 white_king;

extern ui64 black_pawns;
extern ui64 black_knights;
extern ui64 black_bishops;
extern ui64 black_rooks;
extern ui64 black_queens;
extern ui64 black_king;

extern ui64 legalMoves;
extern ui64 knightMoves[64];

extern TTF_Font *Sans;

#define get_bit(bb, idx) (((bb) >> (idx)) & 1ULL)
#define set_bit(bb, idx) ((bb) |= (1ULL << (idx)))
#define pop_bit(bb, idx) ((bb) &= ~(1ULL << (idx)))

void movePiece(SDL_Event event);
int renderBoard(SDL_Renderer *renderer);
int squareToBit(char *square);
