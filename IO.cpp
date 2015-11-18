#include "elements.h"
#include <iomanip>

int mouseButton = 0;
int mouseinput = 0;
short int xbuffer[10], ybuffer[10];
bool canmouseinput = false;

extern bool inputFlag, assistFlag, modeFlag, sideFlag, playerSide;
extern Board gameBoard;
extern Coord inputCoord;

extern Coord AI(Board &board, bool side);
extern void fatalError(unsigned ErrorCode);

extern int screenSize;

void printVersion()
{
    cout << "Othello Main Version " << MAIN_VERSION << endl;
    cout << "AI Version " << AI_VERSION << endl << endl ;
    cout << "Copyleft 2015" << endl;
    cout << endl << endl << endl;
}

// Mouse Callback
void mouseKey(int button, int state, int x, int y){
    if (!canmouseinput) return;
    if (state != GLUT_DOWN) return;
    ybuffer[mouseinput] = (x / (screenSize / 8)) + 1;
    xbuffer[mouseinput] = (y / (screenSize / 8)) + 1;
    mouseinput++;
    canmouseinput = false;
    return;
}

Coord input() //For human input
{
    inputFlag = false;
    canmouseinput = true;
    while (mouseinput == 0) SLP(100);
    Coord tmpCoord{xbuffer[mouseinput-1], ybuffer[mouseinput-1]};
    mouseinput--;
    inputFlag = true;
    return tmpCoord;
}

void getCoord(getType T)
{
    switch (T)
    {
        case Player:
            inputCoord = input();
            break;
        case Computer:
            inputCoord = AI(gameBoard, !playerSide);
            break;
        default:
            fatalError(1);
    }
}
