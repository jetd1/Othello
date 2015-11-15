#ifndef _AIBASE
#define _AIBASE

#include "base.h"


extern short initCoordChara[SAFE_LENGTH][SAFE_LENGTH];

bool cmpBoard(Board &A, Board &B);

bool rcmpBoard(Board &A, Board &B);

bool cmpCoord(Coord &A, Coord &B);

bool rcmpCoord(Coord &A, Coord &B);



#endif 
