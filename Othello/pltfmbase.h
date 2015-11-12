#pragma once

//cross-platform implement
#define PAUSE cin.get();cin.get();

#ifdef _WIN32
#include <windows.h>
#define CLS system("cls")
#define SLP(X) Sleep(X)
#endif


#ifdef linux
#include <unistd.h>
#define CLS system("clear")
#define SLP(X) usleep(X)
#endif


//GLUT flaw fix
#ifndef GLUT_DISABLE_ATEXIT_HACK
#define GLUT_DISABLE_ATEXIT_HACK
#endif
