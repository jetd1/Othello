#ifndef IO_H
#define IO_H

#include "elements.h"

Coord mouseInput();
Coord keyboardInput();
void help();
void getCoord(playerType);

extern Coord CallAI(Board&);
extern void menu();
extern void AchillesInit(short);
extern void gameThread(playerType, playerType);
extern void fatalError(unsigned);
extern void debugMenu();


int mouseButton = 0;
int kbstat[256]{};
bool needUndo = false;
volatile short xBuffer, yBuffer;
volatile bool hasMouseInput = false;

extern double theta, fai;
extern double floatingx, floatingy;
extern double zoom;
extern bool isFocus;
extern int screenWidth, screenHeight, screenSize;

#endif
