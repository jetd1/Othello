#ifndef _BASE
#define _BASE

////Cross-platform implement
#define PAUSE cin.get();cin.get();

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

#elif defined linux
#include <unistd.h>
#include "freeglut_l/include/GL/freeglut.h"
#pragma comment(lib, "freeglut.lib")
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
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>

////Namespaces
using namespace std;


#endif