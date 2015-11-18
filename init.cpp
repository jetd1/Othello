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

extern void loadGame();
extern void printVersion();
extern void fatalError(unsigned ErrorCode);
extern void multiThread(int argc, char **argv);

extern bool assistFlag, AIFlag, playerSide;
extern short passCount, turnCount;
extern Board gameBoard;

void menu()
{
    CLS;

    if (PRINT_VERSION)
        printVersion();

    string in;

    cout << "1.Play with Friends" << endl;
    cout << "2.Play with AI" << endl;
    cout << "3.Load Game" << endl;
    cout << "4.Exit" << endl;
    cout << endl;
    cout << "Input:_\b";

    cin >> in;
    cout << endl;

    if (in.length() == 1)
        switch (in[0])
        {
            case '1':
                AIFlag = NON_AI_MODE;
                init();
                multiThread(0,nullptr);
            case '2':
                AIFlag = AI_MODE;
                init();
                multiThread(0,nullptr);
            case '3':
                loadGame();
                break;
            case '4':
                exit(0);
        }

    cout << "Invalid Input!!!" << endl;
    PAUSE;
    menu();
}

void init()
{
    gameBoard.clear();

    selectSide();
    isAssistMode();
    for (int i = 0; i < SAFE_LENGTH; i++) 
        for (int j = 0; j < SAFE_LENGTH; j++)
        {
            gameBoard[i][j].stat = Empty;
            gameBoard[i][j].pos.x = i;
            gameBoard[i][j].pos.y = j;
            if (AIFlag == AI_MODE) gameBoard[i][j].pos.chara = coordChara[i][j];
        }
    gameBoard[SIDE_LENGTH/2][SIDE_LENGTH/2].stat = gameBoard[SIDE_LENGTH/2+1][SIDE_LENGTH/2+1].stat = White;
    gameBoard[SIDE_LENGTH/2][SIDE_LENGTH/2+1].stat = gameBoard[SIDE_LENGTH/2+1][SIDE_LENGTH/2].stat = Black;
    passCount = turnCount = 0;
    gameBoard.count();
    gameBoard.setValid();
}

void selectSide()
{
    if (AIFlag==AI_MODE)
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
}

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
