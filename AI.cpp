#include "base.h"
#include "extern.h"
#include "AIbase.h"
#include <algorithm>

//C-squares and X-squares Awareness
//Corner Tendency
//Even Block Estimate
//Position Estimate
//Mobility Significance

Coord AI(Cell board[SAFE_LENGTH][SAFE_LENGTH], bool side)
{
    Coord AI = validCoord[0];
    random_shuffle(validCoord.begin(), validCoord.end());


    status tmpBoard[SAFE_LENGTH][SAFE_LENGTH];
    for (int i = 0; i < SAFE_LENGTH; i++) for (int j = 0; j < SAFE_LENGTH; j++) tmpBoard[i][j] = board[i][j].stat;



    return AI;
}