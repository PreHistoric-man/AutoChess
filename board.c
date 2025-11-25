#include "stdio.h"
#include "defs.h"


//making a piece list and updating as the game progresses
void InitUpdateMaterial(Board_Struc *pos)
{
    int sq , color , material , piece ;
    for(int i = 0 ; i<BRD_SQ_NUM ; i++)
    {
        sq = i;
        piece = pos->pieces[i];
        if(piece!=OFFBOARD && piece !=EMPTY)
        {
            color = PieceCol[i];

            if(PieceBig[piece] == TRUE){pos->bigPce[color]++;}
            if(PieceMaj[piece] == TRUE){pos->majPce[color]++;}
            if(PieceMin[piece] == TRUE){pos->minPce[color]++;}

            //material is the total amt of pieces u have so like we are adding the values of pieces and getting a total score of how much "material" ur having
            pos->material[color] += PieceVal[i]; 

            pos->piecelist[piece][pos->pceNum[piece]] = sq;

            if(piece == bK)
            {
                pos->KingSq[BLACK] = sq;
            }
            if(piece == wK)
            {
                pos->KingSq[WHITE] = sq;
            }
        }

    }

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
        ASSERT(file>FILE_A && file < FILE_H);
        ASSERT(rank>RANK1 && rank < RANK8);
        pos->enPas = FR2SQ(file,rank);
    }

    pos->poskey = InitGetHashKey(pos);

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