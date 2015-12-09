/*
Othello For Term Task
Version 3.0
*/
#include "main.h"
#include <thread>


int main(int argc, char **argv)
{

#ifdef WINDOWS_
    system("title=JetOthello V2.0");
    system("mode con cols=50 lines=34");
    system("color 07");
#endif

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

    fatalError(1);
}

void gameThread(playerType B, playerType W)
{
    if (UIFlag)
    {
        thread UI(initUI, 0, nullptr);
        thread game(othelloMain, B, W);
        UI.join();
        game.join();
    }
    else
        othelloMain(B, W);
}

void othelloMain(playerType B, playerType W)
{
    playerType playerlist[2]{W,B};
    gameBoard.print();
    while (!gameBoard.end())
    {
        if (UIFlag)
            while (drawable)
                SLP(10);

        if (!gameBoard(Valid))
        {
            CLS;
            gameBoard.print();

            if (AIFlag == NON_AI_MODE || (AIFlag == AI_MODE &&~gameBoard == playerSide))
                cout << "      No Possible Move, Enter to Pass!";
            else
            {
                cout << "      Achilles Passed, Enter to Your Turn!";
                cPass = true;
            }

            PAUSE;

            gameBoard.move(passCoord);
            gameBoard.print();
            continue;
        }

        getCoord(playerlist[~gameBoard]);
        while (!inputFlag || gameBoard[inputCoord.x][inputCoord.y].stat != Valid)
        {
            if (inputFlag)
                cout << "       Invalid Position! Your input is " << inputCoord.x << char(inputCoord.y + '@') << endl;
            else if (!saveError&&!debugCalled)
                cout << "                Invalid Input!" << endl;
            else
                debugCalled = false;

            getCoord(playerlist[~gameBoard]);
        }

        gameBoard.move(inputCoord);
        gameBoard.print();

        if (AIFlag == AI_MODE&&~gameBoard == !playerSide)
            cout << "            Achilles Thinking ...";

        cPass = false;

        if (UIFlag)
        {
            drawable = true;
            glutPostRedisplay();
        }
    }

    judge();
    menu();
}

void autoPlayThread(short diffB, short diffW)
{
    if (UIFlag)
    {
        thread UI(initUI, 0, nullptr);
        thread game(autoPlay, diffB, diffW);
        UI.join();
        game.join();
    }
    else
        autoPlay(diffB, diffW);
}

void autoPlay(short diffB, short diffW)
{
    short delayDur = 0;

    inputFlag = true;

    short aDiff[2]{diffW,diffB};
    aDiff[Black] = diffB;
    aDiff[White] = diffW;

    gameBoard.print();
    SLP(0);
    while (!gameBoard.end())
    {
        if (UIFlag)
            while (drawable)
                SLP(1);

        SLP(delayDur);
        AchillesInit(aDiff[~gameBoard]);
        randomFlag = true;

        if (gameBoard(Valid))
            getCoord(AI);
        else
            inputCoord = passCoord;

        gameBoard.move(inputCoord);
        gameBoard.print();
        gameBoard.recordPrint();

        if (UIFlag)
        {
            drawable = true;
            glutPostRedisplay();
        }
    }

    inputFlag = false;
    autoFlag = false;
    randomFlag = false;

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
            cout << "    You Defeated Achilles! Congratulations!" << endl << endl;
        else if (gameBoard(playerSide) < gameBoard(!playerSide))
            cout << "           Too Young too Simple!" << endl << endl;
        else
            cout << "   Tie! Achilles Want to Play Again With You." << endl << endl;
    }
    else
    {
        if (gameBoard(Black) > gameBoard(White))
            cout << "                Black Win!" << endl << endl;
        else if (gameBoard(Black) < gameBoard(White))
            cout << "                White Win!" << endl << endl;
        else
            cout << "           Tie!" << endl << endl;
    }
    gameBoard.recordPrint();

    cout << endl << "       Press Any Key to Main Menu...";

    PAUSE;
}