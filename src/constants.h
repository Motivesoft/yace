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
            bishopMoves[ index ] = 0;
            rookMoves[ index ] = 0;
            queenMoves[ index ] = 0;
            kingMoves[ index ] = 0;

            Index8 file = 0b00000111 & index;
            Index8 rank = 0b00000111 & (index >> 3);

            signed char knightArray[][ 2 ] = { { -2, -1 }, { -2, +1 }, { +2, -1 }, { +2, +1 }, { -1, -2 }, { -1, +2 }, { +1, -2 }, { +1, +2 } };

            for ( unsigned short arrayIndex = 0; arrayIndex < 8; arrayIndex++ )
            {
                if ( file + knightArray[ arrayIndex ][ 0 ] >= 0 && file + knightArray[ arrayIndex ][ 0 ] < 8 )
                {
                    if ( rank + knightArray[ arrayIndex ][ 1 ] >= 0 && rank + knightArray[ arrayIndex ][ 1 ] < 8 )
                    {
                        knightMoves[ index ] |= 1ull<<(index + (( knightArray[ arrayIndex ][ 1 ] << 3) + knightArray[ arrayIndex ][ 0 ] ));
                    }
                }
            }

            signed char bishopArray[][ 2 ] = { { -1, -1 }, { -1, +1 }, { +1, -1 }, { +1, +1 } };

            for ( unsigned short arrayIndex = 0; arrayIndex < 4; arrayIndex++ )
            {
                Index8 destinationFile = file;
                Index8 destinationRank = rank;
                for ( Index8 distance = 1; distance < 8; distance++ )
                {
                    destinationFile += bishopArray[ arrayIndex ][ 0 ];
                    destinationRank += bishopArray[ arrayIndex ][ 1 ];

                    if ( destinationFile >= 0 && destinationFile < 8 && destinationRank >= 0 && destinationRank < 8 )
                    {
                        bishopMoves[ index ] |= 1ull << ( ( destinationRank << 3 ) + destinationFile );
                        queenMoves[ index ] |= 1ull << ( ( destinationRank << 3 ) + destinationFile );

                        if ( distance == 1 )
                        {
                            kingMoves[ index ] |= 1ull << ( ( destinationRank << 3 ) + destinationFile );
                        }
                    }
                }
            }

            signed char rookArray[][ 2 ] = { { -1, 0 }, { 0, -1 }, { +1, 0 }, { 0, +1 } };

            for ( unsigned short arrayIndex = 0; arrayIndex < 4; arrayIndex++ )
            {
                Index8 destinationFile = file;
                Index8 destinationRank = rank;
                for ( Index8 distance = 1; distance < 8; distance++ )
                {
                    destinationFile += rookArray[ arrayIndex ][ 0 ];
                    destinationRank += rookArray[ arrayIndex ][ 1 ];

                    if ( destinationFile >= 0 && destinationFile < 8 && destinationRank >= 0 && destinationRank < 8 )
                    {
                        rookMoves[ index ] |= 1ull << ( ( destinationRank << 3 ) + destinationFile );
                        queenMoves[ index ] |= 1ull << ( ( destinationRank << 3 ) + destinationFile );

                        if ( distance == 1 )
                        {
                            kingMoves[ index ] |= 1ull << ( ( destinationRank << 3 ) + destinationFile );
                        }
                    }
                }
            }

            printf( "\n\n(%c%c) %d\n", 'A'+file, '1'+rank, index);
            printBitboard( kingMoves[ index ] );
        }
    };
};