#include "elements.h" 

extern Board gameBoard;

extern bool AIFlag, playerSide;

void judge()
{
    if (AIFlag==AI_MODE)
    {
        if (gameBoard.statusCount[playerSide]>gameBoard.statusCount[!playerSide])
            cout<<"You Defeated Jacob! Congratulations!"<<endl<<endl;
        else if (gameBoard.statusCount[playerSide]<gameBoard.statusCount[!playerSide])
            cout<<"Too Young too Simple!"<<endl<<endl;
        else
            cout<<"Tie! Jacob Want to Play Again With You."<<endl<<endl;
    }
    else
    {
        if (gameBoard.statusCount[Black]>gameBoard.statusCount[White]||!gameBoard.statusCount[White])
            cout<<"Black Win!"<<endl<<endl;
        else if (gameBoard.statusCount[Black]<gameBoard.statusCount[White]||!gameBoard.statusCount[Black])
            cout<<"White Win!"<<endl<<endl;
        else
            cout<<"Tie!"<<endl<<endl;
    }

    cout<<endl<<"Press Any Key to Main Menu..."<<endl;

    PAUSE;
}
