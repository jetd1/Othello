#include "base.h"
#include "extern.h"
#include "AIbase.h"
#include <algorithm>

//Make Pass
//C-squares and X-squares Awareness
//Corner Tendency
//Even Block Estimate
//Position Estimate
//Mobility Significance

Coord AI(sBoard &board, bool side)
{
    Coord AI = validCoord[0];
    random_shuffle(validCoord.begin(), validCoord.end());

    sBoard *tmpBoard = new sBoard[board.statusCount[Valid]];
    for (int i = 0; i < board.statusCount[Valid]; i++) tmpBoard[i] = board;
    



    return AI;
}

short evaluate(sBoard board, bool side)
{
    short value = 0;
    for (int i = 1; i <= SIDE_LENGTH; i++) for (int j = 1; j <= SIDE_LENGTH; j++)
    {
        
    }
    return value;
}