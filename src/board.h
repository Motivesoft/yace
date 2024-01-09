#pragma once

#include <vector>

#include "constants.h"

/// <summary>
/// Board and everything to do with it
/// </summary>

class Board
{
public:
    typedef unsigned char Piece;
    typedef unsigned int Move;

    Piece empty  = 0b00000000;
    Piece pawn   = 0b00000001;
    Piece knight = 0b00000010;
    Piece king   = 0b00000011;
    Piece bishop = 0b00000110;
    Piece rook   = 0b00000101;
    Piece queen  = 0b00000111;

    Piece slidermask = 0b00000100;
    Piece diagonalslidermask = slidermask | 0b00000010;
    Piece straightslidermask = slidermask | 0b00000001;

    Piece colormask = 0b00001000;
    Piece white = 0b00000000;
    Piece black = 0b00001000;

    Index64 index8Mask = 0b00000111;
    Index64 noSquare = -1;

    // Game state
    Index64 epSquare;
    bool whiteToMove;

    inline bool isPiece( Piece piece )
    {
        return piece;
    }

    inline bool isNothing( Piece piece )
    {
        return !isPiece( piece );
    }

    inline bool isWhite( Piece piece )
    {
        return piece & colormask;
    }

    inline bool isBlack( Piece piece )
    {
        return !isWhite( piece );
    }

    inline bool isColorMatch( Piece piece1, Piece piece2 )
    {
        return isBlack( piece1 ) == isBlack( piece2 );
    }

    inline bool isSlider( Piece piece )
    {
        return ( piece & slidermask ) == slidermask;
    }

    inline bool isDiagonalSlider( Piece piece )
    {
        return ( piece & diagonalslidermask ) == diagonalslidermask;
    }

    inline bool isStraighSlider( Piece piece )
    {
        return ( piece & straightslidermask ) == straightslidermask;
    }

    inline Index64 toIndex( Index8 file, Index8 rank )
    {
        return ( rank << 3 ) + file;
    }

    inline Index8 toFile( Index64 index )
    {
        return index & index8Mask;
    }

    inline Index8 toRank( Index64 index )
    {
        return ( index >> 3 ) & index8Mask;
    }

    inline bool isValid( Index64 index )
    {
        return index != noSquare;
    }

    Board()
    {
        // Default position
        for ( Index64 index = 32; index < 48; index++ )
        {
            board[ index ] = empty;
        }

        board[ 4 ] = white | king;
        board[ 3 ] = white | queen;
        board[ 2 ] = board[ 5 ] = white | bishop;
        board[ 1 ] = board[ 6 ] = white | knight;
        board[ 0 ] = board[ 7 ] = white | rook;
        for ( Index64 index = 8; index < 16; index++ )
        {
            board[ index ] = white | pawn;
        }

        board[ 60 ] = black | king;
        board[ 59 ] = black | queen;
        board[ 58 ] = board[ 61 ] = black | bishop;
        board[ 57 ] = board[ 62 ] = black | knight;
        board[ 56 ] = board[ 63 ] = black | rook;
        for ( Index64 index = 48; index < 56; index++ )
        {
            board[ index ] = black | pawn;
        }
    }

    /// <summary>
    /// No copy constructor
    /// </summary>
    /// <param name="board">the board to copy</param>
    Board( const Board& board ) = delete;

    bool getMoves( std::vector<Move>& moves );

private:
    Bitboard whiteKingLocation;
    Bitboard whiteQueenLocation;
    Bitboard whiteRookLocation;
    Bitboard whiteBishopLocation;
    Bitboard whiteKnightLocation;
    Bitboard whitePawnLocation;

    Bitboard blackKingLocation;
    Bitboard blackQueenLocation;
    Bitboard blackRookLocation;
    Bitboard blackBishopLocation;
    Bitboard blackKnightLocation;
    Bitboard blackPawnLocation;

    Bitboard whiteLocations;
    Bitboard blackLocations;

    Piece board[ 64 ];

    bool getMoves( std::vector<Move>& moves,
                   Bitboard kingLocation,
                   Bitboard queenLocation,
                   Bitboard rookLocation,
                   Bitboard bishopLocation,
                   Bitboard knightLocation,
                   Bitboard pawnLocation,
                   Bitboard blockerLocations,
                   Bitboard attackerLocations );

    bool getDiagonalMoves( std::vector<Move>& moves, Bitboard pieceLocation );
    bool getCrossedMoves( std::vector<Move>& moves, Bitboard pieceLocation );

    bool getKingMoves( std::vector<Move>& moves, Bitboard pieceLocation );
    bool getKnightMoves( std::vector<Move>& moves, Bitboard pieceLocation );
    bool getPawnMoves( std::vector<Move>& moves, Bitboard pieceLocation );
};

