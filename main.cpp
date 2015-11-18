/*
Othello For Term Task
Version 0.9.9.9
*/
#include "elements.h"
#include "UI.h"
#include <thread>

short passCount, turnCount;

bool UIFlag, debugFlag, AIFlag, assistFlag, inputFlag, playerSide;

Coord inputCoord;

Board gameBoard;

extern bool drawable;

//in main.cpp
void multiThread(int argc, char **argv);
void othelloMain();

//In init.cpp
void menu();
void init();
void selectSide();
void isAssistMode();

//In error.cpp
void fatalError(unsigned ErrorCode);

//In main.cpp
void othelloMain();

//In IO.cpp
void loadGame();
Coord mouseInput();
Coord keyboardInput();
void getCoord(getType T);

//In operations.cpp
void judge();
bool inline inRange(int p, int q);

//In AI.cpp
Coord AI(Board &board, bool AIside);

//In UI.cpp


int main(int argc, char **argv)
{
    UIFlag = false;
    debugFlag = false;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][1] == 'c')
            UIFlag = false;
        if (argv[i][1] == 'd')
            debugFlag = true;
    }

    menu();

    multiThread(argc, argv);
}

void multiThread(int argc, char **argv)
{
    if (UIFlag)
    {
        thread draw(initdraw, argc, argv);
        thread game(othelloMain);
        draw.join();
        game.join();
    }
    else
        othelloMain();
}

void othelloMain()
{
    gameBoard.print();
    while (gameBoard.statusCount[Empty] && passCount < 2 && gameBoard.statusCount[Black] && gameBoard.statusCount[White])
    {
        if(UIFlag)
            while (drawable)
            {
                SLP(100);
            }

        //No-valid situation handle
        if (!gameBoard.statusCount[Valid])
        {
            if (AIFlag == NON_AI_MODE || (AIFlag == AI_MODE &&gameBoard.sideFlag == playerSide)) 
                cout << "No Possible Move, Enter to Pass!";
            else 
                cout << "Computer Passed, Enter to Your Turn!";
            PAUSE;

            passCount++;
            gameBoard.flipSide();
            gameBoard.setValid();
            gameBoard.count();
            gameBoard.print();
            continue;
        }
 
        ////Get input
        if (AIFlag == NON_AI_MODE || gameBoard.sideFlag == playerSide)
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

        gameBoard.move(inputCoord);   //Move will auto flip side and refresh the board
        gameBoard.print();
        if (UIFlag)
        {
            drawable = true;
            glutPostRedisplay();
            passCount = 0;
        }
    }

    judge();
    menu();
}
