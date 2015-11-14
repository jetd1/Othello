#include "base.h"
#include "extern.h"
#include <algorithm>

string AI()
{
    string AI = validCoord[0];
    random_shuffle(validCoord.begin(), validCoord.end());


    status tmpBoard[10][10];
    for (int i = 0; i < 10; i++) for (int j = 0; j < 10; j++) tmpBoard[i][j] = board[i][j];



    return AI;
}