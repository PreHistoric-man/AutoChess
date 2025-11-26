#include <stdio.h>
#include "stdlib.h"
#include "defs.h"
#define FEN1 "rnbqkbnr/pppppppp/8/8/4P3/8/PPP1PPPP/RNBQKBNR b KQkq e3 0 1"
#define FEN2 "rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"
#define FEN3 "r7/3k4/8/8/4K3/8/8/7R b - - 0 1 "
#define FEN4 "8/3k4/8/8/4K3/8/8/8 b - - 0 1"
#define FEN5 "r7/8/8/8/8/8/8/7R b - - 0 1"

void PrintAttackSquares(int side , Board_Struc *pos)
{
    int index = 0;
    int rank = 0;
    int file = 0;
    int sq = 0;

    for(rank = RANK8 ; rank >=RANK1 ; --rank)
    {
        for(file = FILE_A ;file <=FILE_H ; file++)
        {
            sq = FR2SQ(file,rank);
            if(SqAttacked(sq , side , pos) == TRUE)
            {
                printf("X");
            }
            else{
                printf("-");
            }
        }
        printf("\n");
    }
    printf("\n\n ");
}



int main()
{
    AllInit();
    Board_Struc board[1];
    fenfunc(FEN5 ,board);
    printf("\n\n");
    PrintAttackSquares(WHITE , board);

    printf("Black piece\n");
    PrintAttackSquares(BLACK , board);

    
    return 0 ;
}