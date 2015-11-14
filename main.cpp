/*
Othello For Term Task
Version 0.9.0
*/
#include "base.h"
#include "declaration.h"

int main()
{
    init();
    othelloMain();
    PAUSE;
}

void othelloMain()
{
    output();
    while (stoneCount[Empty] && passCount < 2 && stoneCount[Black] && stoneCount[White])
    {
        ////No-valid situation handle
        if (!stoneCount[Valid])
        {
            if (!modeFlag || (modeFlag&&sideFlag == playerSide)) cout << "No Possible Move, Enter to Pass!";
            else cout << "Computer Passed, Enter to Your Turn!";
            PAUSE;
            passCount++;
            sideFlag ^= 1;
            setValid(board, sideFlag);
            count(board);
            continue;
        }

        ////Get input
        if (!modeFlag || sideFlag == playerSide)
        {
            getCoord(Player);
            while (!inputFlag || board[inputCoord.x][inputCoord.y].stat != Valid)
            {
                if (inputFlag) cout << "Invalid Position!" << endl;
                else cout << "Invalid Input!" << endl;
                getCoord(Player);
            }
        }
        else getCoord(Computer);

        ////Refresh board
        move(inputCoord, board);
        sideFlag ^= 1;
        setValid(board, sideFlag);
        count(board);
        output();
        passCount = 0;
    }
    judge();
}