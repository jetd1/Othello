/*
Othello For Term Task
Version 1.7
*/
#include "main.h"
#include <thread>


int main(int argc, char **argv)
{

#ifdef WINDOWS_
    system("title=JetOthello CMDL V1.7");
    system("mode con cols=58 lines=34");
    system("color 0F");
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

    gameThread(argc, argv);
}

void gameThread(int argc, char **argv)
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
    while (!gameEnd())
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

            passCount++;
            sidePass++;
            gameBoard.move(passCoord);
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
                else if (!saveError&&!debugCalled)
                    cout << "                Invalid Input!" << endl;
                else
                    debugCalled = false;

                getCoord(Player);
            }
        }
        else getCoord(Computer);

        gameBoard.move(inputCoord);   //Move will auto flip side and refresh the board
        gameBoard.print();

        if (AIFlag == AI_MODE&&~gameBoard == !playerSide)
            cout << "            Jacob Thinking ...";

        if (debugFlag)
            for (int i = 0; i < 3; i++)
                cout << ABReturn[i] << endl;

        sidePass = 0;
        cPass = false;

        if (UIFlag)
        {
            drawable = true;
            glutPostRedisplay();
            sidePass = 0;
        }
    }

    judge();
    menu();
}

void autoPlay()
{
    randomFlag = true;
    short delayDur = 300;

    CLS;
    inputFlag = true;

    short aDiff[2]{};
    cout << "Please Set Mode of Jacob Playing Black" << endl << endl;
    selectDiff();
    aDiff[Black] = diff;
    CLS;
    cout << "Please Set Mode of Jacob Playing White" << endl << endl;
    selectDiff();
    aDiff[White] = diff;

    gameBoard.print();
    SLP(500);
    while (!gameEnd())
    {
        SLP(delayDur);
        JacobInit(aDiff[~gameBoard]);
        if (gameBoard(Valid))
        {
            getCoord(Computer);
            sidePass = 0;
        }
        else
        {
            inputCoord = passCoord;
            sidePass++;
        }
        gameBoard.move(inputCoord);
        gameBoard.print();
        gameBoard.recordPrint();
    }

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
            cout << "    You Defeated Jacob! Congratulations!" << endl << endl;
        else if (gameBoard(playerSide) < gameBoard(!playerSide))
            cout << "           Too Young too Simple!" << endl << endl;
        else
            cout << "   Tie! Jacob Want to Play Again With You." << endl << endl;
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

inline bool gameEnd()
{
    return !((gameBoard(Empty) + gameBoard(Valid)) && sidePass < 2 && gameBoard(Black) && gameBoard(White));
}