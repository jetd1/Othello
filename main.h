#ifndef MAIN_H
#define MAIN_H

#include "elements.h"

Coord passCoord = {-1, -1};

Coord inputCoord;
Board gameBoard;
short maxDepth;
bool UIFlag, debugFlag, AIFlag, assistFlag, inputFlag, playerSide, saveError, manualFlag, randomFlag, cPass;

extern Coord passCoord;
extern int ALPHA, BETA;
extern short diff;
extern bool debugCalled, autoFlag;
extern double ABReturn;
extern volatile bool drawable;

int main(int, char**);
void gameThread(playerType, playerType);
void othelloMain(playerType, playerType);
void autoPlayThread(short, short);
void autoPlay(short, short);
void judge();

extern void menu();
extern short selectDiff();
extern void AchillesInit(short);
extern void getCoord(playerType);
extern void initUI(int, char**);
extern void fatalError(unsigned);


#endif // MAIN_H
