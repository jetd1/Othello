/*
Jet Othello
Version 0.6
*/
#include "pltfmbase.h"
#include "GL/freeglut.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
//#include <fstream> 

using namespace std;

int inputX, inputY, passCount, emptyCount, blackCount, whiteCount, validCount;
bool assistFlag, sideFlag, inputFlag;
enum status { White, Black, Empty, Valid };
status board[10][10];
//ifstream fin;

void fatalError(), isAssistMode(), init(), input(), othello(), move(int x, int y), output(), setValid(bool Flag), stoneCount(), judge(), AI();
bool isValid(int x, int y, bool side);

int main(int argc, char* argv[])
{
	//fin.open("othelloinput.txt");
	init();
	othello();
	PAUSE;
}

void fatalError()
{
	SLP(300);
	CLS;
	cerr<<"Fatal Error Detected, Program Will Now Terminate."<<endl;
	PAUSE;
	exit(-1);
}

void init()
{
	isAssistMode();
	for(int i=0; i<10; i++) for(int j=0; j<=10; j++) board[i][j]=Empty;
	board[4][4]=board[5][5]=White;
	board[4][5]=board[5][4]=Black;
	sideFlag=Black;
	inputFlag=false;
	passCount=0;
	emptyCount=60;
	validCount=4;
	blackCount=whiteCount=2;
	setValid(sideFlag);
}

void isAssistMode()
{
	string in;
	char qst[]="Do You Want Any Assistance When Placing the Stone?(Y/N):_\b";
	char rpt[]="Invalid Input!(Sorry that I'm dumb)";
	cout<<qst;
	cin>>in;
	in[0]=toupper(in[0]);
	while(in!="Y"&&in!="N")
	{
		cout<<rpt<<endl;
		cout<<qst;
		cin>>in;
		in[0]=toupper(in[0]);
	}
	if(in=="Y") assistFlag=true;
	else assistFlag=false;
}

void othello()
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
			setValid(sideFlag);
			continue;
		}
		input();
		while(!inputFlag||board[inputX][inputY]!=Valid)
		{
			if(inputFlag) cout<<"Invalid Position!"<<endl;
			else cout<<"Invalid Input!"<<endl;
			input();
		}
		move(inputX, inputY);
		sideFlag^=1;
		setValid(sideFlag);
		stoneCount();
		output();
		passCount=0;
	}
	judge();
}

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

bool isValid(int x, int y, bool side)
{
	if(board[x][y]<Empty) return false;
	int i, j;
	if(board[x-1][y-1]==!side)
	{
		for(i=x-1, j=y-1; i>=1&&j>=1; i--, j--)
		{
			if(board[i][j]>=Empty) break;
			if(int(side)==board[i][j]) return true;
		}
	}
	if(board[x-1][y]==!side)
	{
		for(i=x-1; i>=1; i--)
		{
			if(board[i][y]>=Empty) break;
			if(int(side)==board[i][y]) return true;
		}
	}
	if(board[x-1][y+1]==!side)
	{
		for(i=x-1, j=y+1; i>=1&&j<=8; i--, j++)
		{
			if(board[i][j]>=Empty) break;
			if(int(side)==board[i][j]) return true;
		}
	}
	if(board[x][y+1]==!side)
	{
		for(j=y+1; j<=8; j++)
		{
			if(board[x][j]>=Empty) break;
			if(int(side)==board[x][j]) return true;
		}
	}
	if(board[x+1][y+1]==!side)
	{
		for(i=x+1, j=y+1; i<=8&&j<=8; i++, j++)
		{
			if(board[i][j]>=Empty) break;
			if(int(side)==board[i][j]) return true;
		}
	}
	if(board[x+1][y]==!side)
	{
		for(i=x+1; i<=8; i++)
		{
			if(board[i][y]>=Empty) break;
			if(int(side)==board[i][y]) return true;
		}
	}
	if(board[x+1][y-1]==!side)
	{
		for(i=x+1, j=y-1; i<=8&&j>=1; i++, j--)
		{
			if(board[i][j]>=Empty) break;
			if(int(side)==board[i][j]) return true;
		}
	}
	if(board[x][y-1]==!side)
	{
		for(j=y-1; j>=1; j--)
		{
			if(board[x][j]>=Empty) break;
			if(int(side)==board[x][j]) return true;
		}
	}
	return false;
}

