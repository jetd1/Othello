#include "IO.h"
#include <sstream>
#include <algorithm>


void printVersion()
{
    cout << "Othello Main Version " << MAIN_VERSION << endl;
    cout << "Jacob Version " << JACOB_VERSION << endl << endl;
    cout << "Copyleft 2015" << endl;
    cout << "By Jet" << endl;
    cout << endl;
}

// Mouse Callback
void mouseKey(int button, int state, int x, int y)
{
    if (!mouseInputAvalable) return;
    if (state != GLUT_DOWN) return;
    yBuffer[mouseMove] = (x / (screenSize / SIDE_LENGTH)) + 1;
    xBuffer[mouseMove] = (y / (screenSize / SIDE_LENGTH)) + 1;
    mouseMove++;
    mouseInputAvalable = false;
    return;
}

//For Mouse Input
Coord mouseInput()
{
    inputFlag = false;
    mouseInputAvalable = true;
    while (mouseMove == 0) SLP(100);
    Coord tmpCoord{xBuffer[mouseMove - 1], yBuffer[mouseMove - 1]};
    mouseMove--;
    inputFlag = true;
    return tmpCoord;
}

//For Keyboard Input
Coord keyboardInput()
{
    ////Echo
    if (AIFlag == AI_MODE)
        if (playerSide == Black)
            cout << "            Your(¡ñ) Turn:__\b\b";
        else
            cout << "            Your(¡ð) Turn:__\b\b";
    else
    {
        if (gameBoard == Black)
            cout << "           Black(¡ñ) Turn:__\b\b";
        else
            cout << "           White(¡ð) Turn:__\b\b";
    }

    string input;
    cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    if (input == "EXIT") exit(0);
    if (input == "MENU") menu();
    if (input == "UNDO")
    {
        gameBoard.save("undoTmp");
        loadGame("undoTmp", AIFlag + 1);
    }
    if (input == "SAVE")
    {
        if ((saveError = gameBoard.save()))
        {
            cout << "         Game Successfully Saved!" << endl;
            cout << "       Press Any Key to Main Menu...";

            PAUSE;
            menu();
        }
        else return keyboardInput();
    }
    if (input == "ABAB")
        debugMenu();

    Coord tmpCoord{};
    inputFlag = false;

    if (input.length() == 2)
    {
        if (input[0] >= START_COORD_Y&&input[0] <= END_COORD_Y&&input[1] >= START_COORD_X&&input[1] <= END_COORD_X)
        {
            input.assign(input.rbegin(), input.rend());
            inputFlag = true;
        }
        else if (input[0] >= START_COORD_X&&input[0] <= END_COORD_X&&input[1] >= START_COORD_Y&&input[1] <= END_COORD_Y)
            inputFlag = true;
        else return tmpCoord;

        tmpCoord.x = input[0] - '0';
        tmpCoord.y = input[1] - '@';
    }
    return tmpCoord;
}

void getCoord(getType T)
{
    switch (T)
    {
        case Player:
            if (UIFlag)
                inputCoord = mouseInput();
            else
                inputCoord = keyboardInput();
            break;
        case Computer:
            inputCoord = AI(gameBoard);
            break;
        default:
            fatalError(1);
    }

    if (inputFlag)
        gameBoard.movesRecord.push_back(inputCoord);
}

void loadGame(string loadName, int undoSteps)
{
    CLS;
    ifstream load(loadName + ".save");
    ifstream hload(loadName + ".hash");
    ostringstream sload, hsload;
    if (!load || !hload || !sload)
    {
        cout << "Unable to Open Saved File!" << endl;
        cout << "Press Any Key to Main Menu...";
        PAUSE;
        menu();
    }

    hash<string> hashptr;
    hsload << hload.rdbuf();
    sload << load.rdbuf();

    string saveHash = hsload.str();
    string file = sload.str();

    ostringstream convert;
    convert << hashptr(file);
    string fileHash = convert.str();

    if (fileHash != saveHash)
    {
        cout << "Saved File Damaged!" << endl;
        cout << "Press Any Key to Main Menu...";
        PAUSE;
        menu();
    }
    load.close();
    hload.close();

    gameBoard.clear();
    init();

    load.open(loadName + ".save");

    load >> AIFlag;
    load >> assistFlag;
    load >> playerSide;
    load >> diff;

    if (diff)
        JacobInit(diff);

    int movesCount;
    load >> movesCount;
    movesCount -= undoSteps;
    gameBoard.movesRecord.clear();

    for (int i = 0; i < movesCount; i++)
    {
        Coord tmpCoord{};
        load >> tmpCoord.x;
        load >> tmpCoord.y;
        gameBoard.movesRecord.push_back(tmpCoord);
    }
    load.close();

    for (int i = 0; i < movesCount; i++)
        gameBoard.move(gameBoard.movesRecord[i]);

    multiThread(0, nullptr);
}

void help()
{
    CLS;
    cout << "***************************************************" << endl;
    cout << endl;
    cout << "ON THE BOARD OF COMMAND LINE MODE:" << endl;
    cout << endl;
    cout << "'¡ñ' STANDS FOR BLACK  '¡ð' STANDS FOR WHITE" << endl;
    cout << "'+' MEANS THE CELL IS VALID TO PLACE YOUR STONE" << endl;
    cout << "' ' MEANS THE CELL IS CURRENT EMPTY AND INVALID" << endl;
    cout << endl;
    cout << "7A,A7,7a,a7 ARE ALL RECOGNIZABLE INPUTS" << endl;
    cout << endl;

    cout << "***************************************************" << endl;
    cout << endl;
    cout << "YOU CAN INPUT THESE COMMAND DURING THE GAME" << endl;
    cout << "INSTEAD OF INPUTTING THE COORDINATE:" << endl;
    cout << endl;
    cout << "1.EXIT: ABORT THE GAME AND EXIT." << endl << endl;
    cout << "2.MENU: ABORT THE GAME AND GO BACK TO THE MAIN MENU." << endl << endl;
    cout << "3.SAVE: SAVE THE GAME AND GO BACK TO THE MAIN MENU." << endl << endl;
    cout << "4.UNDO: UNDO YOUR (AND JACOB'S) LAST MOVE." << endl << endl;
    cout << "***************************************************" << endl;
    cout << endl << endl << endl;
    PAUSE;
    menu();
}
