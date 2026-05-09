#include<board.h>
#include<movegen.h>

using namespace std ;
using U64 = uint64_t ;

typedef struct move{
    int from ;
    int to ;
    bool capture ;
    bool promotion ;
    int piece ;
};


