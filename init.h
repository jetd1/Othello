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
extern void loadGame();
extern void printVersion();
extern void fatalError(unsigned);
extern void multiThread(int, char**);

short diff;

extern double BWFACTOR;
extern aiType AIType;
extern Board gameBoard;
extern short maxDepth, passCount;
extern short coordChara[SAFE_LENGTH][SAFE_LENGTH];
extern bool assistFlag, AIFlag, UIFlag, playerSide, manualFlag, randomFlag, debugFlag;

#endif
