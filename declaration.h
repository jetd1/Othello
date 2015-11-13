#pragma once

string coord;

int inputX, inputY;
int stoneCount[4];
int passCount;
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

bool modeFlag, assistFlag, sideFlag, inputFlag, userSide;

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
status board[10][10];						   //White=false & Black=true
//ifstream fin;

vector<string> validCoord;

void selectMode(), isAssistMode(), selectSide(), fatalError(unsigned ErrorCode), init(), othelloMain(), getCoord(getType T), move(int x, int y, status board[10][10]), output(), setValid(status board[10][10]), count(status board[10][10]), judge();
bool isValid(int x, int y, bool side, status board[10][10]), inRange(int p, int q);
string input(), AI();
