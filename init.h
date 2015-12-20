#ifndef INIT_H
#define INIT_H

#include "elements.h"

bool firstRun = true;

void menu();
void selectSide();
void isAssistMode();
void AchillesInit(short);
void debugMenu();
void theme();
void selectLang();
void settings();
short selectdiff();

extern void help();
extern void autoPlay(short, short);
extern void fatalError(unsigned);
extern void autoPlayThread(short, short);
extern void gameThread(playerType, playerType);

#endif
