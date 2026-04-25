#include <iostream>
#include "board.h"

using U64 = uint64_t ;
using namespace std ;

const U64 notAFile = 0x7f7f7f7f7f7f7f7fULL ;
const U64 notHFile = 0xfefefefefefefefeULL ;
const U64 notABFile = 0xfcfcfcfcfcfcfcfcULL;
const U64 notGHFile = 0x3f3f3f3f3f3f3f3fULL;
const U64 whitePawnInitial = 0x000000000000FF00ULL ;
const U64 blackPawnInitial = 0x00FF000000000000ULL ;



U64 generateWhitePawnMoves(){
    U64 singlePush = (WP << 8) & ~allOcc ;
    U64 doublePush = ((singlePush & whitePawnInitial) << 16) & ~allOcc ;
    U64 leftCapture = (WP << 7) & notAFile & blackOcc ;
    U64 rightCapture = (WP << 9) & notHFile & blackOcc ;
    return singlePush | doublePush |leftCapture | rightCapture;
}

U64 generateBlackPawnMoves(){
    U64 singlePush = (BP >> 8) & ~allOcc ;
    U64 doublePush = ((singlePush & blackPawnInitial) << 8) & ~allOcc ;
    U64 leftCapture = (BP >> 9) & notAFile & whiteOcc ;
    U64 rightCapture = (BP >> 7) & notHFile & whiteOcc ;
    return singlePush | doublePush |leftCapture | rightCapture;
}

U64 generateWhiteKnightMoves(){
    U64 knightMoves = 0ULL;
    knightMoves |= (WN & notGHFile ) << 6 ;
    knightMoves |= (WN & notABFile ) << 10 ;
    knightMoves |= (WN & notAFile ) << 15 ;
    knightMoves |= (WN & notHFile ) << 17 ;

    knightMoves |= (WN & notGHFile ) >> 10 ;
    knightMoves |= (WN & notABFile ) >> 6 ;
    knightMoves |= (WN & notAFile ) >> 17 ;
    knightMoves |= (WN & notHFile ) >> 15 ;
    knightMoves = knightMoves & ~whiteOcc ; //allowing to capture the blacks (hehe :))   
    return knightMoves ;
}

// U64 generateWhiteBishopMoves(){

// }

U64 generateWhiteRookMoves(){
    U64 moves = 0ULL ;
    U64 rooks = WR ;
    while(rooks){
        int pos = __builtin_ctzll(rooks);
        rooks = rooks & (rooks - 1);
        int rank = pos / 8 ;
        int file = pos % 8 ;

        for (int i = rank+1 ; i < 8 ; i++){//top
            int t = i * 8 + file ;
            U64 to = 1ULL << t ;
            moves |= to ;
            if(to & allOcc) break ;
        }
        for(int i = rank-1 ; i >= 0 ; i --){//down
            int t = i * 8 + file ;
            U64 to = 1ULL << t ;
            moves|= to ;
            if(to & allOcc) break ;
        }
        for(int i = file + 1 ; i < 8 ; i++){//right
            int t = rank * 8 + i ;
            U64 to = 1ULL << t ;
            moves|= to ;
            if(to & allOcc) break ;
        }
        for(int i = file - 1 ; i >= 0 ; i--){//left
            int t = rank * 8 + i ;
            U64 to = 1ULL << t ;
            moves|= to ;
            if(to & allOcc) break ;
        }
    }
    moves = moves & ~whiteOcc ;
    return moves ;
}

int main(){
    initBitboards();
    cout << "Black moves : \n";
    printBitboard(generateBlackPawnMoves());
    cout << "White moves : \n";
    printBitboard(generateWhitePawnMoves());
    cout << "White knight moves : \n";
    printBitboard(generateWhiteKnightMoves());
    cout << "white rook moves : \n";
    printBitboard(generateWhiteRookMoves()) ;
    return 0 ;
}