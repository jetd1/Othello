#ifndef JACOB_H
#define JACOB_H

#include "base.h"
#include "ctime"

double ABReturn[3];
Coord bestCoord[3];
clock_t startTime;
double BWFACTOR;

extern short maxDepth;
extern Board gameBoard;
extern aiType AIType;
extern double ALPHA, BETA, LOWERA, LOWERB;
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
