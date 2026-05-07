#include "movegen.h"
#include "board.h"

int main(){
    loadFEN("8/8/8/8/8/8/PPPPPPPP/8");
    U64 moves = generateWhitePawnMoves();
    U64 expected = 0x00000000FFFF0000ULL;
    test("White Pawn Initial", moves, expected);
}