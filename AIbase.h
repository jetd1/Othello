#ifndef _AIBASE
#define _AIBASE

#include "base.h"


extern short initCoordChara[SAFE_LENGTH][SAFE_LENGTH];

bool cmpBoard(const Board &A, const Board &B);

bool rcmpBoard(const Board &A, const Board &B);

bool cmpCoord(const Coord &A, const Coord &B);

bool rcmpCoord(const Coord &A, const Coord &B);



#endif 
