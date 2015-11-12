#include "base.h"
#include "extern.h"
#include <iomanip>

string input()
{
	inputFlag=false;

	if(sideFlag) cout<<"Black Turn:__\b\b";
	else cout<<"White Turn:__\b\b";
	string input;
	cin>>input;
	if(input.length()==2)
	{
		input[0]=toupper(input[0]);
		input[1]=toupper(input[1]);
		if(input[0]>='A'&&input[0]<='H'&&input[1]>='1'&&input[1]<='8')
		{
			input[1]-='0';
			input[0]-='@';
			input.assign(input.rbegin(), input.rend());
			inputFlag=true;
		}
		else if(input[1]>='A'&&input[1]<='H'&&input[0]>='1'&&input[0]<='8')
		{
			input[0]-='0';
			input[1]-='@';
			inputFlag=true;
		}
	}
	fflush(stdin);
	return input;
}

void output()
{
	SLP(200);
	CLS;
	cout<<" ";
	for(int i=1; i<=8; i++) cout<<' '<<char('@'+i);
	cout<<endl;
	char outTmp;
	for(int i=1; i<=8; i++)
	{
		cout<<i;
		for(int j=1; j<=8; j++)
		{
			switch(board[i][j])
			{
				case Black:
					outTmp='X';
					break;
				case White:
					outTmp='O';
					break;
				case Empty:
					outTmp=' ';
					break;
				case Valid:
					if(assistFlag) outTmp='*';
					else outTmp=' ';
					break;
				default:
					extern void fatalError();
			}
			cout<<' '<<outTmp;
		}
		if(i-8) cout<<endl;
	}
	cout<<endl<<left<<"Black(X):"<<setw(2)<<blackCount<<"  White(O):"<<setw(2)<<whiteCount<<endl<<endl;
}

void getCoord(getType T)
{
	switch(T)
	{
		case Human:
			coord=input();
			inputX=coord[0];
			inputY=coord[1];
			break;
		case Computer:
			coord=AI();
			inputX=coord[0];
			inputY=coord[1];
			break;
		default:
			fatalError();
	}
}