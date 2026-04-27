#include <iostream>
#include <cstdint>
using namespace std;

using U64 = uint64_t;

U64 WP = 0ULL, WN = 0ULL, WB = 0ULL, WR = 0ULL, WQ = 0ULL, WK = 0ULL;
U64 BP = 0ULL, BN = 0ULL, BB = 0ULL, BR = 0ULL, BQ = 0ULL, BK = 0ULL;

U64 whiteOcc = 0ULL;
U64 blackOcc = 0ULL;
U64 allOcc   = 0ULL;

char board[8][8] = {
    {'r','n','b','q','k','b','n','r'},
    {'p','p','p','p','p','p','p','p'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','.','.','.','.'},
    {'.','.','.','.','B','.','.','.'},
    {'P','P','P','P','P','P','P','P'},
    {'R','N','.','Q','K','B','N','R'}
};

void initBitboards() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int sq = (7 - row) * 8 + col;
            U64 bit = 1ULL << sq;

            switch (board[row][col]) {
                case 'P': WP |= bit; break;
                case 'N': WN |= bit; break;
                case 'B': WB |= bit; break;
                case 'R': WR |= bit; break;
                case 'Q': WQ |= bit; break;
                case 'K': WK |= bit; break;

                case 'p': BP |= bit; break;
                case 'n': BN |= bit; break;
                case 'b': BB |= bit; break;
                case 'r': BR |= bit; break;
                case 'q': BQ |= bit; break;
                case 'k': BK |= bit; break;

                default: break;
            }
        }
    }

    whiteOcc = WP | WN | WB | WR | WQ | WK;
    blackOcc = BP | BN | BB | BR | BQ | BK;
    allOcc   = whiteOcc | blackOcc;
}

void printBitboard(U64 bb) {
    for (int rank = 7; rank >= 0; rank--){
        for (int file = 0; file < 8; file++) {
            int sq = rank * 8 + file;
            cout << ((bb >> sq) & 1ULL) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// int main() {
//     initBitboards();
//     cout << "White Pawns:\n";
//     printBitboard(WP);
//     cout << "Black Pawns:\n";
//     printBitboard(BP);
//     cout << "White Occupancy:\n";
//     printBitboard(whiteOcc);
//     cout << "Black Occupancy:\n";
//     printBitboard(blackOcc);
//     cout << "All Occupancy:\n";
//     printBitboard(allOcc);
//     return 0;
// }