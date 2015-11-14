#pragma once

////cross-platform implement
#define PAUSE cin.get();cin.get();

void fatalError();

#ifdef _WIN32
#include <windows.h>
#define CLS system("cls")
#define SLP(X) Sleep(X)
#elif defined  _WIN64
#include <windows.h>
#define CLS system("cls")
#define SLP(X) Sleep(X)
#elif defined linux
#include <unistd.h>
#define CLS system("clear")
#define SLP(X) usleep(X)
#elif defined __APPLE__
#include <unistd.h>
#define CLS system("clear")
#define SLP(X) usleep(X)
#else
#define CLS fatalError(2)
#define SLP(X) fatalError(2)
#endif


//GLUT flaw fix
#ifndef GLUT_DISABLE_ATEXIT_HACK
#define GLUT_DISABLE_ATEXIT_HACK
#endif


////common includes
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <GL/freeglut.h> //Header needed differs on other platforms


using namespace std;
