/*
Othello For Term Task
Version 0.8.3
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
            if (!modeFlag || (modeFlag&&sideFlag == userSide)) cout << "No Possible Move, Enter to Pass!";
            else cout << "Computer Passed, Enter to Your Turn!";
            PAUSE;
            passCount++;
            sideFlag ^= 1;
            setValid(board);
            count(board);
            continue;
        }

        ////Get input
        if (!modeFlag || sideFlag == userSide)
        {
            getCoord(Player);
            while (!inputFlag || board[inputX][inputY] != Valid)
            {
                if (inputFlag) cout << "Invalid Position!" << endl;
                else cout << "Invalid Input!" << endl;
                getCoord(Player);
            }
        }
        else getCoord(Computer);

        ////Refresh board
        move(inputX, inputY, board);
        sideFlag ^= 1;
        setValid(board);
        count(board);
        output();
        passCount = 0;
    }
    judge();
}