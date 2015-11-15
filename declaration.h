#ifndef _DECL
#define _DECL

#define AI_MODE true
#define NON_AI_MODE false

#define SIDE_LENGTH 8
#define SAFE_LENGTH SIDE_LENGTH+2

#include "base.h"

short passCount;

short dir[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

bool modeFlag, assistFlag, sideFlag, inputFlag, playerSide;

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
	                                           //White=false & Black=true
struct Coord
{
    short x;
    short y;
};

struct Cell
{
    Coord pos;
    status stat;
    short value;
};

struct sBoard
{
    Cell cell[SAFE_LENGTH][SAFE_LENGTH];
    short statusCount[4];
    short value;
};

Cell NULLCELL[SAFE_LENGTH][SAFE_LENGTH]{};

sBoard gameBoard;

Coord inputCoord;

vector<Coord> validCoord;


//In init.cpp
void init();
void selectMode();
void selectSide();
void isAssistMode();

//In error.cpp
void fatalError(unsigned ErrorCode);

//In main.cpp
void othelloMain();

//In IO.cpp
Coord input();
void output();
void getCoord(getType T);

//In operations.cpp
void judge();
bool inline inRange(int p, int q);
bool isValid(sBoard &board, Coord &pos, bool side);
void count(sBoard &board);
void setValid(sBoard &board, bool side);
void move(sBoard &board, Coord &pos, bool side);


//In AI.cpp
Coord AI(sBoard &board, bool side);

//In UI.cpp


#endif