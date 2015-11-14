#pragma once

#define AI_MODE true
#define NON_AI_MODE false

#define SIDE_LENGTH 8
#define SAFE_LENGTH SIDE_LENGTH+2

string coord;

int inputX, inputY;
int stoneCount[4];
int passCount;

int dir[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

bool modeFlag, assistFlag, sideFlag, inputFlag, userSide;

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
status board[SAFE_LENGTH][SAFE_LENGTH];	       //White=false & Black=true
                                               //ifstream fin;

vector<string> validCoord;

void selectMode(), isAssistMode(), selectSide(), fatalError(unsigned ErrorCode), init(), othelloMain(), getCoord(getType T), move(int x, int y, status board[SAFE_LENGTH][SAFE_LENGTH]), output(), setValid(status board[SAFE_LENGTH][SAFE_LENGTH]), count(status board[SAFE_LENGTH][SAFE_LENGTH]), judge();
bool isValid(int x, int y, bool side, status board[SAFE_LENGTH][SAFE_LENGTH]), inRange(int p, int q);
string input(), AI();

