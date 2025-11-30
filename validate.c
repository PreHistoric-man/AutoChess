#include "defs.h"

int SqOnBoard(const int sq)
{
    if(FileBrd[sq] == OFFBOARD)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int sideValid(const int side)
{
    if(side == WHITE || side == BLACK)
    {
        return 1;

    }
    else{
        return 0;
    }
}

int PieceRankValid(const int fr)
{
    return (fr>=0 && fr<=7)?1:0;
}

int PieceValidEmpty(const int pce) {
	return (pce > EMPTY && pce <= bK) ? 1 : 0;
}

int PieceValid(const int p)
{
    return (p>=wP && p<bK)? 1:0;
}

