/*
Othello For Term Task
Version 0.9.3
*/
#include "elements.h"

#define AI_MODE true
#define NON_AI_MODE false

#define SIDE_LENGTH 8
#define SAFE_LENGTH SIDE_LENGTH+2


short passCount;

bool modeFlag, assistFlag, sideFlag, inputFlag, playerSide;

Coord inputCoord;

vector<Coord> validCoord;

Board gameBoard;

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

//In AI.cpp
Coord AI(Board &board, bool side);

//In UI.cpp




int main()
{
    init();
    othelloMain();
    PAUSE;
}

void othelloMain()
{
    output();
    while (gameBoard.statusCount[Empty] && passCount < 2 && gameBoard.statusCount[Black] && gameBoard.statusCount[White])
    {
        ////No-valid situation handle
        if (!gameBoard.statusCount[Valid])
        {
            if (modeFlag == NON_AI_MODE || (modeFlag == AI_MODE &&sideFlag == playerSide)) cout << "No Possible Move, Enter to Pass!";
            else cout << "Computer Passed, Enter to Your Turn!";
            PAUSE;
            passCount++;
            sideFlag ^= 1;
            gameBoard.setValidFor(sideFlag);
            gameBoard.count();
            continue;
        }
 
        ////Get input
        if (modeFlag == NON_AI_MODE || sideFlag == playerSide)
        {
            getCoord(Player);
            while (!inputFlag || gameBoard.cell[inputCoord.x][inputCoord.y].stat != Valid)
            {
                if (inputFlag) cout << "Invalid Position!" << endl;
                else cout << "Invalid Input!" << endl;
                getCoord(Player);
            }
        }
        else getCoord(Computer);

        ////Refresh board
        gameBoard.move(inputCoord, sideFlag);
        sideFlag ^= 1;
        gameBoard.setValidFor(sideFlag);
        gameBoard.count();
        output();
        passCount = 0;
    }
    judge();
}