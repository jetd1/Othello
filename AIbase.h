#ifndef _AIBASE
#define _AIBASE

#include "base.h"


extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];

bool cmpBoard(const Board &A, const Board &B);
bool rcmpBoard(const Board &A, const Board &B);
bool cmpCoordV(const Coord &A, const Coord &B);
bool rcmpCoordV(const Coord &A, const Coord &B);
bool cmpCoordC(const Coord &A, const Coord &B);
bool rcmpCoordC(const Coord &A, const Coord &B);

double AIBoardEval(Board &tmpBoard, bool AISide);



#endif 
