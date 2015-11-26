#ifndef INIT_H
#define INIT_H

#include "elements.h"

void menu();
void init();
void selectSide();
void selectDiff();
void isAssistMode();
void JacobInit(short);
void debugMenu();
void theme();

extern void help();
extern void printVersion();
extern void fatalError(unsigned);
extern void multiThread(int, char**);
extern void loadGame(string loadName = "Othello", int undoSteps = 0);

short diff, passCount;
bool debugCalled = false;

extern Board gameBoard;
extern short maxDepth, sidePass;
extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];
extern double BWFACTOR, CNFACTOR, DCFACTOR;
extern bool assistFlag, AIFlag, UIFlag, playerSide, manualFlag, randomFlag, debugFlag, cPass;

#endif
