#ifndef _EXT
#define _EXT

#include "base.h"

#define AI_MODE true
#define NON_AI_MODE false

#define SIDE_LENGTH 8
#define SAFE_LENGTH SIDE_LENGTH+2

#define START_COORD_X '1'
#define END_COORD_X '0'+SIDE_LENGTH
#define START_COORD_Y 'A'
#define END_COORD_Y '@'+SIDE_LENGTH



extern short dir[8][2];

extern short passCount;
extern bool modeFlag, assistFlag, sideFlag, inputFlag, playerSide;

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid };

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

extern Cell NULLCELL[SAFE_LENGTH][SAFE_LENGTH];

extern sBoard gameBoard;
extern Coord inputCoord;

extern vector<Coord> validCoord;


//In init.cpp
extern void init();
extern void selectMode();
extern void selectSide();
extern void isAssistMode();

//In error.cpp
extern void fatalError(unsigned ErrorCode);

//In main.cpp
extern void othelloMain();

//In IO.cpp
extern Coord input();
extern void output();
extern void getCoord(getType T);

//In operations.cpp
extern void judge();
extern bool inline inRange(int p, int q);
extern bool isValid(sBoard &board, Coord &pos, bool side);
extern void count(sBoard &board);
extern void setValid(sBoard &board, bool side);
extern void move(sBoard &board, Coord &pos, bool side);

//In AI.cpp
extern Coord AI(sBoard &board, bool side);




#endif