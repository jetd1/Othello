/*
Jacob
A Powerful Othello AI
By Jet
Version 1.6.3
*/

//Make Pass
//C-squares and X-squares Awareness
//Corner Tendency
//Even Block Estimate
//Position Estimate
//Mobility Significance
#include "elements.h"
#include "Jacob.h"
#include <cmath>
#include <thread>
#include <algorithm>

extern short maxDepth;
extern bool debugFlag, playerSide, randomFlag;
extern Board gameBoard;
extern aiType AIType;
extern double ALPHA, BETA, LOWERA, LOWERB;

extern void fatalError(unsigned ErrorCode);

double ABReturn[3];
Coord bestCoord[3];

clock_t startTime;

double ABJacob(Board &board, short depth, double alpha, double beta, short r)
{
    if (!depth || !board.statusCount[Empty] || !board.statusCount[Valid] || clock() - startTime > TIME_OUT)
        return BoardEval(board);


    double Eval;
    for (int i = 0; i < board.validCoord.size(); i++)
    {
        Board tmpBoard = board;
        tmpBoard.move(board.validCoord[i]);

        Eval = -ABJacob(tmpBoard, depth - 1, -beta, -alpha, r);
        if (Eval >= beta)
        {
            if (depth == maxDepth)
                bestCoord[r] = board.validCoord[i];
            return (ABReturn[r] = beta);
        }
        if (Eval > alpha)
        {
            alpha = Eval;
            if (depth == maxDepth)
                bestCoord[r] = board.validCoord[i];
        }
    }
    return (ABReturn[r] = alpha);
}

Coord RandomJacob(Board &board)
{
    random_shuffle(board.validCoord.begin(), board.validCoord.end());
    return board.validCoord[0];
}

Coord multiThreadABSearch(Board &board)
{
    if (randomFlag&& !(rand() % RANDFACTOR))
        return RandomJacob(board);

    if (MULTI_THREAD)
    {
        ABReturn[0] = ABReturn[1] = ABReturn[2] = ALPHA;
        thread AB1(ABJacob, board, maxDepth, ALPHA, LOWERA, 0);
        thread AB2(ABJacob, board, maxDepth, LOWERA, LOWERB, 1);
        thread AB3(ABJacob, board, maxDepth, LOWERB, BETA, 2);
        AB1.join();
        AB2.join();
        AB3.join();

        for (int i = 0; i < 3; i++)
            if (ABReturn[i] && ABReturn[i] != LOWERA && ABReturn[i] != LOWERB && board.isValid(bestCoord[i], !playerSide))
                return bestCoord[i];

        for (int i = 0; i < 3; i++)
            if (ABReturn[i] != LOWERA && ABReturn[i] != LOWERB && board.isValid(bestCoord[i], !playerSide))
                return bestCoord[i];

        ABJacob(board, 3, ALPHA, BETA, 0);
        return bestCoord[0];
    }
    else
    {
        ABJacob(board, maxDepth, ALPHA, BETA, 0);
        return bestCoord[0];
    }
}

Coord AI(Board &board)
{
    startTime = clock();
    switch (AIType)
    {
        case Random:
            return RandomJacob(board);
        case Jacob:
            return multiThreadABSearch(board);
        default:
            fatalError(1);
            return{};
    }
}

