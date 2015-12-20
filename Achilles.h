#ifndef Achilles_H
#define ACHILLES_H

#include "base.h"
#include <ctime>
#include <climits>

#define ALPHA INT_MIN

#define BETA INT_MAX

#define MINWINDOW 1

#define TIME_OUT 8

#define RANDFACTOR 24

const short coordValue[10][10] =
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

clock_t startTime;
double BWFACTOR[2];
double CNFACTOR[2];
double DCFACTOR[2];
double SDFACTOR;
double MBFACTOR;
double FRFACTOR;
double CRFACTOR;

Coord Hector(Board&);
Coord CallAI(Board&);
double BoardEval(Board&);
double Achilles(Board &board = Game::board, 
    short depth = Game::maxDepth,
    double alpha = ALPHA, double beta = BETA,
    Coord &bestCoord = Game::inputCoord);



#endif 
