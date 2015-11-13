/*
Othello For Term Task
Version 0.8.2
*/
#include "base.h"
#include "declaration.h"

int main()
{
	//fin.open("othelloinput.txt");
	init();
	othelloMain();
	PAUSE;
}

void othelloMain()
{
	output();
	while(stoneCount[Empty]&&passCount<2&&stoneCount[Black]&&stoneCount[White])
	{
		////No-valid situation handle
		if(!stoneCount[Valid])
		{
			if(!modeFlag||(modeFlag&&sideFlag==userSide)) cout<<"No Possible Move, Enter to Pass!";
			else cout<<"Computer Passed, Enter to Your Turn!";
			PAUSE;
			passCount++;
			sideFlag^=1;
			setValid();
			count();
			continue;
		}

		////Get input
		if(!modeFlag||sideFlag==userSide)
		{
			getCoord(Player);
			while(!inputFlag||board[inputX][inputY]!=Valid)
			{
				if(inputFlag) cout<<"Invalid Position!"<<endl;
				else cout<<"Invalid Input!"<<endl;
				getCoord(Player);
			}
		}
		else getCoord(Computer);

		////Refresh board
		move(inputX, inputY);
		sideFlag^=1;
		setValid();
		count();
		output();
		passCount=0;
	}
	judge();
}