#ifndef DEFS_H
#define DEFS_H
#include "stdlib.h"

#define DEBUG 
#ifndef DEBUG
#else
//used to check if a cond is true or false
#define ASSERT(n)\
if(!(n)){ \
    printf("%s - Failed" , #n);\
    printf("on %s" , __DATE__);\
    printf("At %s" , __TIME__);\
    printf("In File %s" , __FILE__);\
    printf("At Line %d" , __LINE__);\
    exit(1);}

#endif

#define MAXMOVES 2480

typedef unsigned long long U64;
#define BRD_SQ_NUM 120
typedef struct
{
    int move;
    int CastlePerm;
    int enPas;
    int fiftyMove;
    U64 posKey;

}S_Undo;

extern int PiecePawn[13]; 	
extern int PieceKnight[13];
extern int PieceKing[13];
extern int PieceRookQueen[13]; 
extern int PieceBishopQueen[13]; 
extern int PieceSlides[13]; 

typedef struct 
{
    int pieces[BRD_SQ_NUM];
    U64 Pawns[3];

    //piece list
    int piecelist[13][10];


    int CastlePerm;

    int KingSq[3];//for white , black, both
    int side;
    int enPas;
    int fiftymove;

    int ply;//half move 
    int hisply;//history half ply

    U64 poskey;

    int pceNum[13];
    int bigPce[2];
    int majPce[2];//Major Pieces are Kings ,  Bishops and all
    int minPce[2];
    int material[2];//Minior Pices are like Pawns


    S_Undo history[MAXMOVES];

}Board_Struc;

//definations
#define NAME "AutoChess V1"
#define FR2SQ(f,r)  ( (21 +(f)) + ((r)*10))
#define SQ64(sq120) Sq120toSq64[(sq120)];
#define SQ120(sq64) (Sq64ToSq120[(sq64)]);
#define POP(b) PopBit(*b);
#define CNT(b) CountBit(b);
#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
extern U64 ClearBit[64];
extern U64 MakeBit[64];
extern char PceChar[];
extern char SideChar[];
extern char RankChar[];
extern char FileChar[];

extern int majPiece[13];
extern int minPiece[13];
extern int PieceVal[13];
extern int PieceCol[13];



extern int  PieceBig[13];
extern int PieceMaj[13];
extern int PieceVal[13];
extern int PieceCol[13];
extern int PieceMin[13];


#define CLRBIT(bb,sq)((bb) &= ClearBit[(sq)]);
#define MKBIT(bB,sq)((bB) |= MakeBit[(sq)]);

#define IsBQ(p) (PieceBishopQueen[(p)])
#define IsRQ(p) (PieceRookQueen[(p)])
#define IsKn(p) (PieceKnight[(p)])
#define IsKi(p) (PieceKing[(p)])

extern int Sq120toSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];

extern int FileBrd[10];
extern int  RankBrd[10];

//funcs
extern void AllInit();
extern void InitSq120to64();
extern void MakeBitsFunc();
extern U64  InitGetHashKey(Board_Struc *pos);
extern int  ResetBoard(Board_Struc *pos);
extern int  fenfunc(char *fen , Board_Struc *pos);
extern void PrintBoard(Board_Struc *pos);
extern void InitUpdateMaterial(Board_Struc *pos);
extern void RankandFileFunc();
extern int CheckBoard(Board_Struc *pos);
extern int SqAttacked(const int sq , const int side , const Board_Struc *pos);


enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK  };
enum{
    FILE_A  , FILE_B , FILE_C , FILE_D , FILE_E ,FILE_F,FILE_G,FILE_H,FILE_NONE
};
enum
{
    RANK1 , RANK2 , RANK3 , RANK4 , RANK5 , RANK6 , RANK7,RANK8, RANKN
};
enum
{
    WHITE , BLACK , BOTH

};
enum{
    A1 = 21 , B1,C1,D1,E1,F1,G1,H1,
    A2 = 31 , B2,C2,D2,E2,F2,G2,H2,
    A3 = 41 , B3,C3,D3,E3,F3,G3,H3,
    A4 = 51 , B4,C4,D4,E4,F4,G4,H4,
    A5 = 61 , B5,C5,D5,E5,F5,G5,H5,
    A6 = 71 , B6,C6,D6,E6,F6,G6,H6,
    A7 = 81 , B7,C7,D7,E7,F7,G7,H7,
    A8 = 91 , B8,C8,D8,E8,F8,G8,H8,NO_SQ,OFFBOARD
};



enum
{
    FALSE,TRUE
};

//castle constants
enum{
    WKC = 1,
    WQC = 2,
    BKC = 4,
    BQC = 8,
};
//creating the board representations that is the board information

//Globals

extern int Sq120toSq64[BRD_SQ_NUM];
extern int Sq64ToSq120[64];
extern U64 PieceKeys[13][120];
extern U64 SideKey;
extern U64 CasteKeys[16];

//bitboard functions
extern void PrintBitBoard(U64 bB);
extern int PopBit(U64 *bB);
extern int CountBit(U64 b);
#endif
