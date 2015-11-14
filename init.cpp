#include "base.h"
#include "extern.h"

#define AI_MODE true
#define NON_AI_MODE false

/*
* Initialize the game:
* 1.Choose mode(AI or non-AI);
* 2.Choose side(Blacck or White);
* 3.Choose with assistance or without;
* 4.Place four stones;
*/
void init()
{
    CLS;
    selectMode();
    selectSide();
    isAssistMode();
    for (int i = 0; i < 10; i++) for (int j = 0; j < 10; j++) board[i][j] = Empty;
    board[4][4] = board[5][5] = White;
    board[4][5] = board[5][4] = Black;
    sideFlag = Black;
    passCount = 0;
    count(board);
    setValid(board);
}

/*
* Select to play with AI or with stupid human.
*/
void selectMode()
{
    string in;
    string qst = "Play With Computer?(Y/N):_\b";
    string rpt = "Invalid Input!(Sorry that I'm dumb)";
    cout << qst;
    cin >> in;
    in[0] = toupper(in[0]);
    while ((in!="Y")&&(in!="N"))
    {
        cout << rpt << endl;
        cout << qst;
        cin >> in;
        in[0] = toupper(in[0]);
    }
    modeFlag = ((in=="Y") ? AI_MODE : NON_AI_MODE);
}

/*
* Select Black or White for the player.
*/
void selectSide()
{
    if (modeFlag==AI_MODE)
    {
        string in;
        string qst = "Play Black or White?(B/W):_\b";
        string rpt = "Invalid Input!(Sorry that I'm dumb)";
        cout << qst;
        cin >> in;
        in[0] = toupper(in[0]);
        while((in!="B")&&(in!="W"))
        {
            cout << rpt << endl;
            cout << qst;
            cin >> in;
            in[0] = toupper(in[0]);
        }
        userSide = ((in=="W") ? White : Black);
    }
    else sideFlag = Black;
}

/*
* Ask if the player wants assistance.
*/
void isAssistMode()
{
    string in;
    string qst = "Do You Want Any Assistance When Placing the Stone?(Y/N):_\b";
    string rpt = "Invalid Input!(Sorry that I'm dumb)";
    cout << qst;
    cin >> in;
    in[0] = toupper(in[0]);
    while((in!="Y")&&(in!="N"))
    {
        cout << rpt << endl;
        cout << qst;
        cin >> in;
        in[0] = toupper(in[0]);
    }
    assistFlag = ((in=="Y") ? true : false);
}
