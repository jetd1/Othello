/*
Othello For Term Task
Version 1.2.2
*/
#include "elements.h"
#include <thread>

short maxDepth;

short passCount;

bool UIFlag, debugFlag, AIFlag, assistFlag, inputFlag, playerSide, saveError, manualFlag, randomFlag;

Coord inputCoord;

Board gameBoard;

aiType AIType;

Coord passCoord = {-1, -1};

extern bool drawable;

extern double ABReturn[3];

//in main.cpp
void multiThread(int argc, char **argv);
void othelloMain();

//In init.cpp
void menu();
void init();
void selectSide();
void isAssistMode();
void JacobInit(short diff);

//In error.cpp
void fatalError(unsigned ErrorCode);

//In IO.cpp
void loadGame();
Coord mouseInput();
Coord keyboardInput();
void getCoord(getType T);

//In operations.cpp
void judge();

//In AI.cpp
Coord AI(Board &board);
double BoardEval(Board &board);
Coord RandomJacob(Board &board);
double ABJacob(Board &board, short depth, double alpha, double beta, short r);

//In UI.cpp
void initUI(int argc, char **argv);


int main(int argc, char **argv)
{
    randomFlag = false;
    manualFlag = false;
    UIFlag = false;
    debugFlag = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][1] == 'u')
            UIFlag = true;
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
        thread UI(initUI, argc, argv);
        thread game(othelloMain);
        UI.join();
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
        if (UIFlag)
            while (drawable)
                SLP(100);

        //No-valid situation handle
        if (!gameBoard.statusCount[Valid])
        {
            if (AIFlag == NON_AI_MODE || (AIFlag == AI_MODE &&gameBoard.sideFlag == playerSide))
                cout << "No Possible Move, Enter to Pass!";
            else
                cout << "Jacob Passed, Enter to Your Turn!";
            PAUSE;

            gameBoard.movesRecord.push_back(passCoord);
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
                    cout << "Invalid Position! Your input is " << inputCoord.x << char(inputCoord.y + '@') << endl;
                else if (!saveError)
                    cout << "Invalid Input!" << endl;

                getCoord(Player);
            }
        }
        else getCoord(Computer);

        gameBoard.move(inputCoord);   //Move will auto flip side and refresh the board
        gameBoard.print();
        if (debugFlag)
        {
            ios::sync_with_stdio(false);
            for (int i = 0; i < 3; i++)
                cout << ABReturn[i] << endl;
        }

        passCount = 0;

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
