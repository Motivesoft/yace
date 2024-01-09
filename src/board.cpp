#include "board.h"

bool Board::getMoves( std::vector<Move>& moves )
{
    return whiteToMove ?
        getMoves( moves,
                  whiteKingLocation,
                  whiteQueenLocation,
                  whiteRookLocation,
                  whiteBishopLocation,
                  whiteKnightLocation,
                  whitePawnLocation,
                  whiteLocations,
                  blackLocations ) :
        getMoves( moves,
                  blackKingLocation,
                  blackQueenLocation,
                  blackRookLocation,
                  blackBishopLocation,
                  blackKnightLocation,
                  blackPawnLocation,
                  blackLocations,
                  whiteLocations );
}

bool Board::getMoves( std::vector<Move>& moves,
                      Bitboard kingLocation,
                      Bitboard queenLocation,
                      Bitboard rookLocation,
                      Bitboard bishopLocation,
                      Bitboard knightLocation,
                      Bitboard pawnLocation,
                      Bitboard blockLocations,
                      Bitboard attackerLocations )
{
    // Return false if we can capture the opponent's king, i.e. meaning this is an invalid position

    // Queen/Rook
    if ( !getDiagonalMoves( moves, whiteBishopLocation | whiteQueenLocation ) )
    {
        return false;
    }
    // Queen/Bishop
    if ( !getCrossedMoves( moves, whiteRookLocation | whiteQueenLocation ) )
    {
        return false;
    }
    // Knight
    if ( !getKnightMoves( moves, whiteKnightLocation ) )
    {
        return false;
    }
    // Pawn
    if ( !getPawnMoves( moves, whitePawnLocation ) )
    {
        return false;
    }
    // King
    if ( !getKingMoves( moves, whiteKingLocation ) )
    {
        return false;
    }

    return true;
}

bool Board::getDiagonalMoves( std::vector<Move>& moves, Bitboard pieceLocation )
{
    // Return false if we can capture the opponent's king, i.e. meaning this is an invalid position

    // Queen/Rook

    // Queen/Bishop
    // Knight
    // Pawn
    // King

    return true;
}

bool Board::getCrossedMoves( std::vector<Move>& moves, Bitboard pieceLocation )
{
    // Return false if we can capture the opponent's king, i.e. meaning this is an invalid position

    // Queen/Rook

    // Queen/Bishop
    // Knight
    // Pawn
    // King

    return true;
}

bool Board::getKingMoves( std::vector<Move>& moves, Bitboard pieceLocation )
{
    // Return false if we can capture the opponent's king, i.e. meaning this is an invalid position

    if ( !getDiagonalMoves( moves, pieceLocation ) )
    {
        return false;
    }
    if ( !getCrossedMoves( moves, pieceLocation ) )
    {
        return false;
    }

    // Castling

    return true;
}

bool Board::getKnightMoves( std::vector<Move>& moves, Bitboard pieceLocation )
{
    // Return false if we can capture the opponent's king, i.e. meaning this is an invalid position

    return true;
}

bool Board::getPawnMoves( std::vector<Move>& moves, Bitboard pieceLocation )
{
    // Return false if we can capture the opponent's king, i.e. meaning this is an invalid position

    // Single moves
    // Extended moves for any pawns on the home rank and capable of the single move
    // Captures, including ep (if available)

    return true;
}
