#ifndef INIT_H
#define INIT_H

#include "elements.h"

void menu();
void init();
void selectSide();
void isAssistMode();
void AchillesInit(short);
void debugMenu();
void theme();
short selectDiff();

extern void help();
extern void autoPlay(short, short);
extern void printVersion();
extern void fatalError(unsigned);
extern void autoPlayThread(short, short);
extern void gameThread(playerType, playerType);
extern void loadGame(string loadName = "Othello", int undoSteps = 0);

short diff;
bool autoFlag = false, debugCalled = false, finalSearch = false;

extern Board gameBoard;
extern short maxDepth;
extern short coordChara[10][10];
extern double BWFACTOR, CNFACTOR, DCFACTOR;
extern bool assistFlag, AIFlag, UIFlag, playerSide, manualFlag, randomFlag, debugFlag, cPass;

#endif
