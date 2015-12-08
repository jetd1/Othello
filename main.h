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
extern bool drawable,debugCalled,autoFlag;
extern double ABReturn;

int main(int, char**);
void gameThread(int, char**);
void othelloMain();
void autoPlayThread(int, char**);
void autoPlay();
void judge();

extern void menu();
extern void selectDiff();
extern void AchillesInit(short);
extern void getCoord(playerType);
extern void initUI(int, char**);


#endif // MAIN_H
