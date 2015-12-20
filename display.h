#ifndef DISPLAY_H
#define DISPLAY_H

#define NDEBUG

#include "base.h"
#include "elements.h"

const double M_PI = 3.14159265358979323846;
const double step = 2.0 / BOARD_SIZE;
const double hstep = 1.0 / BOARD_SIZE;
const int CYSIDES = 50;

extern void refreshModel(bool lifting);
extern void timerCallback(int index);
extern void keyboardCallback(unsigned char key, int _x, int _y);
extern void keyboardUpCallback(unsigned char key, int _x, int _y);
extern void skeyboardCallback(int key, int _x, int _y);
extern void skeyboardUpCallback(int key, int _x, int _y);

extern vector<Stone> stoneList;
extern double xcenter, ycenter, zcenter;

int screenSize = 80 * BOARD_SIZE, screenWidth = 80 * BOARD_SIZE, screenHeight = 80 * BOARD_SIZE;
double zoom = DEFAULT_ZOOM;
double theta = -90.5, fai = 20.0;
double floatingx = 0.0, floatingy = 0.0;
float backGroundColor = 0.104f;
float fogDensity = 0.00f;
bool isFocus = false;
GLfloat fogColorPause[] = {backGroundColor, backGroundColor, backGroundColor, 1.0f};
GLfloat fogColorFocus[] = {0.1f, 0.15f, 0.2f, 0.0f};
char s_Save[] = "Save";
char s_Load[] = "Load";
char s_Save_and_Quit[] = "Save and Quit";
char s_Quit_without_saving[] = "Quit without Saving";

void initDisplay();
void drawStone();
void drawBackGround();
void display();
void reshape(int, int);
void displayThread(int, char**);

extern void mouseKey(int, int, int, int);
extern void mouseMotion(int, int);

#endif
