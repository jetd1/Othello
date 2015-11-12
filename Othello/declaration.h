#pragma once

string coord;

int inputX, inputY;
int passCount, emptyCount, blackCount, whiteCount, validCount;
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

bool assistFlag, sideFlag, inputFlag;

enum getType { Human, Computer };
enum status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
status board[10][10];						   //White=false & Black=true
//ifstream fin;

void isAssistMode(), isAfatalError(), init(), othelloMain(), getCoord(getType T), move(int x, int y), output(), setValid(), stoneCount(), judge();
bool isValid(int x, int y, bool side), inRange(int p, int q);
string input(), AI();
