/*
Jacob
A Powerful Othello AI
By Jet
Version 1.7.3
*/

//Even Block Estimate
//Stability

#include "elements.h"
#include "Jacob.h"
#include <thread>

//inline bool isWin(bool side, Board &board)
//{
//    return !board(!side) || (!(board(Empty) + board(Valid)) && board(side) > board(!side));
//}

//double ABJacob(Board &board, short depth, double alpha, double beta, short r)
//{
//    if (maxDepth == 0)
//    {
//        bestCoord[r] = RandomJacob(board);
//        return r;
//    }
//
//    if (isWin(!playerSide, board))
//        return BETA - 1;
//    if (isWin(playerSide, board))
//        return ALPHA + 1;
//    if (!depth || !board(Valid) || clock() - startTime > TIME_OUT)
//        return BoardEval(board);
//
//    double Eval;
//
//    for (int i = 0; i < board.validCoord.size(); i++) //i=1(PVS)
//    {
//        Board tmpBoard = board;
//        tmpBoard.move(board.validCoord[i]);
//
//        Eval = -ABJacob(tmpBoard, depth - 1, -beta, -alpha, r);
//        if (Eval >= beta)
//        {
//            if (depth == maxDepth)
//                bestCoord[r] = board.validCoord[i];
//            return (ABReturn[r] = beta);
//        }
//        if (Eval > alpha)
//        {
//            alpha = Eval;
//            if (depth == maxDepth)
//                bestCoord[r] = board.validCoord[i];
//        }
//    }
//    return (ABReturn[r] = alpha);
//}

