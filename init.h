#ifndef INIT_H
#define INIT_H

#include "elements.h"

void menu();
void init();
void selectSide();
void selectDiff();
void isAssistMode();
void AchillesInit(short);
void debugMenu();
void theme();

extern void help();
extern void autoPlay();
extern void printVersion();
extern void fatalError(unsigned);
extern void gameThread(int, char**);
extern void autoPlayThread(int, char**);
extern void loadGame(string loadName = "Othello", int undoSteps = 0);

short diff;
bool autoFlag = false, debugCalled = false, finalSearch = false;

extern Board gameBoard;
extern short maxDepth;
extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];
extern double BWFACTOR, CNFACTOR, DCFACTOR;
extern bool assistFlag, AIFlag, UIFlag, playerSide, manualFlag, randomFlag, debugFlag, cPass;

#endif