void setValid(bool Flag)
{
	validCount=0;
	for(int i=1; i<=8; i++) for(int j=1; j<=8; j++)
	{
		if(board[i][j]<=Black) continue;
		if(isValid(i, j, Flag))
		{
			board[i][j]=Valid;
			validCount++;
		}
		else board[i][j]=Empty;
	}
}

void stoneCount()
{
	blackCount=whiteCount=emptyCount=0;
	for(int i=1; i<=8; i++) for(int j=1; j<=8; j++)
	{
		blackCount+=(board[i][j]==Black);
		whiteCount+=(board[i][j]==White);
		emptyCount+=(board[i][j]>=Empty);
	}
}

void move(int x, int y)
{
	int i, j;
	int tmp=!sideFlag;
	if(board[x-1][y-1]==tmp)
	{
		for(i=x-1, j=y-1; i>=1&&j>=1; i--, j--)
		{
			if(board[i][j]>=Empty) break;
			if(int(sideFlag)==board[i][j])
			{
				while(i!=x)
				{
					board[++i][++j]=status(sideFlag);
				}
				break;
			}
		}
	}
	if(board[x-1][y]==tmp)
	{
		for(i=x-1; i>=1; i--)
		{
			if(board[i][y]>=Empty) break;
			if(int(sideFlag)==board[i][y])
			{
				while(i!=x)
				{
					board[++i][y]=status(sideFlag);
				}
				break;
			}
		}
	}
	if(board[x-1][y+1]==tmp)
	{
		for(i=x-1, j=y+1; i>=1&&j<=8; i--, j++)
		{
			if(board[i][j]>=Empty) break;
			if(int(sideFlag)==board[i][j])
			{
				while(i!=x)
				{
					board[++i][--j]=status(sideFlag);
				}
				break;
			}
		}
	}
	if(board[x][y+1]==tmp)
	{
		for(j=y+1; j<=8; j++)
		{
			if(board[x][j]>=Empty) break;
			if(int(sideFlag)==board[x][j])
			{
				while(j!=y)
				{
					board[x][--j]=status(sideFlag);
				}
				break;
			}
		}
	}
	if(board[x+1][y+1]==tmp)
	{
		for(i=x+1, j=y+1; i<=8&&j<=8; i++, j++)
		{
			if(board[i][j]>=Empty) break;
			if(int(sideFlag)==board[i][j])
			{
				while(i!=x)
				{
					board[--i][--j]=status(sideFlag);
				}
				break;
			}
		}
	}
	if(board[x+1][y]==tmp)
	{
		for(i=x+1; i<=8; i++)
		{
			if(board[i][y]>=Empty) break;
			if(int(sideFlag)==board[i][y])
			{
				while(i!=x)
				{
					board[--i][y]=status(sideFlag);
				}
				break;
			}
		}
	}
	if(board[x+1][y-1]==tmp)
	{
		for(i=x+1, j=y-1; i<=8&&j>=1; i++, j--)
		{
			if(board[i][j]>=Empty) break;
			if(int(sideFlag)==board[i][j])
			{
				while(i!=x)
				{
					board[--i][++j]=status(sideFlag);
				}
				break;
			}
		}
	}
	if(board[x][y-1]==tmp)
	{
		for(j=y-1; j>=1; j--)
		{
			if(board[x][j]>=Empty) break;
			if(int(sideFlag)==board[x][j])
			{
				while(j!=y)
				{
					board[x][++j]=status(sideFlag);
				}
				break;
			}
		}
	}
	board[x][y]=status(sideFlag);
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
					fatalError();
			}
			cout<<' '<<outTmp;
		}
		if(i-8) cout<<endl;
	}
	cout<<endl<<left<<"Black(X):"<<setw(2)<<blackCount<<"  White(O):"<<setw(2)<<whiteCount<<endl<<endl;
}

void judge()
{
	if(blackCount>whiteCount||!whiteCount) cout<<"Black Win!"<<endl<<endl;
	else if(blackCount<whiteCount||!blackCount) cout<<"White Win!"<<endl<<endl;
	else cout<<"Tie!"<<endl<<endl;
}

void AI()
{

}


//main for debug
//int main()
//{
//	isAssistMode();
//	init();
//	for(int i=0; i<10; i++)
//	{
//		for(int j=0; j<10; j++) cout<<isValid(i, j, !sideFlag)<<' ';
//		cout<<endl;
//	}
//	getchar();
//	getchar();
//}