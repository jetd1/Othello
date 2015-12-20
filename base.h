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
#include "GL/freeglut.h"
#undef NDEBUG
#else
#include "GL/freeglut.h"
#endif
#ifdef _WIN64
#pragma comment(lib, "freeglut64.lib")
#else
#pragma comment(lib, "freeglut.lib")
#endif
#define CLS system("cls")
#define SLP(X) Sleep(X)

#elif defined __linux__
#include <unistd.h>
#ifndef NDEBUG
#define NDEBUG
#include "GL/freeglut.h"
#undef NDEBUG
#else
#include "GL/freeglut.h"
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


const int BOARD_SIZE = 8;

const int LEFT_MOUSE_BUTTON = 0x0001;
const int MIDDLE_MOUSE_BUTTON = 0x0002;
const int RIGHT_MOUSE_BUTTON = 0x0004;

const int GLUT_WHEEL_UP = 3;
const int GLUT_WHEEL_DOWN = 4;

const int GRAVITY = 500;
const int DEFAULT_ZOOM = 11;
const int MAX_ZOOM = 20;
const int MIN_ZOOM = 7;
const double lambda = 0.2;
const double RESTITUTION = 0.8;
const double STONE_INTERVAL = 1.0;
const double STONE_RADIUS = 0.4;
const double STONE_HEIGHT = 0.2;
const int TABLE_SIZE = 10;
const int TABLE_HEIGHT = 3;
const double TABLE_THICKNESS = 0.7;
const int FLOOR_SIZE = 45;
const int FLOOR_SHADE_SIZE = 5;
const int FLOOR_CENTER_SIZE = (2 * FLOOR_SHADE_SIZE);
const double FLOOR_GRID_SIZE = 0.25;
const int FPS = 60;
const double TIME_UNIT = (1.0 / (100 * FPS));
const double REFRESH_UNIT = (1.0 / FPS);

ostream& endll(ostream& strm);

#endif

