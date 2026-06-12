#pragma once
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>

typedef uint64_t u64;

extern u64 white_pawns;
extern u64 white_knights;
extern u64 white_bishops;
extern u64 white_rooks;
extern u64 white_queens;
extern u64 white_king;

extern u64 black_pawns;
extern u64 black_knights;
extern u64 black_bishops;
extern u64 black_rooks;
extern u64 black_queens;
extern u64 black_king;
extern u64 white_pieces;
extern u64 black_pieces;

extern u64 occupied;
extern u64 empty;

extern TTF_Font *Sans;

#define get_bit(bitboard, index) (((bitboard >> index)) & 1ULL)
#define set_bit(bitboard, index) ((bitboard) |= (1ULL << (index)))
#define pop_bit(bitboard, index) ((bitboard) &= ~(1ULL << (index)))

void movePiece(SDL_Event event);
int renderBoard(SDL_Renderer *renderer);
