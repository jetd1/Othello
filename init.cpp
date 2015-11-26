#include "init.h"
#include <ctime>
#include <algorithm>

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
    cout << "3.Jacob Auto Play" << endl;
    if (UIFlag)
        cout << "4.Turn Off GUI" << endl;
    else
        cout << "4.Turn On GUI" << endl;
    cout << "5.Load Game" << endl;
    cout << "6.Instructions" << endl;
#ifdef WINDOWS_
    cout << "7.Change Theme" << endl;
#endif
    cout << "0.Exit" << endl;
    cout << endl;
    cout << "Input:_\b";

    cin >> in;
    cout << endl;

    if (in.length() == 1)
        switch (in[0])
        {
            case '1':
                AIFlag = NON_AI_MODE;
                gameBoard.clear();
                isAssistMode();
                init();
                gameThread(0, nullptr);
            case '2':
                AIFlag = AI_MODE;
                gameBoard.clear();
                isAssistMode();
                init();
                selectSide();
                selectDiff();
                gameThread(0, nullptr);
            case '3':
                autoFlag = true;
                AIFlag = NON_AI_MODE;
                gameBoard.clear();
                assistFlag = true;
                init();
                autoPlay();
            case '4':
                UIFlag ^= 1;
                menu();
            case '5':
                loadGame();
            case '6':
                help();
#ifdef WINDOWS_
            case '7':
                theme();
#endif
            case '0':
                exit(0);
        }
    else if (in == "ABAB")
        debugMenu();

    if (debugCalled)
        debugCalled = false;
    else
        cout << "Invalid Input!!!" << endl;
    PAUSE;
    menu();
}

void init() //must gameBoard.clear() or cellclear() before init;
{
    for (int i = 0; i < SAFE_LENGTH; i++)
        for (int j = 0; j < SAFE_LENGTH; j++)
        {
            gameBoard[i][j].stat = Empty;
            gameBoard[i][j].coord.x = i;
            gameBoard[i][j].coord.y = j;
            if (AIFlag == AI_MODE) gameBoard[i][j].coord.value = coordChara[i][j];
        }
    gameBoard[SIDE_LENGTH / 2][SIDE_LENGTH / 2].stat = gameBoard[SIDE_LENGTH / 2 + 1][SIDE_LENGTH / 2 + 1].stat = White;
    gameBoard[SIDE_LENGTH / 2][SIDE_LENGTH / 2 + 1].stat = gameBoard[SIDE_LENGTH / 2 + 1][SIDE_LENGTH / 2].stat = Black;
    sidePass = 0;
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

    if (!autoFlag)
    {
        CLS;

        if (PRINT_VERSION)
            printVersion();
    }

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
        if (!autoFlag)
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
            maxDepth = 0;
            break;
        case 2:
            maxDepth = 1;
            break;
        case 3:
            maxDepth = 3;
            break;
        case 4:
            maxDepth = 5;
            break;
        case 5:
            maxDepth = 8;
            break;
        default:
            fatalError(1);
    }
}

#ifdef WINDOWS_
void theme()
{
    CLS;
    
    cout << "Please Select Theme:" << endl << endl;
    cout << "0.Default (White on Black)" << endl;  //07
    cout << "1.Reverse (Black on White)" << endl;             //70
    cout << "2.Borland (Yellow on Blue) " << endl;            //9e
    cout << "3.BlueScreen (White on Blue)" << endl;          //9f
    cout << "4.Geek (Green on Black)" << endl;            //0a
    cout << "5.Glamorous (Blue on Purple)" << endl;      //5b
    cout << "6.Pinky (Yellow on Pink)" << endl;         //de
    cout << "7.Yima (White on Red)" << endl;            //cf
    cout << "8.DiDiaoYiMa (Red on Black)" << endl;     //7c
    cout << "9.Dragon (Yellow on Dark Red)" << endl << endl; //4e
    cout << "Input JET to Randomize the Theme." << endl;
    cout << endl << endl;
    cout << "Input:___\b\b\b";

    string input;
    cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    string colorlist = "0123456789ABCDEF";

    if (input == "JET")
    {
        short color[2];
        srand(unsigned(time(NULL)));
        color[0] = rand() % 16;
        srand(unsigned(clock()));
        color[1] = rand() % 16;
        char colorCombine[10] = "color ";
        srand(unsigned(clock()) + unsigned(time(NULL)));
        int r = rand() % 2;
        if (r)
        {
            colorCombine[6] = colorlist[color[0]];
            colorCombine[7] = colorlist[color[1]];
            colorCombine[8] = '\0';
        }
        else
        {
            colorCombine[6] = colorlist[color[1]];
            colorCombine[7] = colorlist[color[0]];
            colorCombine[8] = '\0';
        }
        system(colorCombine);
    }
    else if (input.length() == 1 && isdigit(input[0]))
        switch (input[0])
        {
            case '0':
                system("color 07");
                break;
            case '1':
                system("color 70");
                break;
            case '2':
                system("color 9E");
                break;
            case '3':
                system("color 9F");
                break;
            case '4':
                system("color 0A");
                break;
            case '5':
                system("color 5B");
                break;
            case '6':
                system("color DE");
                break;
            case '7':
                system("color CF");
                break;
            case '8':
                system("color 7C");
                break;
            case '9':
                system("color 4E");
                break;
        }
    else
    {
        cout << "Invalid Input!" << endl;
        PAUSE;
        theme();
    }

    cin.sync();
    menu();
}
#endif

void debugMenu()
{
    debugCalled = true;
    string in;
    cin >> in;
    transform(in.begin(), in.end(), in.begin(), ::toupper);
/*    if (in == "TSEN")
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
    else */
    if (in == "SETDEPTH")
    {
        cin >> maxDepth;
        manualFlag = true;
    }
    else if (in == "RANDOM")
        randomFlag = true;
    else if (in == "DEBUG")
        debugFlag = true;
    else if (in == "NDEBUG")
        debugFlag = false;
    else if (in == "FLIP")
    {
        playerSide ^= 1;
        gameThread(0, nullptr);
    }
    else if (in == "WIN")
    {
        for (int i = 1; i <= SIDE_LENGTH; i++)
            for (int j = 1; j <= SIDE_LENGTH; j++)
                gameBoard[i][j].stat = Status(playerSide);
        gameBoard.count();
        cPass = true;
        gameBoard.movesRecord.resize(63);
        gameThread(0, nullptr);
    }
    else
        cout << "^&$^%#*$" << endl;
    PAUSE;
}
