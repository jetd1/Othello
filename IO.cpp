#include "IO.h"
#include <sstream>
#include <algorithm>

//For Keyboard Input
Coord keyboardInput()
{
    ////Echo
    if (Game::AIFlag == AI_MODE)
        if (Game::humanSide == Black)
            cout << Game::mainLang.ytrn1;
        else
            cout << Game::mainLang.ytrn1;
    else
    {
        if (Game::board == Black)
            cout << Game::mainLang.btrn;
        else
            cout << Game::mainLang.wtrn;
    }

    string input;
    cin >> input;

    transform(input.begin(), input.end(), input.begin(), ::toupper);

    if (input == "EXIT") exit(0);
    if (input == "MENU") menu();
    if (input == "UNDO") Game::board.undo();
    if (input == "SAVE")
    {
        Game::saveSuccess = Game::board.save();
        if (Game::saveSuccess)
        {
            cout << Game::mainLang.savess << endl;
            cout << Game::mainLang.gotomainspc << Game::mainLang.gotomain;

            PAUSE;
            menu();
        }
        else return keyboardInput();
    }
    if (input == "ABAB")
        debugMenu();

    Coord tmpCoord{};
    Game::inputFlag = false;

    if (input.length() == 2)
    {
        if (input[0] >= 'A'&&input[0] <= 'H'&&input[1] >= '1'&&input[1] <= '8')
        {
            input.assign(input.rbegin(), input.rend());
            Game::inputFlag = true;
        }
        else if (input[0] >= '1'&&input[0] <= '8'&&input[1] >= 'A'&&input[1] <= 'H')
            Game::inputFlag = true;
        else return tmpCoord;

        tmpCoord.x = input[0] - '0';
        tmpCoord.y = input[1] - '@';
    }
    return tmpCoord;
}

void getCoord(playerType T)
{
    switch (T)
    {
        case Human:
            if (Game::UIFlag)
                Game::inputCoord = mouseInput();
            else
                Game::inputCoord = keyboardInput();
            break;
        case AI:
                Game::inputCoord = CallAI(Game::board);
            break;
        default:
            fatalError(1);
    }
}

void renewMouseStat(double x, double y, int button)
{
    static int button_old = 0;
    static double x_old = 0, y_old = 0;
    if (Game::status == Lifting)
    {
        if (LEFT_MOUSE_BUTTON & button & button_old)
        {
            theta -= 100 * (x - x_old);
            fai += 100 * (y - y_old);
            if (fai > 89.0) fai = 89.0;
            if (fai < 1.0) fai = 1.0;
        }
    }
    else if (Game::status == Playing)
    {
        //They are actually playing.
        floatingx = x;
        floatingy = y;
        if (RIGHT_MOUSE_BUTTON & button) needUndo = true;
    }
    else if ((Game::status == Pause) && Game::UIFlag)
    {
        if (LEFT_MOUSE_BUTTON & button)
        {
            if ((x >= -0.15) && (x <= 0.15))
            {
                if ((y >= 0.15) && (y <= 0.25))
                    Game::board.save();
                else if ((y >= 0.0) && (y <= 0.1))
                    Game::board.load();
                else if ((y >= -0.15) && (y <= -0.05))
                {
                    Game::saveSuccess = Game::board.save();
                    Game::status = End;
                }
                else if ((y >= -0.3) && (y <= -0.2))
                    Game::status = End;
            }
        }
    }
    button_old = button;
    x_old = x; y_old = y;
}

double zoomScale(double zoom, bool zoomOut)
{
    if (zoomOut) return zoom * 0.95 + MAX_ZOOM * 0.05;
    else return zoom * 0.95 + MIN_ZOOM * 0.05;
}

