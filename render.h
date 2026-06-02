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

extern TTF_Font *Sans;

int renderBoard(SDL_Renderer *renderer);
