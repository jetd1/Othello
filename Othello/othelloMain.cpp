/*
Othello For Term Task
Version 0.8.1
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
		if(!stoneCount[Valid])
		{
			cout<<"No Possible Move, Enter to Pass!"<<endl;
			PAUSE;
			passCount++;
			sideFlag^=1;
			setValid();
			continue;
		}
		if(!modeFlag||sideFlag==userSide)
		{
			getCoord(Human);
			while(!inputFlag||board[inputX][inputY]!=Valid)
			{
				if(inputFlag) cout<<"Invalid Position!"<<endl;
				else cout<<"Invalid Input!"<<endl;
				getCoord(Human);
			}
		}
		else
		{
			setValid();
			if(stoneCount[Valid]) getCoord(Computer);
			else
			{
				cout<<"Computer Passed, Your turn."<<endl;
				passCount++;
				sideFlag^=1;
				setValid();
				continue;
			}
			
		}
		move(inputX, inputY);
		sideFlag^=1;
		setValid();
		count();
		output();
		passCount=0;
	}
	judge();
}