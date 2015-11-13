#include "base.h"
#include "extern.h"

bool isValid(int x, int y, bool side, status board[10][10])
{
	if(board[x][y]<Empty) return false;
	for(int i=0; i<8; i++)
	{
		int dx=dir[i][0], dy=dir[i][1];
		if(board[x+dx][y+dy]==!side)
		{
			for(int p=x+dx, q=y+dy; inRange(p, q); p+=dx, q+=dy)
			{
				if(board[p][q]>=Empty) break;
				if(board[p][q]==int(side)) return true;
			}
		}
	}
	return false;
}

void setValid(status board[10][10])
{
	validCoord.clear();
	stoneCount[Valid]=0;
	for(int i=1; i<=8; i++) for(int j=1; j<=8; j++)
	{
		string tmpCoord;
		if(board[i][j]<=Black) continue;
		if(isValid(i, j, sideFlag, board))
		{
			board[i][j]=Valid;
			stoneCount[Valid]++;
			tmpCoord.push_back(char(i+'0'));
			tmpCoord.push_back(char(j+'0'));
			validCoord.push_back(tmpCoord);
		}
		else board[i][j]=Empty;
	}
}

void count(status board[10][10])
{
	stoneCount[Black]=stoneCount[White]=stoneCount[Empty]=0;
	for(int i=1; i<=8; i++) for(int j=1; j<=8; j++)
	{
		stoneCount[Black]+=(board[i][j]==Black);
		stoneCount[White]+=(board[i][j]==White);
		stoneCount[Empty]+=(board[i][j]>=Empty);
	}
}

void move(int x, int y, status board[10][10])
{
	for(int i=0; i<8; i++)
	{
		int dx=dir[i][0], dy=dir[i][1];
		if(board[x+dx][y+dy]==!sideFlag)
		{
			for(int p=x+dx, q=y+dy; inRange(p, q); p+=dx, q+=dy)
			{
				if(board[p][q]>=Empty) break;
				if(board[p][q]==status(sideFlag))
				{
					board[x][y]=status(sideFlag);
					for(int r=p-dx, s=q-dy; board[r][s]!=status(sideFlag); r-=dx, s-=dy) board[r][s]=status(sideFlag);
					break;
				}
			}
		}
	}
}

inline bool inRange(int p, int q)
{
	return p>=1&&p<=8&&q>=1&&q<=8;
}

void judge()
{
	if(modeFlag)
	{
		if(stoneCount[userSide]>stoneCount[!userSide]) cout<<"You Defeated Computer! Congratulations!"<<endl<<endl;
		else if(stoneCount[userSide]<stoneCount[!userSide]) cout<<"Too Young too Simple!"<<endl<<endl;
		else cout<<"Tie! But Liangchen Want to Play Again With You."<<endl<<endl;
	}
	else
	{
		if(stoneCount[Black]>stoneCount[White]||!stoneCount[White]) cout<<"Black Win!"<<endl<<endl;
		else if(stoneCount[Black]<stoneCount[White]||!stoneCount[Black]) cout<<"White Win!"<<endl<<endl;
		else cout<<"Tie!"<<endl<<endl;
	}
}