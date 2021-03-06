﻿/*
Othello For Term Task
Version 3.0
*/
#include "main.h"
#include <thread>

int main(int argc, char **argv)
{

#ifdef _WIN32
    system("mode con cols=50 lines=34");
    system("color 07");
#endif

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][1] == 'u')
            Game::UIFlag = true;
        if (argv[i][1] == 'd')
            Game::debugFlag = true;
    }
    menu();

    fatalError(1);
}

void gameThread(playerType B, playerType W)
{
    if (Game::UIFlag)
    {
        thread UI(displayThread, 0, nullptr);
        thread game(othelloMain, B, W);
        game.join();
    }
    else
        othelloMain(B, W);
}

void othelloMain(playerType B, playerType W)
{
    Game::status = Playing;
    playerType playerlist[2]{W,B};
    Game::board.print();
    while (!Game::board.end())
    {
        if (!Game::board(Valid))
        {
            CLS;
            Game::board.print();

            if (Game::AIFlag == NON_AI_MODE || (Game::AIFlag == AI_MODE &&~Game::board == Game::humanSide))
                cout << Game::mainLang.nposm;
            else
            {
                cout << Game::mainLang.aipass;
                Game::AIPass = true;
            }

            PAUSE;

            Game::board.move(Game::passCoord);
            Game::board.print();
            continue;
        }

        getCoord(playerlist[~Game::board]);
        while (!Game::inputFlag || Game::board[Game::inputCoord.x][Game::inputCoord.y].stat != Valid)
        {
            if (Game::inputFlag)
                cout << Game::mainLang.ip << Game::inputCoord.x << char(Game::inputCoord.y + '@') << endl;
            else if (!Game::saveSuccess&&!Game::debugCalled)
                cout << "                " << Game::mainLang.ivldipt << endl;
            else
                Game::debugCalled = false;

            getCoord(playerlist[~Game::board]);
        }

        Game::board.move(Game::inputCoord);
        Game::board.print();

        if(Game::debugFlag)
            cout << Game::AchillesReturn << endl;

        if (Game::AIFlag == AI_MODE&&~Game::board == !Game::humanSide)
            cout << Game::mainLang.aithink;

        Game::AIPass = false;
    }

    judge();
    menu();
}

void autoPlayThread(short diffB, short diffW)
{
    if (Game::UIFlag)
    {
        thread UI(displayThread, 0, nullptr);
        thread game(autoPlay, diffB, diffW);
        UI.join();
        game.join();
    }
    else
        autoPlay(diffB, diffW);
}

void autoPlay(short diffB, short diffW)
{
    clock_t atstt = clock();

    short delayDur = 0;

    Game::inputFlag = true;

    short adiff[2]{diffW,diffB};
    adiff[Black] = diffB;
    adiff[White] = diffW;

    Game::board.print();
    SLP(0);

    Game::status = Playing;
    while (!Game::board.end())
    {
        SLP(delayDur);
        AchillesInit(adiff[~Game::board]);
        Game::randomFlag = false;

        if (Game::board(Valid))
            getCoord(AI);
        else
            Game::inputCoord = Game::passCoord;

        Game::board.move(Game::inputCoord);
        Game::board.print();
        Game::board.recordPrint();
    }

    if (Game::debugFlag)
    {
        cout << double(clock() - atstt) / CLOCKS_PER_SEC << endl;
        PAUSE;
    }


    judge();

    Game::inputFlag = false;
    Game::autoFlag = false;
    Game::randomFlag = false;

    menu();
}

void judge()
{
    CLS;
    Game::status = End;
    
    if(Game::UIFlag)
        glutLeaveMainLoop();

    Game::board.print();
    if (Game::AIFlag == AI_MODE && !Game::autoFlag)
    {
        if (Game::board(Game::humanSide) > Game::board(!Game::humanSide))
            cout << Game::mainLang.dftai << endl << endl;
        else if (Game::board(Game::humanSide) < Game::board(!Game::humanSide))
            cout << Game::mainLang.toosimple << endl << endl;
        else
            cout << Game::mainLang.tieai << endl << endl;
    }
    else
    {
        if (Game::board(Black) > Game::board(White))
            cout << "                " << Game::mainLang.blk << " " << Game::mainLang.win << endl << endl;
        else if (Game::board(Black) < Game::board(White))
            cout << "                " << Game::mainLang.wht << " " << Game::mainLang.win << endl << endl;
        else
            cout << "           "<< Game::mainLang.tie << endl << endl;
    }
    Game::board.recordPrint();

    cout << endl << Game::mainLang.gotomainspc << Game::mainLang.gotomain;

    PAUSE;
}