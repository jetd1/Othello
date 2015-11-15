#include "elements.h"
#include "AIbase.h"
#include <algorithm>

//Make Pass
//C-squares and X-squares Awareness
//Corner Tendency
//Even Block Estimate
//Position Estimate
//Mobility Significance

extern Board gameBoard;

Coord AI(Board &board, bool side)
{
    random_shuffle(gameBoard.validCoord.begin(), gameBoard.validCoord.end());
    Coord AI = gameBoard.validCoord[0];
    Board *tmpBoard = new Board[board.statusCount[Valid]];
    for (int i = 0; i < board.statusCount[Valid]; i++) tmpBoard[i] = board;
    
    return AI;
}

short evaluate(Board board, bool side)
{
    short value = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        
    }
    return value;
}