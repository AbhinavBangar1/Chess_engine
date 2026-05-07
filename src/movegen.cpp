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
    U64 doublePush = ((WP & whitePawnInitial) << 8) & ~allOcc ;
    doublePush = (doublePush << 8) & ~allOcc ;
    U64 leftCapture = (WP << 7) & notAFile & blackOcc ;
    U64 rightCapture = (WP << 9) & notHFile & blackOcc ;
    U64 epLeft  = (WP << 7) & notAFile & enPassantBB;
    U64 epRight = (WP << 9) & notHFile & enPassantBB;
    return singlePush | doublePush |leftCapture | rightCapture | epLeft | epRight;
}

U64 generateBlackPawnMoves(){
    U64 singlePush = (BP >> 8) & ~allOcc ;
    U64 doublePush = ((BP & blackPawnInitial) >> 8) & ~allOcc ;
    doublePush = (doublePush >> 8) & ~allOcc ;
    U64 leftCapture = (BP >> 9) & notAFile & whiteOcc ;
    U64 rightCapture = (BP >> 7) & notHFile & whiteOcc ;
    U64 epLeft  = (BP >> 7) & notAFile & enPassantBB;
    U64 epRight = (BP >> 9) & notHFile & enPassantBB;
    return singlePush | doublePush |leftCapture | rightCapture | epLeft | epRight;
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

U64 generateBlackKnightMoves(){
    U64 knightMoves = 0ULL ;
    knightMoves |= (BN & notGHFile ) << 6 ;
    knightMoves |= (BN & notABFile ) << 10 ;
    knightMoves |= (BN & notAFile ) << 15 ;
    knightMoves |= (BN & notHFile ) << 17 ;
    knightMoves |= (BN & notGHFile ) >> 10 ;
    knightMoves |= (BN & notABFile ) >> 6 ;
    knightMoves |= (BN & notAFile ) >> 17 ;
    knightMoves |= (BN & notHFile ) >> 15 ;
    knightMoves = knightMoves & ~blackOcc ;    
    return knightMoves ;
}

U64 generateWhiteBishopMoves(){
    U64 moves = 0ULL ;
    U64 bishops = WB ;
    while(bishops){
        int pos = __builtin_ctzll(bishops) ;
        bishops = bishops & (bishops - 1) ;
        int rank = pos / 8 ;
        int file = pos % 8 ;

        for(int i = 1 ; i < 8 ; i++){
            if((file - i) < 0 || (rank + i) >= 8) break ;
            int top_right = (rank + i) * 8 + (file - i) ;
            if(top_right >= 0) {
                moves |= (1ULL <<top_right) ;
                if((1ULL << top_right) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank + i) >= 8 || (file + i) >= 8) break;
            int top_left = (rank + i) * 8 + (file + i ) ;
            if(top_left >= 0) {
                moves |= (1ULL <<top_left) ;
                if((1ULL << top_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file + i) >= 8 ) break ;
            int bottom_left = (rank - i) * 8 + (file + i ) ;
            if(bottom_left >= 0) {
                moves |= (1ULL <<bottom_left) ;
                if((1ULL <<bottom_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file - i) < 0 ) break ;
            int bottom_right = (rank - i) * 8 + (file - i ) ;
            if(bottom_right >= 0) {
                moves |= (1ULL <<bottom_right) ;
                if((1ULL <<bottom_right) & allOcc) break ;
            } 
        }
    }
    moves = moves & ~whiteOcc ;
    return moves ; 
}

U64 generateBlackBishopMoves(){
    U64 moves = 0ULL ;
    U64 bishops = BB ;
    while(bishops){
        int pos = __builtin_ctzll(bishops) ;
        bishops &= (bishops - 1);
        int rank = pos / 8 ;
        int file = pos % 8 ;
        for(int i = 1 ; i < 8 ; i++){
            if((file - i) < 0 || (rank + i) >= 8) break ;
            int top_right = (rank + i) * 8 + (file - i) ;
            if(top_right >= 0) {
                moves |= (1ULL <<top_right) ;
                if((1ULL << top_right) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank + i) >= 8 || (file + i) >= 8) break;
            int top_left = (rank + i) * 8 + (file + i ) ;
            if(top_left >= 0) {
                moves |= (1ULL <<top_left) ;
                if((1ULL << top_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file + i) >= 8 ) break ;
            int bottom_left = (rank - i) * 8 + (file + i ) ;
            if(bottom_left >= 0) {
                moves |= (1ULL <<bottom_left) ;
                if((1ULL <<bottom_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file - i) < 0 ) break ;
            int bottom_right = (rank - i) * 8 + (file - i ) ;
            if(bottom_right >= 0) {
                moves |= (1ULL <<bottom_right) ;
                if((1ULL <<bottom_right) & allOcc) break ;
            } 
        }
    }
    moves &= ~blackOcc ;
    return moves ;
}

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

U64 generateBlackRookMoves(){
    U64 moves = 0ULL ;
    U64 rooks = BR ;
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
    moves = moves & ~blackOcc ;
    return moves ;    
}

U64 generateWhiteQueenMoves(){
    U64 moves = 0ULL ;
    U64 queen = WQ ;
    while(queen){
        int pos = __builtin_ctzll(queen);
        queen = queen & (queen - 1);
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
        for(int i = 1 ; i < 8 ; i++){
            if((file - i) < 0 || (rank + i) >= 8) break ;
            int top_right = (rank + i) * 8 + (file - i) ;
            if(top_right >= 0) {
                moves |= (1ULL <<top_right) ;
                if((1ULL << top_right) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank + i) >= 8 || (file + i) >= 8) break;
            int top_left = (rank + i) * 8 + (file + i ) ;
            if(top_left >= 0) {
                moves |= (1ULL <<top_left) ;
                if((1ULL << top_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file + i) >= 8 ) break ;
            int bottom_left = (rank - i) * 8 + (file + i ) ;
            if(bottom_left >= 0) {
                moves |= (1ULL <<bottom_left) ;
                if((1ULL <<bottom_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file - i) < 0 ) break ;
            int bottom_right = (rank - i) * 8 + (file - i ) ;
            if(bottom_right >= 0) {
                moves |= (1ULL <<bottom_right) ;
                if((1ULL <<bottom_right) & allOcc) break ;
            } 
        }
    }
    moves = moves & ~whiteOcc ;
    return moves ;  
}

U64 generateBlackQueenMoves(){
    U64 moves = 0ULL ;
    U64 queen = BQ ;
    while(queen){
        int pos = __builtin_ctzll(queen);
        queen = queen & (queen - 1);
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
        for(int i = 1 ; i < 8 ; i++){
            if((file - i) < 0 || (rank + i) >= 8) break ;
            int top_right = (rank + i) * 8 + (file - i) ;
            if(top_right >= 0) {
                moves |= (1ULL <<top_right) ;
                if((1ULL << top_right) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank + i) >= 8 || (file + i) >= 8) break;
            int top_left = (rank + i) * 8 + (file + i ) ;
            if(top_left >= 0) {
                moves |= (1ULL <<top_left) ;
                if((1ULL << top_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file + i) >= 8 ) break ;
            int bottom_left = (rank - i) * 8 + (file + i ) ;
            if(bottom_left >= 0) {
                moves |= (1ULL <<bottom_left) ;
                if((1ULL <<bottom_left) & allOcc) break ;
            } 
        }
        for(int i = 1 ; i < 8 ; i++){
            if((rank - i) < 0 || (file - i) < 0 ) break ;
            int bottom_right = (rank - i) * 8 + (file - i ) ;
            if(bottom_right >= 0) {
                moves |= (1ULL <<bottom_right) ;
                if((1ULL <<bottom_right) & allOcc) break ;
            } 
        }
    }
    moves = moves & ~blackOcc ;
    return moves ;  
}

U64 generateWhiteKingMoves(){
    U64 moves = 0ULL ;
    initBitboards();
    U64 up = (WK << 8) & ~allOcc ;
    cout << "up : \n";
    printBitboard(up) ;
    U64 left = ((WK & notAFile) << 1) & ~allOcc ;
    cout << "left : \n";
    printBitboard(left) ;
    U64 right = (WK >> 1) & notHFile & ~allOcc ;
    cout << "right : \n";
    printBitboard(right) ;
    U64 down = (WK >> 8) & ~allOcc ;
    cout << "down : \n";
    printBitboard(down) ;
    U64 top_right = (WK << 9 ) &~allOcc & 0xfefefefefefefefeULL;
    cout << "top_right : \n";
    printBitboard(top_right) ;
    U64 top_left = (WK << 7 ) &~allOcc & 0x7f7f7f7f7f7f7f7fULL ;
    cout << "top_left : \n";
    printBitboard(top_left) ;
    U64 bottom_right = (WK >> 7 ) &~allOcc & 0xfefefefefefefefeULL;
    cout << "bottom_right : \n";
    printBitboard(bottom_right) ;
    U64 bottom_left = (WK >> 9 ) &~allOcc & 0x7f7f7f7f7f7f7f7fULL;
    cout << "bottom_left : \n";
    printBitboard(bottom_left) ;
    moves = up | left | right | down | top_right | top_left | bottom_left | bottom_right;
    cout << "moves_right : \n";
    printBitboard(moves) ;
    U64 checks = generateBlackRookMoves() | generateBlackBishopMoves() | 
                 generateBlackKnightMoves() | generateBlackPawnMoves() | generateBlackQueenMoves() ;
    cout << "Checks : \n";
    printBitboard(checks) ;
    moves = moves & ~checks ;
    moves = moves & ~whiteOcc ;
    return moves ;
}

U64 generateBlackKingMoves(){
    U64 moves = 0ULL ;
    initBitboards();
    U64 up = (BK << 8) & ~allOcc ;
    cout << "up : \n";
    printBitboard(up) ;
    U64 left = ((BK & notAFile) << 1) & ~allOcc ;
    cout << "left : \n";
    printBitboard(left) ;
    U64 right = (BK >> 1) & notHFile & ~allOcc ;
    cout << "right : \n";
    printBitboard(right) ;
    U64 down = (BK >> 8) & ~allOcc ;
    cout << "down : \n";
    printBitboard(down) ;
    U64 top_right = (BK << 9 ) &~allOcc & 0xfefefefefefefefeULL;
    cout << "top_right : \n";
    printBitboard(top_right) ;
    U64 top_left = (BK << 7 ) &~allOcc & 0x7f7f7f7f7f7f7f7fULL ;
    cout << "top_left : \n";
    printBitboard(top_left) ;
    U64 bottom_right = (BK >> 7 ) &~allOcc & 0xfefefefefefefefeULL;
    cout << "bottom_right : \n";
    printBitboard(bottom_right) ;
    U64 bottom_left = (BK >> 9 ) &~allOcc & 0x7f7f7f7f7f7f7f7fULL;
    cout << "bottom_left : \n";
    printBitboard(bottom_left) ;
    moves = up | left | right | down | top_right | top_left | bottom_left | bottom_right;
    cout << "moves_right : \n";
    printBitboard(moves) ;
    U64 checks = generateWhiteRookMoves() | generateWhiteBishopMoves() | 
                generateWhiteKnightMoves() | generateWhitePawnMoves() | generateWhiteQueenMoves() ;
    cout << "Checks : \n";
    printBitboard(checks) ;
    moves = moves & ~checks ;
    moves = moves & ~blackOcc ;
    return moves ;
}

// int main(){
//     initBitboards();
//     cout << "Black king moves : \n";
//     printBitboard(generateBlackKingMoves()) ;
//     // cout << "Black queen moves : \n";
//     // printBitboard(generateBlackQueenMoves()) ;
//     return 0 ;
// }