#include "base.h"

extern bool inRange(int p, int q);
extern int dir[8][2];
extern bool sideFlag;
extern int emptyCount, blackCount, whiteCount, validCount;
extern enum status { White, Black, Empty, Valid } board[10][10];

bool isValid(int x, int y, bool side)
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

void setValid()
{
	validCount=0;
	for(int i=1; i<=8; i++) for(int j=1; j<=8; j++)
	{
		if(board[i][j]<=Black) continue;
		if(isValid(i, j, sideFlag))
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

bool inRange(int p, int q)
{
	return p>=1&&p<=8&&q>=1&&q<=8;
}

void judge()
{
	if(blackCount>whiteCount||!whiteCount) cout<<"Black Win!"<<endl<<endl;
	else if(blackCount<whiteCount||!blackCount) cout<<"White Win!"<<endl<<endl;
	else cout<<"Tie!"<<endl<<endl;
}