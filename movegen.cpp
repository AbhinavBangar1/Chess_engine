#include <iostream>
#include "board.h"

using U64 = uint64_t ;
using namespace std ;

const U64 aFile = 0x7f7f7f7f7f7f7f7fULL ;
const U64 hFile = 0xfefefefefefefefeULL ;
const U64 whitePawnInitial = 0x000000000000FF00ULL ;
const U64 blackPawnInitial = 0x00FF000000000000ULL ;

U64 generateWhitePawnMoves(){
    U64 singlePush = (WP << 8) & ~allOcc ;
    U64 doublePush = ((singlePush & whitePawnInitial) << 8) & ~allOcc ;
    U64 leftCapture = (WP << 9) & aFile & blackOcc ;
    U64 rightCapture = (WP << 7) & hFile & blackOcc ;
    return singlePush | doublePush |leftCapture | rightCapture;
}

U64 generateBlackPawnMoves(){
    U64 singlePush = (BP >> 8) & ~allOcc ;
    U64 doublePush = ((singlePush & blackPawnInitial) << 8) & ~allOcc ;
    U64 leftCapture = (BP >> 9) & aFile & whiteOcc ;
    U64 rightCapture = (BP >> 7) & hFile & whiteOcc ;
    return singlePush | doublePush |leftCapture | rightCapture;
}
