#include "init.h"
#include <ctime>
#include <algorithm>

void menu()
{
    CLS;

    if (firstRun)
    {
        selectLang();
        isAssistMode();
    }

    firstRun = false;

#ifdef _WIN32
    system(Game::mainLang.title);
#endif

    Game::mainLang.printVersion();
    Game::mainLang.printMenu();

    string in;

    cin >> in;
    cout << endl;

    if (in.length() == 1)
        switch (in[0])
        {
            case '1':
                Game::AIFlag = NON_AI_MODE;
                Game::board.init();
                Game::humanSide = Black;
                gameThread(Human, Human);
            case '2':
                Game::AIFlag = AI_MODE;
                Game::board.init();
                Game::humanSide = Black;
                selectSide();
                Game::diff = selectdiff();
                AchillesInit(Game::diff);
                if (Game::humanSide == Black)
                    gameThread(Human, AI);
                else
                    gameThread(AI, Human);
            case '3':
                Game::AIFlag = AI_MODE;
                Game::autoFlag = true;
                Game::assistFlag = true;
                Game::board.init();

                short diffB, diffW;
                CLS;
                cout << Game::mainLang.atplbs << endl << endl;
                diffB = selectdiff();
                CLS;
                cout << Game::mainLang.atplws << endl << endl;
                diffW = selectdiff();

                autoPlayThread(diffB, diffW);
            case '4':
                Game::UIFlag ^= 1;
                menu();
            case '5':
                Game::board.load();
                if (Game::AIFlag)
                {
                    if (Game::humanSide == Black)
                        gameThread(Human, AI);
                    else
                        gameThread(AI, Human);
                }
                else
                    gameThread(Human, Human);
            case '6':
                settings();
                break;
            case '7':
                Game::mainLang.help();
                menu();
            case '0':
                exit(0);
        }
    else if (in == "ABAB")
        debugMenu();

    if (Game::debugCalled)
        Game::debugCalled = false;
    else
        cout << Game::mainLang.ivldipt << endl;
    PAUSE;
    menu();
}

void selectLang()
{
    CLS;
    string in;
    cout << "Please Select Language:" << endll;
    cout << "1.English" << endl;
    cout << "2.简体中文" << endl;
    cout << "3.繁体中文" << endll;
    cout << "Please Select:_\b";
    cin >> in;

    if (in.length() == 1 && isdigit(in[0]))
        switch (in[0])
        {
            case '1':
                Game::langFlag = en_us;
                break;
            case '2':
                Game::langFlag = zh_cn;
                break;
            case '3':
                Game::langFlag = zh_tw;
                break;
            case '4':
                cout << "Developing..." << endl;
                Game::langFlag = en_us;
                PAUSE;
                break;
            default:
                cout << Game::mainLang.ivldipt << endl;
                PAUSE;
                selectLang();
        }
    else
    {
        cout << Game::mainLang.ivldipt << endl;
        PAUSE;
        selectLang();
    }
    Game::mainLang.setLangStrings(Game::langFlag);
}

void selectSide()
{
    string in;
    cout << Game::mainLang.sidesel;
    cin >> in;
    in[0] = toupper(in[0]);
    while ((in != "B") && (in != "W"))
    {
        cout << Game::mainLang.ivldipt << endl;
        cout << Game::mainLang.sidesel;
        cin >> in;
        in[0] = toupper(in[0]);
    }
    Game::humanSide = ((in == "W") ? White : Black);
}

short selectdiff()
{
    if (Game::manualFlag)
        return Game::diff;

    short diff;
    if (!Game::autoFlag)
    {
        CLS;

        if (PRINT_VERSION)
            Game::mainLang.printVersion();
    }

    string in;

    for (int i = 0; i < 5; i++)
        cout << Game::mainLang.dif[i] << endl;
    cout << endl;
    cout << Game::mainLang.sglipt;

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
        return diff;
    }
    else
    {
        cout << Game::mainLang.ivldipt << endl;
        PAUSE;
        CLS;
        selectdiff();
    }
}

void isAssistMode()
{
    string in;
    cout << Game::mainLang.isass;
    cin >> in;
    in[0] = toupper(in[0]);
    while ((in != "Y") && (in != "N"))
    {
        cout << Game::mainLang.ivldipt << endl;
        cout << Game::mainLang.isass;
        cin >> in;
        in[0] = toupper(in[0]);
    }
    Game::assistFlag = (in == "Y");
}

