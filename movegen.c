#include "stdio.h"
#include "defs.h"

#define MOVE(f,t,ca,pro,fl) ( (f) | ((t) << 7) | ( (ca) << 14 ) | ( (pro) << 20 ) | (fl))
#define SQOFFBOARD(sq) (FileBrd[(sq)]==OFFBOARD)

/*Just adding a normal move*/
void AddQuietMove(Board_Struc *pos, int move ,S_MOVELIST  *list)
{
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

/*Capture moves func*/
void AddCaptureMove(Board_Struc *pos,int move ,S_MOVELIST  *list)
{
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

/*Enpas Move*/
void AddEnPasMove(Board_Struc *pos,int move ,S_MOVELIST  *list)
{
    list->moves[list->count].move = move;
    list->moves[list->count].score = 0;
    list->count++;
}

static void WhitePawnCapture(Board_Struc *pos,  int from,  int to,  int cap, S_MOVELIST *list) 
{
	
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));

	if(RankBrd[from] == RANK7)
    {
		AddCaptureMove(pos, MOVE(from,to,cap,wQ,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,wR,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,wB,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,wN,0), list);
	} 
	else 
    {
		AddCaptureMove(pos, MOVE(from,to,cap,EMPTY,0), list);
	}
}

static void WhitePawnEmptyMove(Board_Struc *pos , const int from , const  int to , S_MOVELIST *list)
{
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));

    if(RankBrd[from] == RANK7)
    {
        AddCaptureMove(pos , MOVE(from , to , EMPTY , wQ , 0) , list);
        AddCaptureMove(pos , MOVE(from , to , EMPTY , wR , 0) , list);
        AddCaptureMove(pos , MOVE(from , to , EMPTY , wB , 0) , list);
        AddCaptureMove(pos , MOVE(from , to , EMPTY , wN , 0) , list);
    }
    else
    {
        AddQuietMove(pos , MOVE(from,to,EMPTY,EMPTY,0) , list);
    }
}

static void AddBlackPawnCapMove(  Board_Struc *pos, const int from, const int to, const int cap, S_MOVELIST *list ) {

	ASSERT(PieceValidEmpty(cap));
	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));

	if(RankBrd[from] == RANK2) {
		AddCaptureMove(pos, MOVE(from,to,cap,bQ,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,bR,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,bB,0), list);
		AddCaptureMove(pos, MOVE(from,to,cap,bN,0), list);
	} else {
		AddCaptureMove(pos, MOVE(from,to,cap,EMPTY,0), list);
	}
}

static void AddBlackPawnMove( Board_Struc *pos,  int from,  int to, S_MOVELIST *list ) {

	ASSERT(SqOnBoard(from));
	ASSERT(SqOnBoard(to));
	ASSERT(CheckBoard(pos));

	if(RankBrd[from] == RANK2) {
		AddQuietMove(pos, MOVE(from,to,EMPTY,bQ,0), list);
		AddQuietMove(pos, MOVE(from,to,EMPTY,bR,0), list);
		AddQuietMove(pos, MOVE(from,to,EMPTY,bB,0), list);
		AddQuietMove(pos, MOVE(from,to,EMPTY,bN,0), list);
	} else {
		AddQuietMove(pos, MOVE(from,to,EMPTY,EMPTY,0), list);
	}
}



void GenerateAllMoves(Board_Struc *pos , S_MOVELIST *list)
{
    list->count =0;
    int index = 0;
    int dir = 0;
    int sq = 0 ; 
    int t_sq = 0;
    int pce = EMPTY;
    int side = pos->side;
    int pceindex = 0;
    int pceNum = 0;

	if(side == WHITE)
	{
		for (pceNum = 0; pceNum < pos->pceNum[wP];pceNum++)
		{
			sq = pos->piecelist[wP][pceNum];
			ASSERT(SqOnBoard(sq));
		}

		if(pos->pieces[sq+10] == EMPTY)
		{
			WhitePawnEmptyMove(pos , sq , sq+10 , list);
			if(RankBrd[sq] == RANK2 && pos->pieces[sq+20] == EMPTY)
			{
				AddQuietMove(pos , MOVE(sq,sq+10 , EMPTY , EMPTY , MFLAGPS) , list);
			}
		}

		if(!SQOFFBOARD(sq+9) && PieceCol[pos->pieces[sq+9]])
		{
			WhitePawnCapture(pos , sq , sq+9,pos->pieces[sq+9],list);
		}
		if(!SQOFFBOARD(sq+11) && PieceCol[pos->pieces[sq+11]]);
		{
			WhitePawnCapture(pos , sq , sq+11 , pos->pieces[sq+11],list);
		}

		if(pos->enPas != NO_SQ)
		{
			if(sq+9 == pos-> enPas)
			{
				AddEnPasMove(pos , MOVE(sq,sq+9,EMPTY , EMPTY,MFLAGEP)  , list);
			}
			if(sq+11 == pos->enPas)
			{
				AddEnPasMove(pos , MOVE(sq,sq+11,EMPTY,EMPTY,MFLAGEP)  , list);
			}
		}

		} 
		else 		
		{

		for(pceNum = 0; pceNum < pos->pceNum[bP]; ++pceNum) {
			sq = pos->piecelist[bP][pceNum];
			ASSERT(SqOnBoard(sq));

			if(pos->pieces[sq - 10] == EMPTY) {
				AddBlackPawnMove(pos, sq, sq-10, list);
				if(RankBrd[sq] == RANK7 && pos->pieces[sq - 20] == EMPTY) {
					AddQuietMove(pos, MOVE(sq,(sq-20),EMPTY,EMPTY,MFLAGPS),list);
				}
			}

			if(!SQOFFBOARD(sq - 9) && PieceCol[pos->pieces[sq - 9]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-9, pos->pieces[sq - 9], list);
			}

			if(!SQOFFBOARD(sq - 11) && PieceCol[pos->pieces[sq - 11]] == WHITE) {
				AddBlackPawnCapMove(pos, sq, sq-11, pos->pieces[sq - 11], list);
			}
			if(pos->enPas != NO_SQ) {
				if(sq - 9 == pos->enPas) {
					AddEnPasMove(pos, MOVE(sq,sq - 9,EMPTY,EMPTY,MFLAGEP), list);
				}
				if(sq - 11 == pos->enPas) 
				{
					AddEnPasMove(pos, MOVE(sq,sq - 11,EMPTY,EMPTY,MFLAGEP), list);
				}
			}
		}
	}
}



