#include<board.h>
#include<movegen.h>

using namespace std ;
using U64 = uint64_t ;

enum pieces{
    Bpawn , Bbishop , Bknight , Brook , Bqueen , Bking, // brook hehe :))
    Wpawn , Wbishop , Wknight , Wrook , Wqueen , Wking
};

typedef struct move{
    int from ; // from which square
    int to ; // to which square
    bool capture ; // true if the move resulted in a capture
    bool promotion ; // true if the move resulted in a promotion
    int piece ; // the move belogs to which piece
    int capturedPiece ; // if capture , then which piece captured
    int promotedPiece ; // if promoted , then promoted to which piece
};

// Helper Function
void updateOcc(){
    whiteOcc = WP | WN | WB | WR | WQ | WK ;
    blackOcc = BP | BN | BB | BR | BQ | BK ;
    allOcc = whiteOcc | blackOcc ;
}

// to remove the captured piece
void removeCaptured(U64 toBB , int capturedPiece){
    switch(capturedPiece){
        case Bpawn:   BP &= ~toBB; break;
        case Bbishop: BB &= ~toBB; break;
        case Bknight: BN &= ~toBB; break;
        case Brook:   BR &= ~toBB; break;
        case Bqueen:  BQ &= ~toBB; break;
        case Bking:   BK &= ~toBB; break;

        case Wpawn:   WP &= ~toBB; break;
        case Wbishop: WB &= ~toBB; break;
        case Wknight: WN &= ~toBB; break;
        case Wrook:   WR &= ~toBB; break;
        case Wqueen:  WQ &= ~toBB; break;
        case Wking:   WK &= ~toBB; break;
    }
}

// to restore the captured piece
void restoreCaptured(U64 toBB , int capturedPiece){
    switch (capturedPiece){
        case Bpawn : BP |= toBB ; break ;
        case Bbishop : BB |= toBB ; break ;
        case Bknight : BN |= toBB ; break ;
        case Brook : BR |= toBB ; break ;
        case Bqueen : BQ |= toBB ; break ;
        case Bking : BK |= toBB ; break ;
        
        case Wpawn : WP |= toBB ; break ;
        case Wbishop : WB |= toBB ; break ;
        case Wknight : WN |= toBB ; break ;
        case Wrook : WR |= toBB ; break ;
        case Wqueen : WQ |= toBB ; break ;
        case Wking : WK |= toBB ; break ;
    }
}


void makeMove(struct move m){
    U64 fromBB = 1ULL << m.from ;
    U64 toBB = 1ULL << m.to ;
    bool blackMove = (m.piece <= Bking) ;
    if(m.capture){
        removeCaptured(toBB , m.capturedPiece);
    }
    switch(m.piece){
        case Bpawn :
            BP &= ~fromBB ;
            BP |= toBB ;
            break ;

        case Bbishop :
            BB &= ~fromBB ;
            BB |= toBB ;
            break ;

        case Bknight :
            BN &= ~fromBB ;
            BN |= toBB ;
            break ;

        case Brook :
            BR &= ~fromBB ;
            BR |= toBB ;
            break ;

        case Bqueen :
            BQ &= ~fromBB ;
            BQ |= toBB ;
            break ;

        case Bking :
            BK &= ~fromBB ;
            BK |= toBB ;
            break ;

        case Wpawn :
            WP &= ~fromBB ;
            WP |= toBB ;
            break ;

        case Wbishop :
            WB &= ~fromBB ;
            WB |= toBB ;
            break ;

        case Wknight :
            WN &= ~fromBB ;
            WN |= toBB ;
            break ;

        case Wrook :
            WR &= ~fromBB ;
            WR |= toBB ;
            break ;

        case Wqueen :
            WQ &= ~fromBB ;
            WQ |= toBB ;
            break ;

        case Wking :
            WK &= ~fromBB ;
            WK |= toBB ;
            break ;
    }
    updateOcc();
}


void unmakeMove(struct move m){
    U64 fromBB = 1ULL << m.from ;
    U64 toBB = 1ULL << m.to ;
    switch (m.piece){
        case Bpawn :
            BP &= ~toBB ;
            BP |= fromBB ;
            break ;

        case Bbishop :
            BB &= ~toBB ;
            BB |= fromBB ;
            break ;

        case Bknight :
            BN &= ~toBB ;
            BN |= fromBB ;
            break ;

        case Brook :
            BR &= ~toBB ;
            BR |= fromBB ;
            break ;

        case Bqueen :
            BQ &= ~toBB ;
            BQ |= fromBB ;
            break ;

        case Bking :
            BK &= ~toBB ;
            BK |= fromBB ;
            break ;

        case Wpawn :
            WP &= ~toBB ;
            WP |= fromBB ;
            break ;

        case Wbishop :
            WB &= ~toBB ;
            WB |= fromBB ;
            break ;

        case Wknight :
            WN &= ~toBB ;
            WN |= fromBB ;
            break ;

        case Wrook :
            WR &= ~toBB ;
            WR |= fromBB ;
            break ;

        case Wqueen :
            WQ &= ~toBB ;
            WQ |= fromBB ;
            break ;

        case Wking :
            WK &= ~toBB ;
            WK |= fromBB ;
            break ;
    }
    if(m.capture){
        restoreCaptured(toBB , m.capturedPiece);
    }
    updateOcc() ;
}