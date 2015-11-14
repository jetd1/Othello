#ifndef _DECL
#define _DECL

#define AI_MODE true
#define NON_AI_MODE false

#define SIDE_LENGTH 8
#define SAFE_LENGTH SIDE_LENGTH+2



int stoneCount[4];
int passCount;

int dir[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

bool modeFlag, assistFlag, sideFlag, inputFlag, playerSide;

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
	                                           //White=false & Black=true
struct Coord
{
    int x;
    int y;
};

struct Cell
{
    Coord pos;
    status stat;
    short value;
};

Cell board[SAFE_LENGTH][SAFE_LENGTH];

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
void count(Cell board[SAFE_LENGTH][SAFE_LENGTH]);
void setValid(Cell board[SAFE_LENGTH][SAFE_LENGTH], bool side);
void move(Coord pos, Cell board[SAFE_LENGTH][SAFE_LENGTH]);
bool inline inRange(int p, int q);
bool isValid(Coord pos, bool side, Cell board[SAFE_LENGTH][SAFE_LENGTH]);

//In AI.cpp
Coord AI(Cell board[SAFE_LENGTH][SAFE_LENGTH], bool side);

//In UI.cpp


#endif