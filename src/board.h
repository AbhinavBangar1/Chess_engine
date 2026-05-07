#pragma once
#include <cstdint>
#include <string>
using namespace std ;

using U64 = uint64_t ;

extern U64 WK , WQ , WR , WB , WN , WP ;
extern U64 BK , BQ , BR , BB , BN , BP ;

extern U64 whiteOcc , blackOcc , allOcc , enPassantBB ;

extern char board[8][8];
void initBitboards() ;
void clearBitboards();
void loadFEN(string s) ;
void test(string s , U64 g , U64 e) ;
void printBitboard(U64 bb);