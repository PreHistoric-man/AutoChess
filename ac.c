#include <stdio.h>
#include "stdlib.h"
#include "defs.h"
#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPP1PPPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "r7/3k4/8/8/4K3/8/8/7R b - - 0 1 "
#define FEN4 "8/3k4/8/8/4K3/8/8/8 b - - 0 1"
#define FEN5 "r7/8/8/8/8/8/8/7R b - - 0 1"







int main()
{
    AllInit();
    Board_Struc board[1];
    fenfunc(FEN2 , board);

    S_MOVELIST list[1];

    GenerateAllMoves(board , list);
    PrintMoveList(list);

    return 0 ;
}