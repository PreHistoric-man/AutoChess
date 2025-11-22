#include <stdio.h>
#include "defs.h"
#include "stdlib.h"

//rand gives a random 15bit(this is due to rand) no  which is added into a random 64 bit no 
#define RAND64 ((U64)rand() +\
                (U64)rand()+15 +\
                (U64)rand()+30 +\
                (U64)rand()+45 +\
                (U64)rand() & 0xf )<< 60

int Sq120toSq64[BRD_SQ_NUM];
int Sq64ToSq120[64];

// 64 bit arrays to clear and add bits to the board like pawns
U64 ClearBit[64];
U64 MakeBit[64];

//arrays to store the position keys 
U64 PieceKeys[13][120];
U64 SideKey;
U64 CasteKeys[16];

void MakeHashKeys()
{
    int index = 0;
    int index2 = 0;
    for(index = 0  ; index < 13 ; ++index)
    {
        for(index2 = 0 ; index2 <120 ; index2++)
        {
            PieceKeys[index][index2] = RAND64;
            printf("Random Values = %d \n" , PieceKeys[index][index2]);
        }
    }

    for(int index = 0 ; index <16 ; index++)
    {
        CasteKeys[index] = RAND64;
    }
}


void MakeBitsFunc()
{
    int index = 0;

    for(index = 0 ; index <64 ; index++)
    {
        ClearBit[index] = 0ULL;
        MakeBit[index] = 0ULL;
    }

    for(index = 0;index<64;index++)
    {
        MakeBit[index] = (1ULL << index);
        ClearBit[index] = ~MakeBit[index];
    }
}


void InitSq120to64()
{
    int index = 0;
    int file = FILE_A;
    int rank = RANK1;
    int sq = A1;
    int sq64 = 0;
    for(index = 0 ; index < BRD_SQ_NUM ; ++index)
    {
        Sq120toSq64[index] = 65;
    }
    for(index = 0; index <64 ; ++index)
    {   
        Sq64ToSq120[index] = 120;
    }

    for(rank = RANK1; rank<=RANK8 ; ++rank)
    {
        for(file = FILE_A ; file <=FILE_H ; ++file)
        {
            sq = FR2SQ(file,rank);
            Sq64ToSq120[sq64] = sq;
            Sq120toSq64[sq] = sq64;
            sq64++;
        }
    }
}

void AllInit()
{
    InitSq120to64();
    MakeBitsFunc();
    MakeHashKeys();
}