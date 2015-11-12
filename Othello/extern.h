#pragma once

extern string coord;

extern int dir[8][2];
extern int inputX, inputY;
extern int passCount, emptyCount, blackCount, whiteCount, validCount;

extern bool assistFlag, sideFlag, inputFlag;

enum getType { Human, Computer };
enum status { White, Black, Empty, Valid }; 
extern status board[10][10];						  

extern void isAssistMode(), fatalError(), init(), othelloMain(), getCoord(getType T), move(int x, int y), output(), setValid(), stoneCount(), judge();
extern bool isValid(int x, int y, bool side), inRange(int p, int q);
extern string input(), AI();
