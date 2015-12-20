#ifndef MODEL_H
#define MODEL_H

#include "elements.h"
#include "base.h"
#include <ctime>
#include <vector>

vector<Stone> stoneList;
double lightDirAngle = 0;
double xcenter = 0.0, ycenter = 0.0, zcenter = 0.0;
int liftingTableTime = 0;
double emulateTimes = 5.0;

extern bool isFocus;
extern GLfloat fogColorFocus[];
extern float fogDensity;
extern double theta, fai;

#endif // MODEL_H
