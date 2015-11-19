#ifndef BASE_H
#define BASE_H

////Cross-platform implement
#define PAUSE cin.clear();cin.sync();cin.get();cin.get()

//OpenGL flaw fix
#ifndef NDEBUG
#define NDEBUG
#endif
#ifndef GLUT_DISABLE_ATEXIT_HACK
#define GLUT_DISABLE_ATEXIT_HACK
#endif

//Platform auto detect
#ifdef _WIN32
#include <windows.h>
#include "freeglut_w/include/GL/freeglut.h"
#ifdef _WIN64
#pragma comment(lib, "freeglut64.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif
#define CLS system("cls")
#define SLP(X) Sleep(X)

#elif defined __linux__
#include <unistd.h>
#include "freeglut_l/include/GL/freeglut.h"
#define CLS system("clear")
#define SLP(X) usleep(1000*X)

#elif defined __APPLE__
#include <unistd.h>
#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h> 
#pragma comment(lib, "freeglut.lib")
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

////Namespaces
using namespace std;


////Macro Arguments

//Version Information
#define MAIN_VERSION "1.1"
#define AI_VERSION "1.0"
#define PRINT_VERSION true

//Not Changeable
#define AI_MODE true
#define NON_AI_MODE false

//Changeable
#define SIDE_LENGTH 8
#define SAFE_LENGTH SIDE_LENGTH+2

#define START_COORD_X '1'
#define END_COORD_X '0'+SIDE_LENGTH
#define START_COORD_Y 'A'
#define END_COORD_Y '@'+SIDE_LENGTH

#define ALPHA -200000
#define BETA 200000

#endif
