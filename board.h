#ifndef BOARD_H
#define BOARD_H

#include "elements.h"
#include <ctime>

inline bool inRange(int, int);

extern void fatalError(unsigned);
extern bool cmpCoord(const Coord&, const Coord&);

extern short diff;
extern clock_t startTime;
extern short coordChara[10][10];
extern bool debugFlag, assistFlag, AIFlag, playerSide, cPass;

short dir[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

#endif
