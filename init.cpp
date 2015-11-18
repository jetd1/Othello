#include "elements.h"
#include "AIbase.h"

/*
* Initialize the game:
* 1.Choose mode(AI or non-AI);
* 2.Choose side(Blacck or White);
* 3.Choose with assistance or without;
* 4.Place four stones;
*/

void menu();
void init();
void selectSide();
void isAssistMode();

extern void printVersion();
extern void fatalError(unsigned ErrorCode);

extern bool assistFlag, modeFlag, sideFlag, playerSide;
extern short passCount, turnCount;
extern Board gameBoard;

void menu()
{
    if (PRINT_VERSION)
        printVersion();

    string in;

    menu:
    cout << "1.Play with Your Friends" << endl;
    cout << "2.Play with AI" << endl;
    cout << "3.Change Board Size" << endl;
    cout << "4.Read Game" << endl;
    cout << "5.Select Language" << endl;
    cout << "6.Exit" << endl;

    cin >> in;

    if (in.length() == 1)
        switch (in[0])
        {
            case '1':
                modeFlag = NON_AI_MODE;
                isAssistMode();
                init();
                return;
            case '2':
                modeFlag = AI_MODE;
                selectSide();
                isAssistMode();
                init();
                return;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '6':
                exit(0);
            default:
                fatalError(1);
        }
    else goto menu;
}

void init()
{
    for (int i = 0; i < SAFE_LENGTH; i++) 
        for (int j = 0; j < SAFE_LENGTH; j++)
        {
            gameBoard[i][j].stat = Empty;
            gameBoard[i][j].pos.x = i;
            gameBoard[i][j].pos.y = j;
            if (modeFlag == AI_MODE) gameBoard[i][j].pos.chara = coordChara[i][j];
        }
    gameBoard[SIDE_LENGTH/2][SIDE_LENGTH/2].stat = gameBoard[SIDE_LENGTH/2+1][SIDE_LENGTH/2+1].stat = White;
    gameBoard[SIDE_LENGTH/2][SIDE_LENGTH/2+1].stat = gameBoard[SIDE_LENGTH/2+1][SIDE_LENGTH/2].stat = Black;
    sideFlag = Black;
    passCount = turnCount = 0;
    gameBoard.count();
    gameBoard.setValidFor(sideFlag);
}

//void selectMode()
//{
//    string in;
//    string qst = "Play With Computer?(Y/N):_\b";
//    string rpt = "Invalid Input!(Sorry that I'm dumb)";
//    cout << qst;
//    cin >> in;
//    in[0] = toupper(in[0]);
//    while ((in!="Y")&&(in!="N"))
//    {
//        cout << rpt << endl;
//        cout << qst;
//        cin >> in;
//        in[0] = toupper(in[0]);
//    }
//    modeFlag = ((in=="Y") ? AI_MODE : NON_AI_MODE);
//}

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
        playerSide = ((in=="W") ? White : Black);
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
