#include "elements.h"
#include "AIbase.h"

void menu();
void init();
void selectSide();
void selectDiff();
void isAssistMode();
void initAI(short diff);

extern void loadGame();
extern void printVersion();
extern void fatalError(unsigned ErrorCode);
extern void multiThread(int argc, char **argv);

extern bool assistFlag, AIFlag, playerSide;
extern short passCount;
extern Board gameBoard;
extern short maxDepth;
extern aiType AIType;

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
                selectSide();
                selectDiff();
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
    passCount = 0;
    gameBoard.count();
    gameBoard.setValid();
    playerSide = Black;
}

void selectSide()
{
    string in;
    string qst = "Play Black or White?(B/W):_\b";
    string rpt = "Invalid Input!(Sorry that I'm dumb)";
    cout << qst;
    cin >> in;
    in[0] = toupper(in[0]);
    while ((in != "B") && (in != "W"))
    {
        cout << rpt << endl;
        cout << qst;
        cin >> in;
        in[0] = toupper(in[0]);
    }
    playerSide = ((in == "W") ? White : Black);
}

void selectDiff()
{
    short diff;
    CLS;

    if (PRINT_VERSION)
        printVersion();

    string in;

    cout << "1.Dumb Mode" << endl;
    cout << "2.Easy Mode" << endl;
    cout << "3.Normal Mode" << endl;
    cout << "4.Hard Mode" << endl;
    cout << "5.Call Police Mode" << endl;
    cout << endl;
    cout << "Input:_\b";

    cin >> in;
    cout << endl;

    if (in.length() == 1 && in[0] >= '1'&&in[0] <= '5')
    {
        switch (in[0])
        {
            case '1':
                diff = 1;
                break;
            case '2':
                diff = 2;
                break;
            case '3':
                diff = 3;
                break;
            case '4':
                diff = 4;
                break;
            case '5':
                diff = 5;
                break;
        }
        initAI(diff);
    }
    else
    {
        cout << "Invalid Input!!!" << endl;
        PAUSE;
        selectDiff();
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

void initAI(short diff)
{
    switch (diff)
    {
        case 1:
            AIType = Random;
            break;
        case 2:
            AIType = Jet;
            break;
        case 3:
            AIType = AB;
            maxDepth = 3;
            break;
        case 4:
            AIType = AB;
            maxDepth = 5;
            break;
        case 5:
            AIType = AB;
            maxDepth = 8;
            break;
        default:
            fatalError(1);
    }
}