double ABJacob(Board &board, short depth, double alpha, double beta, short r)
{
    if (maxDepth == 0)
    {
        bestCoord[r] = RandomJacob(board);
        return r;
    }

    //if (isWin(!playerSide, board))
    //    return BETA - 1;
    //if (isWin(playerSide, board))
    //    return ALPHA + 1;

    if (!depth || !board(Valid) || clock() - startTime > TIME_OUT * CLOCKS_PER_SEC)
        return BoardEval(board);

    double Eval;

    //PVS START
    Board mainTmp = board;
    mainTmp.move(board.validCoord[0]);

    Eval = -ABJacob(mainTmp, depth - 1, -beta, -alpha, r);
    if (Eval >= beta)
    {
        if (depth == maxDepth)
            bestCoord[r] = board.validCoord[0];
        return (ABReturn[r] = beta);
    }
    if (Eval > alpha)
    {
        alpha = Eval;
        if (depth == maxDepth)
            bestCoord[r] = board.validCoord[0];
    }
    //PVS END

    for (unsigned i = 1; i < board.validCoord.size(); i++) //i=1(PVS)
    {
        Board tmpBoard = board;
        tmpBoard.move(board.validCoord[i]);

        Eval = -ABJacob(tmpBoard, depth - 1, -alpha - MINWINDOW , -alpha, r);
        
        if (Eval > alpha&&Eval < beta)
        {
            Eval = -ABJacob(tmpBoard, depth - 1, -beta, -alpha - MINWINDOW , r);
        }
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
    return board.validCoord[rand()%board.validCoord.size()];
}

Coord multiThreadABSearch(Board &board)
{
    if (randomFlag&&!(rand() % RANDFACTOR))
        return RandomJacob(board);

    if(gameBoard.movesRecord.size() == 1)
        switch (inputCoord.x)
        {
            case 3:
            case 4:
                return{3,3};
                break;
            case 5:
            case 6:
                return{6,6};
                break;
            default:
                fatalError(1);
        }

   /* if (MULTI_THREAD)
    {
        ABReturn[0] = ABReturn[1] = ABReturn[2] = ALPHA;
        thread AB1(ABJacob, ref(board), maxDepth, ALPHA, LOWERA, 0);
        thread AB2(ABJacob, ref(board), maxDepth, LOWERA, LOWERB, 1);
        thread AB3(ABJacob, ref(board), maxDepth, LOWERB, BETA, 2);
        AB1.join();
        AB2.join();
        AB3.join();

        for (int i = 0; i < 3; i++)
            if (ABReturn[i] && ABReturn[i] != LOWERA && ABReturn[i] != LOWERB && board.isValid(bestCoord[i], !playerSide))
            {
                ABLast = ABReturn[i];
                return bestCoord[i];
            }

        for (int i = 0; i < 3; i++)
            if (ABReturn[i] != LOWERA && ABReturn[i] != LOWERB && board.isValid(bestCoord[i], !playerSide))
            {
                ABLast = ABReturn[i];
                return bestCoord[i];
            }

        ABLast = ABJacob(board, 4);
        return bestCoord[0];
    }
    else*/
    {
        ABJacob(board);

        if (bestCoord[0].x)
        {
            ABLast = ABReturn[0];
            return bestCoord[0];
        }

        return RandomJacob(board);
    }
}

Coord AI(Board &board)
{
    BWFACTOR = (playerSide == Black&&!(passCount % 2)) ? 0.80 : 0.70;
    CNFACTOR = (playerSide == Black&&!(passCount % 2)) ? 11.0 : 10.0;
    DCFACTOR = (playerSide == Black&&!(passCount % 2)) ? 3.80 : 3.70;
    startTime = clock();
    return multiThreadABSearch(board);
}

double BoardEval(Board &board)
{
    //Evaluation Based on Character Value
    double CharaEval;

    double myChara = board.allEval(~board);
    double opChara = board.allEval(!board);

    CharaEval = myChara - opChara;


    //Evaluation Based on Stone Rate
    double BWRateEval;

    short myStoneCount = board(~board);
    short opStoneCount = board(!board);

    if (myStoneCount > opStoneCount)
        BWRateEval = 100.0 * myStoneCount / (myStoneCount + opStoneCount);
    else if (myStoneCount < opStoneCount)
        BWRateEval = -100.0 * opStoneCount / (myStoneCount + opStoneCount);
    else BWRateEval = 0;


    //Evaluation Based on Stone Frontier Rate
    double FrontierRateEval;

    short myFrontierCount = board.frontierCount(~board);
    short opFrontierCount = board.frontierCount(!board);

    if (myFrontierCount > opFrontierCount)
        FrontierRateEval = -100.0 * myFrontierCount / (myFrontierCount + opFrontierCount);
    else if (myFrontierCount < opFrontierCount)
        FrontierRateEval = 100.0 * opFrontierCount / (myFrontierCount + opFrontierCount);
    else FrontierRateEval = 0;


    //Evaluation Based on Corner Stone Count
    double CornerEval;

    short myCornerCount =
        (board[1][1].stat == Status(~board)) +
        (board[1][SIDE_LENGTH].stat == Status(~board)) +
        (board[SIDE_LENGTH][1].stat == Status(~board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat == Status(~board));

    short opCornerCount =
        (board[1][1].stat == Status(!board)) +
        (board[1][SIDE_LENGTH].stat == Status(!board)) +
        (board[SIDE_LENGTH][1].stat == Status(!board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat == Status(!board));

    CornerEval = 25 * (myCornerCount - opCornerCount);


    //Evaluation Based on Dangerous Corner-Beside-Stone Count
    double DCornerEval;

    short myDCornerCount =
        (board[1][1].stat >= Empty) && (board[1][2].stat == Status(~board)) +
        (board[1][1].stat >= Empty) && (board[2][2].stat == Status(~board)) +
        (board[1][1].stat >= Empty) && (board[2][1].stat == Status(~board)) +
        (board[1][SIDE_LENGTH].stat >= Empty) && (board[1][SIDE_LENGTH - 1].stat == Status(~board)) +
        (board[1][SIDE_LENGTH].stat >= Empty) && (board[2][SIDE_LENGTH - 1].stat == Status(~board)) +
        (board[1][SIDE_LENGTH].stat >= Empty) && (board[2][SIDE_LENGTH].stat == Status(~board)) +
        (board[SIDE_LENGTH][1].stat >= Empty) && (board[SIDE_LENGTH][2].stat == Status(~board)) +
        (board[SIDE_LENGTH][1].stat >= Empty) && (board[SIDE_LENGTH - 1][1].stat == Status(~board)) +
        (board[SIDE_LENGTH][1].stat >= Empty) && (board[SIDE_LENGTH - 1][2].stat == Status(~board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board[SIDE_LENGTH][SIDE_LENGTH - 1].stat == Status(~board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board[SIDE_LENGTH - 1][SIDE_LENGTH - 1].stat == Status(~board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board[SIDE_LENGTH - 1][SIDE_LENGTH].stat == Status(~board));

    short opDCornerCount =
        (board[1][1].stat >= Empty) && (board[1][2].stat == Status(!board)) +
        (board[1][1].stat >= Empty) && (board[2][2].stat == Status(!board)) +
        (board[1][1].stat >= Empty) && (board[2][1].stat == Status(!board)) +
        (board[1][SIDE_LENGTH].stat >= Empty) && (board[1][SIDE_LENGTH - 1].stat == Status(!board)) +
        (board[1][SIDE_LENGTH].stat >= Empty) && (board[2][SIDE_LENGTH - 1].stat == Status(!board)) +
        (board[1][SIDE_LENGTH].stat >= Empty) && (board[2][SIDE_LENGTH].stat == Status(!board)) +
        (board[SIDE_LENGTH][1].stat >= Empty) && (board[SIDE_LENGTH][2].stat == Status(!board)) +
        (board[SIDE_LENGTH][1].stat >= Empty) && (board[SIDE_LENGTH - 1][1].stat == Status(!board)) +
        (board[SIDE_LENGTH][1].stat >= Empty) && (board[SIDE_LENGTH - 1][2].stat == Status(!board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board[SIDE_LENGTH][SIDE_LENGTH - 1].stat == Status(!board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board[SIDE_LENGTH - 1][SIDE_LENGTH - 1].stat == Status(!board)) +
        (board[SIDE_LENGTH][SIDE_LENGTH].stat >= Empty) && (board[SIDE_LENGTH - 1][SIDE_LENGTH].stat == Status(!board));


    DCornerEval = -12.5 * (myDCornerCount - opDCornerCount);

    //Evaluation Based on Stabilitrons
    //double stab


    //Evaluation Based on Mobility
    double MobEval;

    short myValidCount = board.countValidFor(~board);
    short opValidCount = board.countValidFor(!board);

    if (!opValidCount)
        MobEval = 150;
    else if (!myValidCount)
        MobEval = -400;
    else if (myValidCount > opValidCount)
        MobEval = (100.0 * myValidCount) / (myValidCount + opValidCount);
    else if (myValidCount < opValidCount)
        MobEval = -(100.0 * opValidCount) / (myValidCount + opValidCount);
    else MobEval = 0;




    int loseFlag = 0;
    if (board(!playerSide) == 0)
        loseFlag = -1;
    else if (board(playerSide) == 0)
        loseFlag = 1;


    //Weighed Evaluation
    double Eval =
        (BWFACTOR*BWRateEval) +
        (CNFACTOR*CornerEval) +
        (DCFACTOR*DCornerEval) +
        (1.10*MobEval) +
        (0.80*FrontierRateEval) +
        (0.10*CharaEval) +
        (200 * loseFlag);

    return Eval;

}

bool cmpBoard(const Board &A, const Board &B) { return A > B; }
bool rcmpBoard(const Board &A, const Board &B) { return A < B; }
bool cmpCoordV(const Coord &A, const Coord &B) { return A.value > B.value; }
bool rcmpCoordV(const Coord &A, const Coord &B) { return A.value < B.value; }
