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
        printf( "\n" );
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

    Bitboard whiteKingsideCastleEmpties;
    Bitboard whiteQueensideCastleEmpties;
    Bitboard whiteKingsideCastleUnchecked;
    Bitboard whiteQueensideCastleUnchecked;
    Bitboard blackKingsideCastleEmpties;
    Bitboard blackQueensideCastleEmpties;
    Bitboard blackKingsideCastleUnchecked;
    Bitboard blackQueensideCastleUnchecked;

    Constants()
    {
        for ( Index64 index = 0; index < 64; index++ )
        {
            knightMoves[ index ] = 0;
            bishopMoves[ index ] = 0;
            rookMoves[ index ] = 0;
            queenMoves[ index ] = 0;
            kingMoves[ index ] = 0;
            whitePawnMoves[ index ] = 0;
            whitePawnExtendedMoves[ index ] = 0;
            whitePawnCaptures[ index ] = 0;
            blackPawnMoves[ index ] = 0;
            blackPawnExtendedMoves[ index ] = 0;
            blackPawnCaptures[ index ] = 0;

            Index8 file = 0b00000111 & index;
            Index8 rank = 0b00000111 & (index >> 3);

            signed char knightArray[][ 2 ] = { { -2, -1 }, { -2, +1 }, { +2, -1 }, { +2, +1 }, { -1, -2 }, { -1, +2 }, { +1, -2 }, { +1, +2 } };

            for ( unsigned short arrayIndex = 0; arrayIndex < 8; arrayIndex++ )
            {
                Index8 destinationFile = file + knightArray[ arrayIndex ][ 0 ];
                Index8 destinationRank = rank + knightArray[ arrayIndex ][ 1 ];

                if ( destinationFile >= 0 && destinationFile < 8 && destinationRank >= 0 && destinationRank < 8 )
                {
                    knightMoves[ index ] |= 1ull << ( ( destinationRank << 3 ) + destinationFile );
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

            // Encode pawn moves even from the respective first ranks, even though pawns won't be there
            // This does no harm and actually, having the captures encoded like that might help with attacker detection
            if ( index < 56 )
            {
                whitePawnMoves[ index ] |= 1ull << ( index + 8 );

                if ( file > 0 )
                {
                    whitePawnCaptures[ index ] |= 1ull << ( index + 7 );
                }
                if ( file < 7 )
                {
                    whitePawnCaptures[ index ] |= 1ull << ( index + 9 );
                }

                if ( index > 7 && index < 16 )
                {
                    whitePawnExtendedMoves[ index ] |= 1ull << ( index + 16 );
                }
            }

            if ( index > 7 )
            {
                blackPawnMoves[ index ] |= 1ull << ( index - 8 );

                if ( file > 0 )
                {
                    blackPawnCaptures[ index ] |= 1ull << ( index - 9 );
                }
                if ( file < 7 )
                {
                    blackPawnCaptures[ index ] |= 1ull << ( index - 7 );
                }

                if ( index > 47 && index < 56 )
                {
                    blackPawnExtendedMoves[ index ] |= 1ull << ( index - 16 );
                }
            }

            //printf( "\n\n(%c%c) %d\n", 'A'+file, '1'+rank, index);
            //printBitboard( blackPawnCaptures[ index ] );
        }

        // Squares which must be empty to permit castling
        whiteKingsideCastleEmpties  = 0b0000000000000000000000000000000000000000000000000000000001100000;
        whiteQueensideCastleEmpties = 0b0000000000000000000000000000000000000000000000000000000000001110;
        blackKingsideCastleEmpties  = 0b0110000000000000000000000000000000000000000000000000000000000000;
        blackQueensideCastleEmpties = 0b0000111000000000000000000000000000000000000000000000000000000000;

        // Squares which must not be under attack to permit castling
        whiteKingsideCastleUnchecked  = 0b0000000000000000000000000000000000000000000000000000000001110000;
        whiteQueensideCastleUnchecked = 0b0000000000000000000000000000000000000000000000000000000000011100;
        blackKingsideCastleUnchecked  = 0b0111000000000000000000000000000000000000000000000000000000000000;
        blackQueensideCastleUnchecked = 0b0001110000000000000000000000000000000000000000000000000000000000;
    }
};