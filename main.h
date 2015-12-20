#ifndef MAIN_H
#define MAIN_H

#include "elements.h"

int main(int, char**);
void gameThread(playerType, playerType);
void othelloMain(playerType, playerType);
void autoPlayThread(short, short);
void autoPlay(short, short);
void judge();

extern void menu();
extern short selectdiff();
extern void displayThread(int, char**);
extern void AchillesInit(short);
extern void getCoord(playerType);
extern void fatalError(unsigned);


#endif