// Mouse Callback
void mouseKey(int button, int state, int x, int y)
{
    if (GLUT_DOWN == state) switch (button)
    {
        case GLUT_LEFT_BUTTON:
            mouseButton |= LEFT_MOUSE_BUTTON;
            break;
        case GLUT_MIDDLE_BUTTON:
            mouseButton |= MIDDLE_MOUSE_BUTTON;
            break;
        case GLUT_RIGHT_BUTTON:
            mouseButton |= RIGHT_MOUSE_BUTTON;
            break;
    }
    else switch (button)
    {
        case GLUT_LEFT_BUTTON:
            mouseButton &= ~LEFT_MOUSE_BUTTON;
            break;
        case GLUT_MIDDLE_BUTTON:
            mouseButton &= ~MIDDLE_MOUSE_BUTTON;
            break;
        case GLUT_RIGHT_BUTTON:
            mouseButton &= ~RIGHT_MOUSE_BUTTON;
            break;
    }
    if (GLUT_WHEEL_DOWN == button) zoom = zoomScale(zoom, true);
    if (GLUT_WHEEL_UP == button) zoom = zoomScale(zoom, false);

    renewMouseStat(double(x - screenWidth / 2.0) / screenSize,
        double(screenHeight / 2.0 - y) / screenSize,
        mouseButton);

    if (Game::status != Playing) return;
    if (state != GLUT_UP) return;
    if ((GLUT_WHEEL_DOWN == button) || (GLUT_WHEEL_UP == button)) return;

    int step = (screenSize / BOARD_SIZE);

    yBuffer = (x - screenWidth / 2 + screenSize / 2 + screenSize) / step - BOARD_SIZE + 1;
    xBuffer = (y - screenHeight / 2 + screenSize / 2 + screenSize) / step - BOARD_SIZE + 1;
    hasMouseInput = true;
    return;
}

//Mouse Passive Callback
void mouseMotion(int x, int y)
{
    renewMouseStat((double)(x - screenWidth / 2.0) / screenSize,
        (double)(screenHeight / 2.0 - y) / screenSize,
        mouseButton);
}

void update()
{
    if (kbstat['l'] && (Game::status == Playing)) Game::liftTheTable();
    if (kbstat['\x1B'] && Game::UIFlag)
    {
        if (Game::status == Playing) Game::status = Pause;
        else if (Game::status == Pause) Game::status = Playing;
    }
    if (kbstat['\x11'] && (Game::status == Lifting)) isFocus = true;

    if (kbstat['w'] && (Game::status == Playing)) fai = 1.0 * 0.05 + fai * 0.95;
    if (kbstat['s'] && (Game::status == Playing)) fai = 50.0 * 0.05 + fai * 0.95;
}

// Keyboard Callback
void keyboardCallback(unsigned char key, int _x, int _y)
{
    kbstat[key] = 1;
    update();
}

void keyboardUpCallback(unsigned char key, int x, int y)
{
    kbstat[key] = 0;
    update();
}

// SpecialKeyboard Callback
void skeyboardCallback(int key, int _x, int _y)
{
    switch (key)
    {
        case GLUT_KEY_CTRL_L:
        case GLUT_KEY_CTRL_R:
            kbstat['\x11'] = 1;
            break;
        case GLUT_KEY_SHIFT_L:
        case GLUT_KEY_SHIFT_R:
            kbstat['\x0F'] = 1;
            break;
    }
    update();
}


void skeyboardUpCallback(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_CTRL_L:
        case GLUT_KEY_CTRL_R:
            kbstat['\x11'] = 0;
            break;
        case GLUT_KEY_SHIFT_L:
        case GLUT_KEY_SHIFT_R:
            kbstat['\x0F'] = 0;
            break;
    }
    update();
}

//For Mouse Input
Coord mouseInput()
{
    while (Game::status == Pause) SLP(10);
    while ((Game::status == Playing) && !hasMouseInput) SLP(10);
    hasMouseInput = false;
    if (Game::status != Playing)
    {
        while (Game::status != End) SLP(10);
        Game::status = Idle;
    }
    if (needUndo) 
    { 
        needUndo = false;
        Game::board.undo();
        return{-368,-368};
    }
    Game::inputFlag = true;
    return{xBuffer, yBuffer};
}

ostream& endll(ostream& strm)
{
    strm.put('\n');
    strm.put('\n');
    strm.flush();
    return strm;
}

