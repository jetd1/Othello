/*
Othello For Term Task
Version 0.7.5
*/
#include "base.h"
#include "declaration.h"

int main(int argc, char* argv[])
{
	//fin.open("othelloinput.txt");
	init();
	othelloMain();
	PAUSE;
}

void othelloMain()
{
	output();
	while(emptyCount&&passCount<2&&blackCount&&whiteCount)
	{
		if(passCount)
		{
			CLS;
			output();
		}
		if(!validCount)
		{
			cout<<"No Possible Move, Enter to Pass!"<<endl;
			PAUSE;
			passCount++;
			sideFlag^=1;
			setValid();
			continue;
		}
		getCoord(Human);
		while(!inputFlag||board[inputX][inputY]!=Valid)
		{
			if(inputFlag) cout<<"Invalid Position!"<<endl;
			else cout<<"Invalid Input!"<<endl;
			getCoord(Human);
		}
		move(inputX, inputY);
		sideFlag^=1;
		setValid();
		stoneCount();
		output();
		passCount=0;
	}
	judge();
}