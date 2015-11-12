#pragma once

int inputX, inputY;
int passCount, emptyCount, blackCount, whiteCount, validCount;
bool assistFlag, sideFlag, inputFlag;
int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
enum status { White, Black, Empty, Valid };    //Then status<Empty: Have Stone on It, status>=Empty: Truly Empty
status board[10][10];						   //White=false & Black=true
//ifstream fin;

void fatalError(), init(), input(), othello(), move(int x, int y), output(), setValid(), stoneCount(), judge(), AI();
bool isValid(int x, int y, bool side), inRange(int p, int q);
