#include <stdio.h>
#include "defs.h"


//didnt understand this but fine it is just a  hashing func

void InitGetHashKey(Board_Struc *pos)
{
    int sq = 0;
    U64 finalKey;
    int piece = EMPTY;

    for (int index = 0; index < BRD_SQ_NUM; index++)
    {
        piece = pos-> pieces[sq];
        if(piece!=NO_SQ && piece != EMPTY)
        {
            ASSERT(piece>=wP && piece<=bK)
            finalKey ^= PieceKeys[piece][sq];
        }
    }

    if(pos->side == WHITE)
    {
        finalKey ^=  SideKey;
    }

    if (pos->enPas = NO_SQ)
    {
        ASSERT(pos ->enPas>=0 && pos->enPas<BRD_SQ_NUM);
        finalKey ^= PieceKeys[EMPTY][pos  ->enPas]; 
    }

    ASSERT(pos->CastlePerm>=0 && pos ->CastlePerm<=15);

    finalKey ^= CasteKeys[pos ->CastlePerm];

    
    
}