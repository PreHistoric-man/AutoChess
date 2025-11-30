#include "stdio.h"
#include "defs.h"

/*Has All the input and output functionality*/

/*this is used to input the sqs of the pieces like b4 that is b4 square a pawn is there*/

char *prtStr(const int move)
{
    static char Sqstr[3];
    int file = FileBrd[move];
    int rank = RankBrd[move];

    sprintf(Sqstr , "%c%c" , ('a'+file) , ('1'+rank));
    return Sqstr;
}

char *PrMove(const int move)
{
    char pchar; 
    static char MvStr[3];
    int ff = FROMSQ(FileBrd[move]);
    int ft = FROMSQ(FileBrd[move]);
    int rf = FROMSQ(RankBrd[move]);
    int rt = FROMSQ(RankBrd[move]);

    int promoted  = PROMOTED(move);

    if(promoted)
    {
        pchar = 'q';
    
    
        if(IsKn(promoted))
        {
            pchar = 'n';
        }
        else if(IsBQ(promoted) == TRUE && IsRQ(promoted) != FALSE)
        {
            pchar = 'b';
        }
        else if(IsRQ(promoted) == TRUE && IsBQ(promoted) != TRUE)
        {
            pchar = 'r';
        }   

    sprintf(MvStr, "%c%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt), pchar);
}
    else
    {
        sprintf(MvStr, "%c%c%c%c", ('a'+ff), ('1'+rf), ('a'+ft), ('1'+rt));
    }

    return MvStr;

}

void PrintMoveList(const S_MOVELIST *list)
{
    int index = 0;
    int score = 0;
    int move = 0;
    
    for(index =0 ; index<list->count ; index++)
    {
        move = list->moves[index].move;
        score = list->moves[index].score;

        printf("Move:%d>%s (score:%d)\n" ,index+1, PrMove(move),score);
    }
    printf("MoveList Total : %d Move:\n\n" , list->count);

}


