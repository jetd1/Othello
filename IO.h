#ifndef IO_H
#define IO_H

#include "elements.h"

int mouseMove = 0;
short xBuffer[10], yBuffer[10];
bool mouseInputAvalable = false;

extern Board gameBoard;
extern Coord inputCoord;
extern short maxDepth, diff;
extern bool UIFlag, debugFlag, inputFlag, assistFlag, AIFlag, playerSide, saveError;

Coord mouseInput();
Coord keyboardInput();
void help();
void loadGame();
void printVersion();
void getCoord(getType);
void mouseKey(int, int, int, int);

extern Coord AI(Board&);
extern void menu();
extern void init();
extern void JacobInit(short);
extern void multiThread(int, char**);
extern void fatalError(unsigned);



extern int screenSize;




#endif