double BoardEval(Board &board)
{
    //Evaluation Based on Character Value
    double CharaEval;

    double myChara = board.allEval(board.sideFlag);
    double opChara = board.allEval(!board.sideFlag);

    CharaEval = myChara - opChara;


    //Evaluation Based on Stone Rate
    double BWRateEval;

    short myStoneCount = board.statusCount[board.sideFlag];
    short opStoneCount = board.statusCount[!board.sideFlag];

    if (myStoneCount > opStoneCount)
        BWRateEval = 100.0 * myStoneCount / (myStoneCount + opStoneCount);
    else if (myStoneCount < opStoneCount)
        BWRateEval = -100.0 * opStoneCount / (myStoneCount + opStoneCount);
    else BWRateEval = 0;


    //Evaluation Based on Stone Frontier Rate
    double FrontierRateEval;

    short myFrontierCount = board.frontierCount(board.sideFlag);
    short opFrontierCount = board.frontierCount(!board.sideFlag);

    if (myFrontierCount > opFrontierCount)
        FrontierRateEval = -100.0 * myFrontierCount / (myFrontierCount + opFrontierCount);
    else if (myFrontierCount < opFrontierCount)
        FrontierRateEval = 100.0 * opFrontierCount / (myFrontierCount + opFrontierCount);
    else FrontierRateEval = 0;


    //Evaluation Based on Corner Stone Count
    double CornerEval;

    short myCornerCount =
        (board[1][1].stat == status(board.sideFlag)) +
        (board[1][SIDE_LENGTH].stat == status(board.sideFlag)) +
        (board[SIDE_LENGTH][1].stat == status(board.sideFlag)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat == status(board.sideFlag));

    short opCornerCount =
        (board[1][1].stat == status(!board.sideFlag)) +
        (board[1][SIDE_LENGTH].stat == status(!board.sideFlag)) +
        (board[SIDE_LENGTH][1].stat == status(!board.sideFlag)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat == status(!board.sideFlag));

    CornerEval = 25 * (myCornerCount - opCornerCount);


    //Evaluation Based on Dangerous Corner-Beside-Stone Count
    double DCornerEval;

    short myDCornerCount =
        (board.cell[1][1].stat >= Empty) && (board.cell[1][2].stat == status(board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][2].stat == status(board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][1].stat == status(board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[1][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH][2].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][1].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][2].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH - 1].stat == status(board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH].stat == status(board.sideFlag));

    short opDCornerCount =
        (board.cell[1][1].stat >= Empty) && (board.cell[1][2].stat == status(!board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][2].stat == status(!board.sideFlag)) +
        (board.cell[1][1].stat >= Empty) && (board.cell[2][1].stat == status(!board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[1][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[1][SIDE_LENGTH].stat >= Empty) && (board.cell[2][SIDE_LENGTH].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH][2].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][1].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][1].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][2].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH - 1].stat == status(!board.sideFlag)) +
        (board.cell[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board.cell[SIDE_LENGTH - 1][SIDE_LENGTH].stat == status(!board.sideFlag));


    DCornerEval = -12.5 * (myDCornerCount - opDCornerCount);


    //Evaluation Based on Mobility
    double MobEval;

    short myValidCount = board.countValidFor(board.sideFlag);
    short opValidCount = board.countValidFor(!board.sideFlag);

    if (!opValidCount)
        MobEval = 250;
    else if (!myValidCount)
        MobEval = -250;
    else if (myValidCount > opValidCount)
        MobEval = (100.0 * myValidCount) / (myValidCount + opValidCount);
    else if (myValidCount < opValidCount)
        MobEval = -(100.0 * opValidCount) / (myValidCount + opValidCount);
    else MobEval = 0;

    int loseFlag = 0;
    if (board.statusCount[board.sideFlag] == 0)
        loseFlag = -1;
    else if (board.statusCount[!board.sideFlag] == 0)
        loseFlag = 1;

    //Weighed Evaluation
    double Eval =
        (0.8*BWRateEval) +
        (8.0*CornerEval) +
        (3.8*DCornerEval) +
        (0.8*MobEval) +
        (0.7*FrontierRateEval) +
        (0.1*CharaEval) +
        (1000 * loseFlag);

    return Eval;

}

bool cmpBoard(const Board &A, const Board &B) { return A > B; }
bool rcmpBoard(const Board &A, const Board &B) { return A < B; }
bool cmpCoordV(const Coord &A, const Coord &B) { return A.value > B.value; }
bool rcmpCoordV(const Coord &A, const Coord &B) { return A.value < B.value; }
bool cmpCoordC(const Coord &A, const Coord &B) { return A.chara > B.chara; }
bool rcmpCoordC(const Coord &A, const Coord &B) { return A.chara < B.chara; }
