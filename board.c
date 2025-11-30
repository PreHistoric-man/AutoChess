#include "stdio.h"
#include "defs.h"


//making a piece list and updating as the game progresses
void InitUpdateMaterial(Board_Struc *pos) {

	int piece,sq,index,colour;

	for(index = 0; index < BRD_SQ_NUM; ++index) {
		sq = index;
		piece = pos->pieces[index];

		if(piece!=OFFBOARD && piece!= EMPTY) {
			colour = PieceCol[piece];

		    if(PieceBig[piece] == TRUE)pos->bigPce[colour]++;
		    if(PieceMin[piece] == TRUE)pos->minPce[colour]++;
		    if(PieceMaj[piece] == TRUE)pos->majPce[colour]++;

			pos->material[colour] += PieceVal[piece];

			ASSERT(pos->pceNum[piece] < 10 && pos->pceNum[piece] >= 0);

			pos->piecelist[piece][pos->pceNum[piece]] = sq;
			pos->pceNum[piece]++;


			if(piece==wK) pos->KingSq[WHITE] = sq;
			if(piece==bK) pos->KingSq[BLACK] = sq;

			if(piece==wP) {
				MKBIT(pos->Pawns[WHITE],Sq120toSq64[sq]);
				MKBIT(pos->Pawns[BOTH],Sq120toSq64[sq]);
			} else if(piece==bP) {
				MKBIT(pos->Pawns[BLACK],Sq120toSq64[sq]);
				MKBIT(pos->Pawns[BOTH],Sq120toSq64[sq]);
			}
		}
	}
}


