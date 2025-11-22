#include "stdio.h"
#include "defs.h"

void ResetBoard(Board_Struc *pos)
{
    int index = 0;

    for(index = 0 ; index < BRD_SQ_NUM ; index++)
    {
        pos->pieces[index] = OFFBOARD;
    }

    for (int index = 0; index < 64; index++)
    {
        pos->pieces[Sq64ToSq120[index]] = EMPTY;
    }

    for(index = 0 ; index<3 ; index++)
    {
        pos ->pceNum[index] = 0;
        pos ->bigPce[index] = 0;
        pos ->majPce[index] = 0;//Major Pieces are Kings ,  Bishops and all
        pos->minPce[index] = 0;//Minior Pices are like Pawns
        pos ->Pawns[index] = 0ULL;
    }

    pos->ply = 0;
    pos->hisply = 0;
    
    pos->CastlePerm = 0;



    
}