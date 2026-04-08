#pragma once
#include <cstdint>

using U64 = uint64_t ;

extern U64 WK , WQ , WR , WB , WN , WP ;
extern U64 BK , BQ , BR , BB , BN , BP ;

extern U64 whiteOcc , blackOcc , allOcc ;

extern char board[8][8];
void initBitboards() ;
void printBitboard(U64 bb);