#ifndef JACOB_H
#define JACOB_H

#include "base.h"
#include "ctime"

#define ALPHA -3000

#define BETA 3000

#define MINWINDOW 10

#define TIME_OUT 100

#define RANDFACTOR 16

#define MULTI_THREAD true

#if SIDE_LENGTH==8
short coordChara[SAFE_LENGTH][SAFE_LENGTH] =
{
    {-8,-8,-8,-8,-8,-8,-8,-8,-8,-8},
    {-8,20,-3,11, 8, 8,11,-3,20,-8},
    {-8,-3,-7,-4, 1, 1,-4,-7,-3,-8},
    {-8,11,-4, 2, 2, 2, 2,-4,11,-8},
    {-8, 8, 1, 2,-3,-3, 2, 1, 8,-8},
    {-8, 8, 1, 2,-3,-3, 2, 1, 8,-8},
    {-8,11,-4, 2, 2, 2, 2,-4,11,-8},
    {-8,-3,-7,-4, 1, 1,-4,-7,-3,-8},
    {-8,20,-3,11, 8, 8,11,-3,20,-8},
    {-8,-8,-8,-8,-8,-8,-8,-8,-8,-8}
};

#else
short coordChara[SAFE_LENGTH][SAFE_LENGTH]{};
#endif

double ABReturn[3];
Coord bestCoord[3];
clock_t startTime;
double ABLast = 0;
double BWFACTOR, CNFACTOR, DCFACTOR;

extern Coord inputCoord;
extern Board gameBoard;
extern short maxDepth, passCount;
extern bool debugFlag, playerSide, randomFlag;
extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];

extern void fatalError(unsigned);

Coord RandomJacob(Board&);
Coord multiThreadABSearch(Board&);
Coord AI(Board &board);
double BoardEval(Board&);
double ABJacob(Board &board = gameBoard, short depth = maxDepth, double alpha = ALPHA, double beta = BETA, short r = 0);

bool cmpBoard(const Board&, const Board&);
bool rcmpBoard(const Board&, const Board&);
bool cmpCoordV(const Coord&, const Coord&);
bool rcmpCoordV(const Coord&, const Coord&);
bool cmpCoordC(const Coord&, const Coord&);
bool rcmpCoordC(const Coord&, const Coord&);



#endif 
