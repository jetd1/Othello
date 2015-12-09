#ifndef Achilles_H
#define ACHILLES_H

#include "base.h"
#include <ctime>
#define ALPHA INT_MIN

#define BETA INT_MAX

#define MINWINDOW 1

#define TIME_OUT 100

#define RANDFACTOR 24

#if 8==8
short coordChara[10][10] =
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
short coordChara[10][10]{};
#endif

double ABReturn;
clock_t startTime;
double ABLast = 0;
double BWFACTOR[2];
double CNFACTOR[2];
double DCFACTOR[2];
double SDFACTOR;
double MBFACTOR;
double FRFACTOR;
double CRFACTOR;

extern Coord inputCoord;
extern Board gameBoard;
extern short maxDepth;
extern bool debugFlag, playerSide, randomFlag, finalSearch;
extern short coordChara[10][10];

extern void fatalError(unsigned);

Coord Hector(Board&);
Coord CallAI(Board &board);
double BoardEval(Board&);
double Achilles(Board &board = gameBoard, short depth = maxDepth, double alpha = ALPHA, double beta = BETA, Coord &bestCoord = inputCoord);

bool cmpCoord(const Coord&, const Coord&);



#endif 
