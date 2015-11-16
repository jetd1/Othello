/*
AI by Jet
Version 0.5
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

        if (tmpBoard[i].validCoord.size() == 0) 
            return gameBoard.validCoord[i];

        board.validCoord[i].value = (sqrt(tmpBoard[i].rCount(!side) * ( board.validCoord[i].chara + POSFACTOR1)) - tmpBoard[i].vEval(!side) + POSFACTOR2);

        if (DEBUGMODE)
        {
            cout << endl;
            cout << "Coord: " << char(board.validCoord[i].y + '@') << board.validCoord[i].x << endl;
            cout << "Post-move Board Value: " << board.validCoord[i].value << endl;
            cout << "Post-move rCount(!side): " << tmpBoard[i].rCount(!side) << endl;
            cout << "Move Coord Chara: " << board.validCoord[i].chara << endl;
            cout << "Post-move vEval(!side): " << tmpBoard[i].vEval(!side) << endl;
            cout << endl;
            cout << "Post-move aEval(side): " << tmpBoard[i].aEval(side) << endl;
            cout << "Post-move aEval(!side): " << tmpBoard[i].aEval(!side) << endl;
            cout << endl;
        }
    }

    delete[] tmpBoard;
    delete[] humanValidCount;

    sort(board.validCoord.begin(), board.validCoord.end(), cmpCoordV);

    return gameBoard.validCoord[0];
}


bool cmpBoard(const Board &A, const Board &B) { return A > B; }
bool rcmpBoard(const Board &A, const Board &B) { return A < B; }
bool cmpCoordV(const Coord &A, const Coord &B) { return A.value > B.value; }
bool rcmpCoordV(const Coord &A, const Coord &B) { return A.value < B.value; }
bool cmpCoordC(const Coord &A, const Coord &B) { return A.chara > B.chara; }
bool rcmpCoordC(const Coord &A, const Coord &B) { return A.chara < B.chara; }
