#include "elements.h"

extern Board gameBoard;

extern bool assistFlag, modeFlag, sideFlag, playerSide;


bool inRange(int p, int q)
{
    return p >= 1 && p <= SIDE_LENGTH && q >= 1 && q <= SIDE_LENGTH;
}

void judge()
{
    if (modeFlag == AI_MODE)
    {
        if (gameBoard.statusCount[playerSide] > gameBoard.statusCount[!playerSide]) 
            cout << "You Defeated Computer! Congratulations!" << endl << endl;
        else if (gameBoard.statusCount[playerSide] < gameBoard.statusCount[!playerSide]) 
            cout << "Too Young too Simple!" << endl << endl;
        else 
            cout << "Tie! But Liangchen Want to Play Again With You." << endl << endl;
    }
    else
    {
        if (gameBoard.statusCount[Black] > gameBoard.statusCount[White] || !gameBoard.statusCount[White]) 
            cout << "Black Win!" << endl << endl;
        else if (gameBoard.statusCount[Black] < gameBoard.statusCount[White] || !gameBoard.statusCount[Black]) 
            cout << "White Win!" << endl << endl;
        else 
            cout << "Tie!" << endl << endl;
    }
}