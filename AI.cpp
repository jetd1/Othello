#include "base.h"
#include "extern.h"
#include <algorithm>

string AI()
{
    string AI = validCoord[0];
    random_shuffle(validCoord.begin(), validCoord.end());


    status tmpBoard[SAFE_LENGTH][SAFE_LENGTH];
    for (int i = 0; i < SAFE_LENGTH; i++) for (int j = 0; j < SAFE_LENGTH; j++) tmpBoard[i][j] = board[i][j];



    return AI;
}