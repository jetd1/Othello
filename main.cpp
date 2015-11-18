/*
Othello For Term Task
Version 0.9.9
*/
#include "elements.h"
#include "draw.h"
#include <thread>

short passCount, turnCount;

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
void getCoord(getType T);

//In operations.cpp
void judge();
bool inline inRange(int p, int q);

//In AI.cpp
Coord AI(Board &board, bool AIside);

//In draw.cpp
extern bool drawable;


int main(int argc, char **argv)
{
    init();
    thread draw(initdraw, argc, argv);
    thread game(othelloMain);
    draw.join();
    game.join();
    PAUSE;
}

void othelloMain()
{
    gameBoard.print();
    while (gameBoard.statusCount[Empty] && passCount < 2 && gameBoard.statusCount[Black] && gameBoard.statusCount[White])
    {

        while (drawable)
        {
            SLP(100);
        }

        //No-valid situation handle
        if (!gameBoard.statusCount[Valid])
        {
            if (modeFlag == NON_AI_MODE || (modeFlag == AI_MODE &&sideFlag == playerSide))
                cout << "No Possible Move, Enter to Pass!";
            else
                cout << "Computer Passed, Enter to Your Turn!";
            PAUSE;

            passCount++;
            sideFlag ^= 1;
            gameBoard.setValidFor(sideFlag);
            gameBoard.count();
            gameBoard.print();
            continue;
        }

        ////Get input
        if (modeFlag == NON_AI_MODE || sideFlag == playerSide)
        {
            getCoord(Player);
            while (!inputFlag || gameBoard[inputCoord.x][inputCoord.y].stat != Valid)
            {

                if (inputFlag)
                    cout << "Invalid Position! Your input is " << inputCoord.x << " " << inputCoord.y << endl;
                else
                    cout << "Invalid Input!" << endl;

                getCoord(Player);
            }
        }
        else getCoord(Computer);

        ////Refresh board
        gameBoard.move(inputCoord, sideFlag);   //Move will auto refresh the board now
        sideFlag ^= 1;
        gameBoard.print();
        drawable = true;
        glutPostRedisplay();
        passCount = 0;
    }
    judge();
}