int CheckBoard(Board_Struc *pos) {

	int t_pceNum[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int t_bigPce[2] = { 0, 0};
	int t_majPce[2] = { 0, 0};
	int t_minPce[2] = { 0, 0};
	int t_material[2] = { 0, 0};

	int sq64,t_piece,t_pce_num,sq120,colour,pcount;

	U64 t_pawns[3] = {0ULL, 0ULL, 0ULL};

	t_pawns[WHITE] = pos->Pawns[WHITE];
	t_pawns[BLACK] = pos->Pawns[BLACK];
	t_pawns[BOTH] = pos->Pawns[BOTH];

	// check piece lists
	for(t_piece = wP; t_piece <= bK; ++t_piece) {
		for(t_pce_num = 0; t_pce_num < pos->pceNum[t_piece]; ++t_pce_num) {
			sq120 = pos->piecelist[t_piece][t_pce_num];
			ASSERT(pos->pieces[sq120]==t_piece);
		}
	}

	// check piece count and other counters
	for(sq64 = 0; sq64 < 64; ++sq64) {
		sq120 = SQ120(sq64);
		t_piece = pos->pieces[sq120];
		t_pceNum[t_piece]++;
		colour = PieceCol[t_piece];
		if( PieceBig[t_piece] == TRUE) t_bigPce[colour]++;
		if( PieceMin[t_piece] == TRUE) t_minPce[colour]++;
		if( PieceMaj[t_piece] == TRUE) t_majPce[colour]++;

		t_material[colour] += PieceVal[t_piece];
	}

	for(t_piece = wP; t_piece <= bK; ++t_piece) 
    {
		ASSERT(t_pceNum[t_piece]=pos->pceNum[t_piece]);
	}

	// check bitboards count
	pcount = CNT(t_pawns[BLACK]);
	ASSERT(pcount = pos->pceNum[bP]);
	pcount = CNT(t_pawns[BOTH]);
	ASSERT(pcount = (pos->pceNum[bP] + pos->pceNum[wP]));

	// check bitboards squares
	while(t_pawns[WHITE]) {
		sq64 = PopBit(&t_pawns[WHITE]);
		ASSERT(pos->pieces[Sq64ToSq120[sq64]] = wP);
	}

	while(t_pawns[BLACK]) {
		sq64 = PopBit(&t_pawns[BLACK]);
		ASSERT(pos->pieces[Sq64ToSq120[sq64]] = bP);
	}

	while(t_pawns[BOTH]) {
		sq64 = PopBit(&t_pawns[BOTH]);
		ASSERT((pos->pieces[Sq64ToSq120[sq64]] = bP) || (pos->pieces[Sq64ToSq120[sq64]] = wP));
	}

	ASSERT(t_material[WHITE]==pos->material[WHITE] && t_material[BLACK]==pos->material[BLACK]);
	ASSERT(t_minPce[WHITE]=pos->minPce[WHITE] && t_minPce[BLACK]==pos->minPce[BLACK]);
	ASSERT(t_majPce[WHITE]=pos->majPce[WHITE] && t_majPce[BLACK]==pos->majPce[BLACK]);
	ASSERT(t_bigPce[WHITE]=pos->bigPce[WHITE] && t_bigPce[BLACK]==pos->bigPce[BLACK]);

	ASSERT(pos->side==WHITE || pos->side==BLACK);
    //look into problem
	//ASSERT(InitGetHashKey(pos)==pos->poskey);


	ASSERT(pos->pieces[pos->KingSq[WHITE]] = wK);
	ASSERT(pos->pieces[pos->KingSq[BLACK]] = bK);

	ASSERT(pos->CastlePerm >= 0 && pos->CastlePerm <= 15);

	return TRUE;
}



int FileBrd[10];
int RankBrd[10];

void RankandFileFunc()
{
    
    int rank , file ,sq, pieces[BRD_SQ_NUM];
    rank = 0;
    file = 0;
    sq = A1;
    for(int index = 0 ; index < BRD_SQ_NUM ; index++)
    {
        FileBrd[index] = OFFBOARD;
        RankBrd[index] = OFFBOARD;
    }
    for(rank = RANK1 ; rank<=RANK8 ; rank++)
    {
        for(file = FILE_A ; file<=FILE_H ; file++)
        {
            sq = FR2SQ(file,rank);
            FileBrd[sq] = file;
            RankBrd[sq] = rank;
        }
    }
}

//used to find the fen notation of a chess positions which is used to communicate with GUI
int fenfunc(char *fen , Board_Struc *pos)
{
    ASSERT(fen !=NULL);
    ASSERT(pos !=NULL);

    int rank = RANK8;
    int file = FILE_A;
    int count = 0;
    int sq64 = 0;
    int sq120 = 0;
    int piece = 0;

    ResetBoard(pos);


    while ((rank >= RANK1) && *fen)
    {
        count = 1;
        switch (*fen)
        {
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'B': piece = wB; break;
            case 'K': piece = wK; break;
            case 'Q': piece = wQ; break;


            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            piece = EMPTY;
            count = *fen  - '0';
            break;

            case '/':
            case ' ':
            rank--;
            file = FILE_A;
            fen++;
            continue;

            default:
                printf("FEN ERROR");
                break;
        }

        for(int i= 0 ; i<count;i++)
        {
            sq64 = rank*8 + file;
            sq120 = Sq64ToSq120[sq64];
            if(piece != EMPTY)
            {
                pos->pieces[sq120] = piece;
            }
            file++;
        }
        fen++;
    }

    ASSERT(*fen == 'w' || *fen == 'b');
    pos->side = (*fen == 'w')?WHITE:BLACK;
    fen += 2;

    for(int i = 0 ; i<4 ; i++)
    {
        if(*fen ==' ')
        {
            fen++;
            break;
        }
        switch (*fen)
        {
            case 'q':pos->CastlePerm |= BQC; break;
            case 'k':pos->CastlePerm |= BKC; break;
            case 'Q':pos->CastlePerm |= WQC; break;
            case 'K':pos->CastlePerm |= WKC; break;
            default : printf("Castle Error"); break;

        }
        fen++;
    }
    fen++;

    ASSERT(pos ->CastlePerm >=0 && pos->CastlePerm <=15);

    if(*fen != '-')
    {
        file = fen[0] - 'a';
        rank =  fen[1] - '1';
        //ASSERT(file>FILE_A && file < FILE_H);
        //ASSERT(rank>RANK1 && rank < RANK8);
        pos->enPas = FR2SQ(file,rank);
    }

    pos->poskey = InitGetHashKey(pos);

    InitUpdateMaterial(pos);
    return 0 ;



}

void PrintBoard(Board_Struc *pos)
{
    int sq , file , rank , piece;

    printf("The Board is\n");

    for(rank = RANK8 ; rank>=RANK1 ; rank--)
    {
        printf("%d " , rank+1);
        for(file = FILE_A ; file <= FILE_H ; file++)
        {
            sq = FR2SQ(file,rank);
            piece = pos->pieces[sq];
            printf("%3c", PceChar[piece]);
        }
        printf("\n");
    }

    printf("\n  ");

    for(file = FILE_A ; file<=FILE_H;file++)
    {
        printf("%3c", 'a'+file);
    }

    printf("\nside:%c\n" , SideChar[pos->side]);
    printf("enPas:%d\n" , pos->enPas);
    printf("castle: %c%c%c%c\n" ,
        pos->CastlePerm&WKC?'K':'-',
        pos->CastlePerm&WQC?'Q':'-',
        pos->CastlePerm&BKC?'k':'-',
        pos->CastlePerm&BQC?'q' : '-');
    printf("PosKey = %11f" , pos->poskey);
}


int ResetBoard(Board_Struc *pos)
{
    int index = 0;

    for(index = 0 ; index < BRD_SQ_NUM ; index++)
    {
        pos->pieces[index] = OFFBOARD;
    }

    for (int index = 0; index < 64; index++)
    {
        pos->pieces[Sq120toSq64[index]] = EMPTY;
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

    for(index = 0 ; index<13;index++)
    {
        pos->pceNum[index] = 0;
    }

    pos->KingSq[0] = pos->KingSq[1] = NO_SQ;

    pos->poskey = 0ULL;

}