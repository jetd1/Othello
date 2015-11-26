#ifndef MAIN_H
#define MAIN_H

#include "elements.h"

Coord passCoord = {-1, -1};

Coord inputCoord;
Board gameBoard;
short maxDepth, sidePass;
bool UIFlag, debugFlag, AIFlag, assistFlag, inputFlag, playerSide, saveError, manualFlag, randomFlag, cPass;

extern Coord passCoord;
extern int ALPHA, BETA;
extern short passCount, diff;
extern bool drawable,debugCalled;
extern double ABReturn[3];

int main(int, char**);
void gameThread(int, char**);
void othelloMain();
void autoPlay();
void judge();

inline bool gameEnd();

extern void menu();
extern void selectDiff();
extern void JacobInit(short);
extern void getCoord(getType);
extern void initUI(int, char**);


#endif // MAIN_H
