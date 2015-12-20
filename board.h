#ifndef BOARD_H
#define BOARD_H

#include "elements.h"
#include <ctime>

extern void fatalError(unsigned);
extern void AchillesInit(short);

inline bool cmpCoord(const Coord &A, const Coord &B) { return coordValue[A.x][A.y] > coordValue[B.x][B.y]; }

extern clock_t startTime;
extern const short coordValue[10][10];

const short dir[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

#endif
