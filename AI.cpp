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

Coord AI(Board &board, bool AISide)
{
    Board *tmpBoard = new Board[board.statusCount[Valid]];
    short *humanValidCount = new short[board.statusCount[Valid]];

    for (int i = 0; i < board.statusCount[Valid]; i++)
    {
        tmpBoard[i] = board;
        tmpBoard[i].move(gameBoard.validCoord[i], AISide);
        if (DEBUGMODE)
        {
            cout << endl;
            cout << "Coord: " << char(board.validCoord[i].y + '@') << board.validCoord[i].x << endl;
        }

        board.validCoord[i].value = AIBoardEval(tmpBoard[i], AISide);
    }

    delete[] tmpBoard;
    delete[] humanValidCount;

    sort(board.validCoord.begin(), board.validCoord.end(), cmpCoordV);

    return gameBoard.validCoord[0];
}


double AIBoardEval(Board &board, bool side)
{
    //Evaluation Based on Character Value
    double CharaEval;

    double myChara = board.allEval(side);
    double opChara = board.allEval(!side);

    CharaEval = myChara - opChara;


    //Evaluation Based on Stone Rate
    double BWRateEval;

    short myStoneCount = board.statusCount[side];
    short opStoneCount = board.statusCount[!side];

    if (myStoneCount > opStoneCount)
        BWRateEval = 100.0 * myStoneCount / (myStoneCount + opStoneCount);
    else if (myStoneCount < opStoneCount)
        BWRateEval = -100.0 * opStoneCount / (myStoneCount + opStoneCount);
    else BWRateEval = 0;


    //Evaluation Based on Stone Frontier Rate
    double FrontierRateEval;

    short myFrontierCount = board.frontierCount(side);
    short opFrontierCount = board.frontierCount(!side);

    if (myFrontierCount > opFrontierCount)
        FrontierRateEval = -100.0 * myFrontierCount / (myFrontierCount + opFrontierCount);
    else if (myFrontierCount < opFrontierCount)
        FrontierRateEval = 100.0 * opFrontierCount / (myFrontierCount + opFrontierCount);
    else FrontierRateEval = 0;


    //Evaluation Based on Corner Stone Count
    double CornerEval;

    short myCornerCount =
        (board[1][1].stat == status(side)) +
        (board[1][8].stat == status(side)) +
        (board[8][1].stat == status(side)) +
        (board[8][8].stat == status(side));

    CornerEval = 50 * (myCornerCount - 2);


    //Evaluation Based on Dangerous Corner-Beside-Stone Count
    double DCornerEval;

    short myDCornerCount =
        (board.cell[1][1].stat >= Empty) && (board.cell[1][2].stat == status(side)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][2].stat == status(side)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][1].stat == status(side)) +
        (board.cell[1][8].stat >= Empty) && (board.cell[1][7].stat == status(side)) +
        (board.cell[1][8].stat >= Empty) && (board.cell[2][7].stat == status(side)) +
        (board.cell[1][8].stat >= Empty) && (board.cell[2][8].stat == status(side)) +
        (board.cell[8][1].stat >= Empty) && (board.cell[8][2].stat == status(side)) +
        (board.cell[8][1].stat >= Empty) && (board.cell[7][1].stat == status(side)) +
        (board.cell[8][1].stat >= Empty) && (board.cell[7][2].stat == status(side)) +
        (board.cell[8][8].stat >= Empty) && (board.cell[8][7].stat == status(side)) +
        (board.cell[8][8].stat >= Empty) && (board.cell[7][7].stat == status(side)) +
        (board.cell[8][8].stat >= Empty) && (board.cell[7][8].stat == status(side));

    DCornerEval = -25 * (myStoneCount - 6);


    //Evaluation Based on Mobility
    double MobEval;

    short myValidCount = board.countValidFor(side);
    short opValidCount = board.countValidFor(!side);

    if (myValidCount > opValidCount)
        MobEval = (100.0 * myValidCount) / (myValidCount + opValidCount);
    else if (myValidCount < opValidCount)
        MobEval = -(100.0 * opValidCount) / (myValidCount + opValidCount);
    else MobEval = 0;


    //Weighed Evaluation
    double Eval = 
        (10 * BWRateEval) +
        (801.724 * CornerEval) +
        (382.026 * DCornerEval) + 
        (78.922 * MobEval) + 
        (74.396 * FrontierRateEval) + 
        (10 * CharaEval);

    if (DEBUGMODE)
    {
        cout << "BWRateEval\t" << BWRateEval << endl;
        cout << "CornerEval\t" << CornerEval << endl;
        cout << "DCornerEval\t" << DCornerEval << endl;
        cout << "MobilityEval\t" << MobEval << endl;
        cout << "FRTRRateEval\t" << FrontierRateEval << endl;
        cout << "CharaEval\t" << CharaEval << endl << endl;
        cout << "TotalEval\t" << Eval << endl << endl << endl;
    }

    return Eval;

}

//double AIEval(Coord &validMove, Board &tmpBoard, bool AISide)
//{
//    double AIEval = POSFACTOR1;
//
//    AIEval += PASSVALUE * (tmpBoard.validCoord.size() == 0);
//
//    AIEval += (sqrt(sqrt(tmpBoard.rCount(!AISide)) * ( validMove.chara + POSFACTOR2)) - tmpBoard.vEval(!AISide));
//
//    return AIEval;
//}


bool cmpBoard(const Board &A, const Board &B) { return A > B; }
bool rcmpBoard(const Board &A, const Board &B) { return A < B; }
bool cmpCoordV(const Coord &A, const Coord &B) { return A.value > B.value; }
bool rcmpCoordV(const Coord &A, const Coord &B) { return A.value < B.value; }
bool cmpCoordC(const Coord &A, const Coord &B) { return A.chara > B.chara; }
bool rcmpCoordC(const Coord &A, const Coord &B) { return A.chara < B.chara; }
