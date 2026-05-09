#include "movegen.h"
#include "board.h"

int main(){
    loadFEN("8/8/8/8/8/8/PPPPPPPP/8");
    U64 moves = generateWhitePawnMoves();
    U64 expected = 0x00000000FFFF0000ULL;
    test("White Pawn Initial 1", moves, expected);
    loadFEN("8/8/8/8/8/PPPPPPPP/8/8");
    moves = generateWhitePawnMoves();
    expected = 0x00000000FF000000ULL;
    test("White Pawn Initial 2", moves, expected);
    loadFEN("8/8/8/8/8/P6P/1PPPPPP1/8");
    moves = generateWhitePawnMoves();
    expected = 0x00000000FF7E0000ULL;
    test("White Pawn Initial 3", moves, expected);
}