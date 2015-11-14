#pragma once

#define AI_MODE true
#define NON_AI_MODE false

#define SIDE_LENGTH 8
#define SAFE_LENGTH SIDE_LENGTH+2

#define START_COORD_X '1'
#define END_COORD_X '0'+SIDE_LENGTH
#define START_COORD_Y 'A'
#define END_COORD_Y '@'+SIDE_LENGTH

extern string coord;

extern int dir[8][2];
extern int inputX, inputY;
extern int stoneCount[4];

extern int passCount;
extern bool modeFlag, assistFlag, sideFlag, inputFlag, userSide;

enum getType { Player, Computer };
enum status { White, Black, Empty, Valid };
extern status board[SAFE_LENGTH][SAFE_LENGTH];

extern vector<string> validCoord;

extern void selectMode(), isAssistMode(), selectSide(), fatalError(unsigned ErrorCode), init(), othelloMain(), getCoord(getType T), move(int x, int y, status board[SAFE_LENGTH][SAFE_LENGTH]), output(), setValid(status board[SAFE_LENGTH][SAFE_LENGTH]), count(status board[SAFE_LENGTH][SAFE_LENGTH]), judge();
extern bool isValid(int x, int y, bool side, status board[SAFE_LENGTH][SAFE_LENGTH]), inRange(int p, int q);
extern string input(), AI();
