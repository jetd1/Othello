/*
AI by Jet
Version 0.6.7
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

extern short turnCount;
extern Board gameBoard;

Coord AI(Board &board, bool AISide)
{
    turnCount++;
    Board *tmpBoard = new Board[board.statusCount[Valid]];

    for (int i = 0; i < board.statusCount[Valid]; i++)
    {
        tmpBoard[i] = board;
        tmpBoard[i].move(gameBoard.validCoord[i], AISide);

        if (DEBUGMODE)
        {
            cout << endl;
            cout << "Coord: " << char(board.validCoord[i].y + '@') << board.validCoord[i].x << endl;
        }

        board.validCoord[i].value = MixedBoardEval(board.validCoord[i], tmpBoard[i], AISide);
            
        if (DEBUGMODE) cout << "FinalEval\t" << board.validCoord[i].value << endl << endl << endl;
    }

    delete[] tmpBoard;

    sort(board.validCoord.begin(), board.validCoord.end(), cmpCoordV);

    return gameBoard.validCoord[0];
}

double MixedBoardEval(Coord &validMove, Board &tmpBoard, bool side)
{
    double MixedEval;

    if (MIXFACTOR - TURNFACTOR*turnCount < BOUNDFACTOR)
        MixedEval = ClassicBoardEval(tmpBoard, side) +
        BOUNDFACTOR * JetBoardEval(validMove, tmpBoard, side);
    else
        MixedEval = ClassicBoardEval(tmpBoard, side) +
        (MIXFACTOR - TURNFACTOR * turnCount) * JetBoardEval(validMove, tmpBoard, side);

    return MixedEval;
}


double ClassicBoardEval(Board &board, bool side)
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

    short opCornerCount =
        (board[1][1].stat == status(!side)) +
        (board[1][8].stat == status(!side)) +
        (board[8][1].stat == status(!side)) +
        (board[8][8].stat == status(!side));

    CornerEval = 25 * (myCornerCount - opCornerCount);


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

    short opDCornerCount =
        (board.cell[1][1].stat >= Empty) && (board.cell[1][2].stat == status(!side)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][2].stat == status(!side)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][1].stat == status(!side)) +
        (board.cell[1][8].stat >= Empty) && (board.cell[1][7].stat == status(!side)) +
        (board.cell[1][8].stat >= Empty) && (board.cell[2][7].stat == status(!side)) +
        (board.cell[1][8].stat >= Empty) && (board.cell[2][8].stat == status(!side)) +
        (board.cell[8][1].stat >= Empty) && (board.cell[8][2].stat == status(!side)) +
        (board.cell[8][1].stat >= Empty) && (board.cell[7][1].stat == status(!side)) +
        (board.cell[8][1].stat >= Empty) && (board.cell[7][2].stat == status(!side)) +
        (board.cell[8][8].stat >= Empty) && (board.cell[8][7].stat == status(!side)) +
        (board.cell[8][8].stat >= Empty) && (board.cell[7][7].stat == status(!side)) +
        (board.cell[8][8].stat >= Empty) && (board.cell[7][8].stat == status(!side));

    DCornerEval = -12.5 * (myDCornerCount - opDCornerCount);


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
        (8 * BWRateEval) +
        (800 * CornerEval) +
        (380 * DCornerEval) + 
        (80 * MobEval) + 
        (70 * FrontierRateEval) + 
        (9 * CharaEval);

    if (DEBUGMODE)
    {
        cout << "Classic Eval:" << endl;
        cout << "BWRateEval\t" << BWRateEval << endl;
        cout << "CornerEval\t" << CornerEval << endl;
        cout << "DCornerEval\t" << DCornerEval << endl;
        cout << "MobilityEval\t" << MobEval << endl;
        cout << "FRTRRateEval\t" << FrontierRateEval << endl;
        cout << "CharaEval\t" << CharaEval << endl << endl;
        cout << "ClassicEval\t" << Eval << endl << endl;
    }

    return Eval;

}

inline double JetBoardEval(Coord &validMove, Board &tmpBoard, bool side)
{
    double JetEval = POSFACTOR1;

    JetEval += PASSVALUE * (tmpBoard.validCoord.size() == 0);

    JetEval += (sqrt(sqrt(tmpBoard.CountRate(!side)) * ( validMove.chara + POSFACTOR2)) - tmpBoard.validEval(!side));

    if (DEBUGMODE)
    {
        cout << endl;
        cout << "JetEval\t" << JetEval << endl << endl;
    }

    return JetEval;
}


bool cmpBoard(const Board &A, const Board &B) { return A > B; }
bool rcmpBoard(const Board &A, const Board &B) { return A < B; }
bool cmpCoordV(const Coord &A, const Coord &B) { return A.value > B.value; }
bool rcmpCoordV(const Coord &A, const Coord &B) { return A.value < B.value; }
bool cmpCoordC(const Coord &A, const Coord &B) { return A.chara > B.chara; }
bool rcmpCoordC(const Coord &A, const Coord &B) { return A.chara < B.chara; }
