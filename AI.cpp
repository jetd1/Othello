/*
AI by Jet
Version 0.3.6
*/

//Make Pass
//C-squares and X-squares Awareness
//Corner Tendency
//Even Block Estimate
//Position Estimate
//Mobility Significance

#include "elements.h"
#include "AIbase.h"
#include <algorithm>


extern Board gameBoard;

Coord AI(Board &board, bool side)
{
    Board *tmpBoard = new Board[board.statusCount[Valid]];
    short *humanValidCount = new short[board.statusCount[Valid]];

    for (int i = 0; i < board.statusCount[Valid]; i++)
    {
        tmpBoard[i] = board;
        tmpBoard[i].move(gameBoard.validCoord[i], side);
        board.validCoord[i].value=(tmpBoard[i].rCount(!side)*board.validCoord[i].chara - tmpBoard[i].vEval(!side)+POSFACTOR);

        if (DEBUGMODE)
        {
            cout << endl;
            tmpBoard[i].print();
            cout << board.validCoord[i].value << endl;
        }
    }

    sort(board.validCoord.begin(), board.validCoord.end(), cmpCoord);

    return gameBoard.validCoord[0];
}


bool cmpBoard(const Board &A, const Board &B) { return A > B; }
bool rcmpBoard(const Board &A, const Board &B) { return A < B; }
bool cmpCoord(const Coord &A, const Coord &B) { return A.value > B.value; }
bool rcmpCoord(const Coord &A, const Coord &B) { return A.value < B.value; }
