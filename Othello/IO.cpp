#include "base.h"
#include <iomanip>
using namespace std;

extern int inputX, inputY;
extern bool assistFlag, sideFlag, inputFlag;
extern int blackCount, whiteCount;
extern enum status { White, Black, Empty, Valid };
extern status board[10][10];

void input()
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
			inputX=input[1]-'0';
			inputY=input[0]-'@';
			inputFlag=true;
		}
		else if(input[1]>='A'&&input[1]<='H'&&input[0]>='1'&&input[0]<='8')
		{
			inputX=input[0]-'0';
			inputY=input[1]-'@';
			inputFlag=true;
		}
	}
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