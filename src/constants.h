#pragma once

#include <stdio.h>

class Constants
{
public:
    typedef unsigned long long Bitboard;
    typedef unsigned char Index64;
    typedef unsigned char Index8;

    static Constants getInstance()
    {
        static Constants constants;

        return constants;
    }

    Bitboard getQueenMoves( Index64 index )
    {
        return queenMoves[ index ];
    }

    void printBitboard( Bitboard bitboard )
    {
        for ( int outer = 7; outer >= 0; outer-- )
        {
            for ( int inner = 0; inner < 8; inner++ )
            {
                if ( bitboard & ( 1ull << ( ( outer << 3 ) + inner ) ) )
                {
                    printf( "X" );
                }
                else
                {
                    printf( "." );
                }
            }
            printf( "\n" );
        }
    }

private:
    Bitboard knightMoves[ 64 ];
    Bitboard bishopMoves[ 64 ];
    Bitboard rookMoves[ 64 ];
    Bitboard queenMoves[ 64 ];
    Bitboard kingMoves[ 64 ];
    Bitboard whitePawnMoves[ 64 ];
    Bitboard whitePawnExtendedMoves[ 64 ];
    Bitboard whitePawnCaptures[ 64 ];
    Bitboard blackPawnMoves[ 64 ];
    Bitboard blackPawnExtendedMoves[ 64 ];
    Bitboard blackPawnCaptures[ 64 ];
    Bitboard whiteKingsideCastleEmpties[ 64 ];
    Bitboard whiteQueensideCastleEmpties[ 64 ];
    Bitboard whiteKingsideCastleUnchecked[ 64 ];
    Bitboard whiteQueensideCastleUnchecked[ 64 ];
    Bitboard blackKingsideCastleEmpties[ 64 ];
    Bitboard blackQueensideCastleEmpties[ 64 ];
    Bitboard blackKingsideCastleUnchecked[ 64 ];
    Bitboard blackQueensideCastleUnchecked[ 64 ];

    Constants()
    {
        for ( Index64 index = 0; index < 64; index++ )
        {
            knightMoves[ index ] = 0;

            Index8 file = 0b00000111 & index;
            Index8 rank = 0b00000111 & (index >> 3);

            signed char knightArray[][ 2 ] = { { -2, -1 }, { -2, +1 }, { +2, -1 }, { +2, +1 }, { -1, -2 }, { -1, +2 }, { +1, -2 }, { +1, +2 } };

            for ( unsigned short knightArrayIndex = 0; knightArrayIndex < 8; knightArrayIndex++ )
            {
                if ( file + knightArray[ knightArrayIndex ][ 0 ] >= 0 && file + knightArray[ knightArrayIndex ][ 0 ] < 8 )
                {
                    if ( rank + knightArray[ knightArrayIndex ][ 1 ] >= 0 && rank + knightArray[ knightArrayIndex ][ 1 ] < 8 )
                    {
                        knightMoves[ index ] |= 1ull<<(index + (( knightArray[ knightArrayIndex ][ 1 ] << 3) + knightArray[ knightArrayIndex ][ 0 ] ));
                    }
                }
            }

            printf( "\n\n(%c%c) %d\n", 'A'+file, '1'+rank, index);
            printBitboard( knightMoves[ index ] );
        }
    };
};