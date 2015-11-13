#pragma once

extern string coord;

extern int dir[8][2];
extern int inputX, inputY;
extern int stoneCount[4];

extern int passCount;
extern bool modeFlag, assistFlag, sideFlag, inputFlag, userSide;

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid }; 
extern status board[10][10];						

extern vector<string> validCoord;

extern void selectMode(), isAssistMode(), selectSide(), fatalError(unsigned ErrorCode), init(), othelloMain(), getCoord(getType T), move(int x, int y, status board[10][10]), output(), setValid(status board[10][10]), count(status board[10][10]), judge();
extern bool isValid(int x, int y, bool side, status board[10][10]), inRange(int p, int q);
extern string input(), AI();
