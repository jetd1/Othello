#ifndef BASE_H
#define BASE_H

////Cross-platform implement
#define PAUSE cin.clear();cin.sync();cin.get();cin.get()

//OpenGL flaw fix
#ifndef GLUT_DISABLE_ATEXIT_HACK
#define GLUT_DISABLE_ATEXIT_HACK
#endif

//Platform auto detect
#ifdef _WIN32
#include <windows.h>
#ifndef NDEBUG
#define NDEBUG
#include "freeglut/include/GL/freeglut.h"
#undef NDEBUG
#else
#include "freeglut/include/GL/freeglut.h"
#endif
#ifdef _WIN64
#pragma comment(lib, "freeglut64.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif
#define CLS system("cls")
#define SLP(X) Sleep(X)
#define WINDOWS_

#elif defined __linux__
#include <unistd.h>
#ifndef NDEBUG
#define NDEBUG
#include "freeglut/include/GL/freeglut.h"
#undef NDEBUG
#else
#include "freeglut/include/GL/freeglut.h"
#endif
#define CLS system("clear")
#define SLP(X) usleep(1000*X)

#elif defined __APPLE__
#include <unistd.h>
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h> 
#define CLS system("clear")
#define SLP(X) usleep(1000*X)

#else
#define CLS fatalError(2)
#define SLP(X) fatalError(2)
#endif



////Common includes
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <cassert>

////Namespaces
using namespace std;


////Macro Arguments

//Version Information
#define MAIN_VERSION "3.0"
#define ACHILLES_VERSION "2.9"
#define PRINT_VERSION true

//Not Changeable
#define AI_MODE true
#define NON_AI_MODE false

#endif

