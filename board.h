#ifndef BOARD_H
#define BOARD_H

#include "elements.h"
#include "ctime"

inline bool inRange(int, int);

extern void fatalError(unsigned);
extern bool cmpCoordV(const Coord&, const Coord&);

extern short diff;
extern Cell NULLCELL;
extern short dir[8][2];
extern short passCount;
extern clock_t startTime;
extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];
extern bool debugFlag, assistFlag, AIFlag, playerSide, cPass;

#endif;