void AchillesInit(short diff)
{
    switch (diff)
    {
        case 1:
            Game::maxDepth = 0;
            break;
        case 2:
            Game::maxDepth = 1;
            Game::finalSearch = false;
            Game::randomFlag = true;
            break;
        case 3:
            Game::maxDepth = 3;
            Game::finalSearch = false;
            Game::randomFlag = true;
            break;
        case 4:
            Game::maxDepth = 5;
            Game::finalSearch = false;
            Game::randomFlag = true;
            break;
        case 5:
            Game::maxDepth = 8;
            Game::finalSearch = true;
            Game::randomFlag = false;
            break;
        default:
            fatalError(1);
    }
}

#ifdef _WIN32
void theme()
{
    CLS;
    
    cout << Game::mainLang.seltheme << endll;
    for (int i = 0; i < 10; i++)
        cout << Game::mainLang.theme[i] << endl;
    cout << Game::mainLang.rdmtheme << endl;
    cout << endll;
    cout << Game::mainLang.triipt;

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
        cout << Game::mainLang.ivldipt << endl;
        PAUSE;
        theme();
    }
    cin.sync();
}
#endif

void settings()
{
    CLS;
    string in;
    for (int i = 0; i < 4; i++)
        cout << Game::mainLang.sts[i] << endl;
    cout << endl << Game::mainLang.sglipt;

    cin >> in;
    if (in.length() == 1 && isdigit(in[0]))
        switch (in[0])
        {
            case '1':
#ifdef _WIN32
                theme();
#else
                cout << Game::mainLang.themenspt << endl;
                PAUSE;
#endif
                break;
            case '2':
                selectLang();
                break;
            case '3':
                isAssistMode();
                break;
            case '0':
                menu();
            default:
                cout << Game::mainLang.ivldipt << endl;
                PAUSE;
        }
    else
    {
        cout << Game::mainLang.ivldipt << endl;
        PAUSE;
    }
    settings();
}

void debugMenu()
{
    Game::debugCalled = true;
    string in;
    cin >> in;
    transform(in.begin(), in.end(), in.begin(), ::toupper);
    if (in == "SETDEPTH")
    {
        cin >> Game::maxDepth;
        Game::manualFlag = true;
    }
    else if (in == "RANDOM")
        Game::randomFlag = true;
    else if (in == "DEBUG")
        Game::debugFlag = true;
    else if (in == "NDEBUG")
        Game::debugFlag = false;
    else if (in == "FLIP"&&Game::AIFlag == AI_MODE)
    {
        Game::humanSide ^= 1;
        if (Game::humanSide == Black)
            gameThread(Human, AI);
        else 
            gameThread(AI, Human);
    }
    else if (in == "WIN"&&Game::AIFlag == AI_MODE)
    {
        for (int i = 1; i <= 8; i++)
            for (int j = 1; j <= 8; j++)
                Game::board[i][j].stat = Status(Game::humanSide);
        Game::board.count();
        Game::AIPass = true;
        Game::board.movesRecord.resize(63);
        if (Game::humanSide == Black)
            gameThread(Human, AI);
        else
            gameThread(AI, Human);
    }
    else
        cout << "^&$^%#*$" << endl;
    PAUSE;
}


Board Game::board = Board();
Coord Game::inputCoord = {-1,-1};
const Coord Game::passCoord = {-1,-1};

bool Game::AIPass = false;
bool Game::randomFlag = false;
bool Game::manualFlag = false;
bool Game::UIFlag = false;
bool Game::AIFlag = false;
bool Game::debugFlag = false;
bool Game::assistFlag = false;
bool Game::inputFlag = false;
bool Game::humanSide = Black;
bool Game::saveSuccess = false;
bool Game::autoFlag = false;
bool Game::debugCalled = false;
bool Game::finalSearch = false;

short Game::maxDepth = 0;
short Game::diff = 1;

double Game::AchillesReturn = 0;

language Game::langFlag = en_us;

gameStatus Game::status = Idle;
langStrings Game::mainLang;

bool Game::liftTheTable()
{
    if (status == Playing)
    {
        status = Lifting;
        return true;
    }
    return false;;
}
