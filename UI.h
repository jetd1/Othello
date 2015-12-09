#ifndef UI_H
#define UI_H

#include "elements.h"

const double M_PI = 3.14159265358979323846;
const int CIRCLE_MAX = 50;
int screenSize = 400;
volatile bool drawable = true;

extern Board gameBoard;
extern bool AIFlag, assistFlag, inputFlag, playerSide;

void initDisplay();
void drawCircle(double, double, double, Status);
void drawPlus(double, double, double);
void drawCell(double, double, Status);
void drawBoard();
void drawStone();
void display();
void reshape(int, int);
void initUI(int, char**);

extern void fatalError(unsigned);
extern void mouseKey(int, int, int, int);

#endif