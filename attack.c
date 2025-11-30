#include "stdio.h"
#include "defs.h"

/*for a particular square sq the if any piece is present in sq+Dir[i] 
then it is used to know that the piece is attacking it*/

const int KnDir[8] = { -8, -19,	-21, -12, 8, 19, 21, 12};
const int RkDir[4] = { -1, -10,	1, 10 };
const int BiDir[4] = { -9, -11, 11, 9 };
const int KiDir[8] = { -1, -10,	1, 10, -9, -11, 11, 9 };




int SqAttacked(const int sq , const int side , const Board_Struc *pos)
{
    int pce,dir,t_sq,index;

    ASSERT(SqOnBoard(sq))
    ASSERT(sideValid(side))
    //pawns/soliders 
    if(side == WHITE)
    {
        if(pos->pieces[sq-11] == wP || pos->pieces[sq-9] == wP)
        {
            return TRUE;
        }
    }
    else
    {
        if(pos->pieces[sq+11] == bP || pos->pieces[sq+9] == bP)
        {
            return TRUE;
        }
    }
    
        /*KNIGHT OR HORSE*/

    for(index = 0 ; index < 8 ; index++)
    {
        pce = pos->pieces[sq+KnDir[index]];
        if( pce != OFFBOARD && IsKn(pce) && PieceCol[pce] == side)
        {
            return TRUE;
        }
    }
    /*for Rooks OR ELEPHANTS and the queens*/
    for(index = 0; index < 4; ++index) 
    {		
		dir = RkDir[index];
		t_sq = sq + dir;
		
		pce = pos->pieces[t_sq];
		
		while(pce != OFFBOARD) {
			if(pce != EMPTY) {
				if(IsRQ(pce) && PieceCol[pce] == side) {
					return TRUE;
				}
				break;
			}
			t_sq += dir;
			pce = pos->pieces[t_sq];
		}
	}    
       /*King Pieces*/
        for(index = 0 ; index<8 ; index++)
        {
            pce = pos->pieces[sq+PieceKing[index]];
            if( pce != OFFBOARD && PieceKing[sq] && PieceCol[pce] == side)
            {
                return TRUE;
            }
        }
        return FALSE;
    
}