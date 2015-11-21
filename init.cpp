#include <algorithm>
#include "elements.h"
#include "AIbase.h"

short diff;

void menu();
void init();
void selectSide();
void selectDiff();
void isAssistMode();
void JacobInit(short diff);
void debugMenu();

extern void help();
extern void loadGame();
extern void printVersion();
extern void fatalError(unsigned ErrorCode);
extern void multiThread(int argc, char **argv);

extern bool assistFlag, AIFlag, UIFlag, playerSide, manualFlag;
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

    if (UIFlag)
        cout << "GUI Mode On" << endl << endl;
    else
        cout << endl;

    cout << "1.Play with Friends" << endl;
    cout << "2.Play with Jacob" << endl;
    cout << "3.Load Game" << endl;
    if (UIFlag)
        cout << "4.Turn Off GUI" << endl;
    else
        cout << "4.Turn On GUI" << endl;
    cout << "5.Instructions" << endl;
    cout << "6.Exit" << endl;
    cout << endl;
    cout << "Input:_\b";

    cin >> in;
    cout << endl;

    if (in.length() == 1)
        switch (in[0])
        {
            case '1':
                AIFlag = NON_AI_MODE;
                isAssistMode();
                init();
                multiThread(0, nullptr);
            case '2':
                AIFlag = AI_MODE;
                isAssistMode();
                init();
                selectSide();
                selectDiff();
                multiThread(0, nullptr);
            case '3':
                loadGame();
            case '4':
                UIFlag ^= 1;
                menu();
            case '5':
                help();
            case '6':
                exit(0);
        }
    else if (in == "ABAB")
        debugMenu();

    cout << "Invalid Input!!!" << endl;
    PAUSE;
    menu();
}

void init()
{
    gameBoard.clear();
    for (int i = 0; i < SAFE_LENGTH; i++)
        for (int j = 0; j < SAFE_LENGTH; j++)
        {
            gameBoard[i][j].stat = Empty;
            gameBoard[i][j].pos.x = i;
            gameBoard[i][j].pos.y = j;
            if (AIFlag == AI_MODE) gameBoard[i][j].pos.chara = coordChara[i][j];
        }
    gameBoard[SIDE_LENGTH / 2][SIDE_LENGTH / 2].stat = gameBoard[SIDE_LENGTH / 2 + 1][SIDE_LENGTH / 2 + 1].stat = White;
    gameBoard[SIDE_LENGTH / 2][SIDE_LENGTH / 2 + 1].stat = gameBoard[SIDE_LENGTH / 2 + 1][SIDE_LENGTH / 2].stat = Black;
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
    if (manualFlag)
        return;

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
        JacobInit(diff);
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
    while ((in != "Y") && (in != "N"))
    {
        cout << rpt << endl;
        cout << qst;
        cin >> in;
        in[0] = toupper(in[0]);
    }
    assistFlag = ((in == "Y") ? true : false);
}

void JacobInit(short diff)
{
    switch (diff)
    {
        case 1:
            AIType = Random;
            break;
        case 2:
            AIType = Jacob;
            maxDepth = 1;
            break;
        case 3:
            AIType = Jacob;
            maxDepth = 3;
            break;
        case 4:
            AIType = Jacob;
            maxDepth = 5;
            break;
        case 5:
            AIType = Jacob;
            maxDepth = 10;
            break;
        default:
            fatalError(1);
    }
}

void debugMenu()
{
    string in;
    cin >> in;
    transform(in.begin(), in.end(), in.begin(), ::toupper);
    if (in == "TSEN")
    {
        double ALPHA = -2000;
        double LOWERA = 5;
        double LOWERB = 90;
        double BETA = 2000;
        cout << "UPUPDOWNDOWN" << endl;
    }
    else if (in == "ZEBRA")
    {
        double ALPHA = -2000;
        double LOWERA = -80;
        double LOWERB = 30;
        double BETA = 2000;
        cout << "UPUPDOWNDOWN" << endl;
    }
    else if (in == "DEFAULT" || in == "HUMAN")
    {
        double ALPHA = -2000;
        double LOWERA = -10;
        double LOWERB = 100;
        double BETA = 2000;
        cout << "UPUPDOWNDOWN" << endl;
    }
    else if (in == "SETDEPTH")
    {
        AIType = Jacob;
        cin >> maxDepth;
        manualFlag = true;
    }
    else
        cout << "^&$^%#*$" << endl;
    PAUSE;
    menu();
}