


//didnt understand this but fine it is just a  hashing func

#include "stdio.h"
#include "defs.h"

U64 InitGetHashKey(Board_Struc *pos) {

	int sq = 0;
	U64 finalKey = 0;
	int piece = EMPTY;
	
	// pieces
	for(sq = 0; sq < BRD_SQ_NUM; ++sq) {
		piece = pos->pieces[sq];
		if(piece!=NO_SQ && piece!=EMPTY && piece != OFFBOARD) 
        {
			ASSERT(piece>=wP && piece<=bK);
			finalKey ^= PieceKeys[piece][sq];
		}		
	}
	
	if(pos->side == WHITE) 
	{
		finalKey ^= SideKey;
	}
		
	if(pos->enPas != NO_SQ) {
		//ASSERT(pos->enPas>=0 && pos->enPas<BRD_SQ_NUM);
		finalKey ^= PieceKeys[EMPTY][pos->enPas];
	}
	
	ASSERT(pos->CastlePerm>=0 && pos->CastlePerm<=15);
	
	finalKey ^= CasteKeys[pos->CastlePerm];
	
	return finalKey;
}