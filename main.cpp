/*
Othello For Term Task
Version 1.5
*/
#include "main.h"
#include <thread>


int main(int argc, char **argv)
{
    cPass = false;
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
    while (gameBoard(Empty) && passCount < 2 && gameBoard(Black) && gameBoard(White))
    {
        if (UIFlag)
            while (drawable)
                SLP(100);

        //No-valid situation handle
        if (!gameBoard(Valid))
        {
            CLS;
            gameBoard.print();

            if (AIFlag == NON_AI_MODE || (AIFlag == AI_MODE &&~gameBoard == playerSide))
                cout << "      No Possible Move, Enter to Pass!";
            else
            {
                cout << "      Jacob Passed, Enter to Your Turn!";
                cPass = true;
            }
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
        if (AIFlag == NON_AI_MODE || ~gameBoard == playerSide)
        {
            getCoord(Player);
            while (!inputFlag || gameBoard[inputCoord.x][inputCoord.y].stat != Valid)
            {

                if (inputFlag)
                    cout << "       Invalid Position! Your input is " << inputCoord.x << char(inputCoord.y + '@') << endl;
                else if (!saveError)
                    cout << "                Invalid Input!" << endl;

                getCoord(Player);
            }
        }
        else getCoord(Computer);

        gameBoard.move(inputCoord);   //Move will auto flip side and refresh the board
        gameBoard.print();

        if (AIFlag == AI_MODE&&~gameBoard == !playerSide)
            cout << "          Jacob Thinking ...";

        if (debugFlag)
            for (int i = 0; i < 3; i++)
                cout << ABReturn[i] << endl;

        passCount = 0;
        cPass = false;

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

void judge()
{
    CLS;
    gameBoard.print();
    if (AIFlag == AI_MODE)
    {
        if (gameBoard(playerSide) > gameBoard(!playerSide))
            cout << "    You Defeated Jacob! Congratulations!" << endl << endl;
        else if (gameBoard(playerSide) < gameBoard(!playerSide))
            cout << "           Too Young too Simple!" << endl << endl;
        else
            cout << "   Tie! Jacob Want to Play Again With You." << endl << endl;
    }
    else
    {
        if (gameBoard(Black) > gameBoard(White))
            cout << "        Black Win!" << endl << endl;
        else if (gameBoard(Black) < gameBoard(White))
            cout << "        White Win!" << endl << endl;
        else
            cout << "           Tie!" << endl << endl;
    }

    cout << endl << "       Press Any Key to Main Menu...";

    PAUSE;
}