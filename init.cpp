#include "base.h"
#include "extern.h"

void init()
{
	CLS;
	selectMode();
	selectSide();
	isAssistMode();
	for(int i=0; i<10; i++) for(int j=0; j<10; j++) board[i][j]=Empty;
	board[4][4]=board[5][5]=White;
	board[4][5]=board[5][4]=Black;
	sideFlag=Black;
	passCount=0;
	count(board);
	setValid(board);
}

void selectMode()
{
	string in;
	string qst="Play With Computer?(Y/N):_\b";
	string rpt="Invalid Input!(Sorry that I'm dumb)";
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
	if(in=="Y") modeFlag=true;
	else modeFlag=false;
}

void selectSide()
{
	if(modeFlag)
	{
		string in;
		string qst="Play Black or White?(B/W):_\b";
		string rpt="Invalid Input!(Sorry that I'm dumb)";
		cout<<qst;
		cin>>in;
		in[0]=toupper(in[0]);
		while(in!="B"&&in!="W")
		{
			cout<<rpt<<endl;
			cout<<qst;
			cin>>in;
			in[0]=toupper(in[0]);
		}
		if(in=="W") userSide=White;
		else userSide=Black;
	}
	else sideFlag=Black;
}

void isAssistMode()
{
	string in;
	string qst="Do You Want Any Assistance When Placing the Stone?(Y/N):_\b";
	string rpt="Invalid Input!(Sorry that I'm dumb)";
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
