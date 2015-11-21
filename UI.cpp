#include "elements.h"
#include <cmath>

const double M_PI=3.14159265358979323846;
int CIRCLE_MAX=50;

//const int CIRCLE_MAX = 7;

int screenSize=400;
bool drawable=true;

extern Board gameBoard;
extern bool AIFlag, assistFlag, inputFlag, playerSide;

extern void fatalError(unsigned ErrorCode);
extern void mouseKey(int button, int state, int x, int y);

void initDisplay()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void drawCircle(double x, double y, double r, status stat)
{

    switch (stat)
    {
        case Black:
            glColor3d(0.0, 0.0, 0.0);
            break;
        case White:
            glColor3d(1.0, 1.0, 1.0);
            break;
        default:
            fatalError(1);
    }
    glBegin(GL_POLYGON);
    for (int i=0; i<CIRCLE_MAX; ++i)
        glVertex2d(x+r*cos(2*M_PI*i/CIRCLE_MAX), y+r*sin(2*M_PI*i/CIRCLE_MAX));
    glEnd();
}

void drawPlus(double x, double y, double r)
{
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i=0; i<2; ++i)
    {
        glVertex2d(x+r*cos(i*M_PI/2), y+r*sin(i*M_PI/2));
        glVertex2d(x+r*cos(i*M_PI/2+M_PI), y+r*sin(i*M_PI/2+M_PI));
    }
    glEnd();
}

void drawCell(double x, double y, status s)
{
    switch (s)
    {
        case Black:
            drawCircle(x, y, 0.085, Black);
            break;
        case White:
            drawCircle(x, y, 0.085, White);
            break;
        case Empty:
            break;
        case Valid:
            if (assistFlag&&((AIFlag==AI_MODE&&gameBoard.sideFlag==playerSide)||(AIFlag==NON_AI_MODE)))
            {
                drawPlus(x, y, 0.07);
            }
            break;
        default:
            fatalError(1);
    }
}

void drawBoard()
{
    //Draw background
    glClearColor(0.54f, 0.14f, 0.0f, 0.8f);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.0, 0.0, 0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    for (int i=1; i<SIDE_LENGTH; ++i)
    {
        glVertex2d(-1.0, 0.25*i-1.0);
        glVertex2d(1.0, 0.25*i-1.0);
    }
    for (int i=1; i<SIDE_LENGTH; ++i)
    {
        glVertex2d(0.25*i-1.0, -1.0);
        glVertex2d(0.25*i-1.0, 1.0);
    }
    glEnd();
}

void drawStone()
{
    for (int i=1; i<=SIDE_LENGTH; ++i)
    {
        for (int j=1; j<=SIDE_LENGTH; ++j)
        {
            switch (gameBoard[i][j].stat)
            {
                case Black:
                    drawCell(-1.125+0.25*j, 1.125-0.25*i, Black);
                    break;
                case White:
                    drawCell(-1.125+0.25*j, 1.125-0.25*i, White);
                    break;
                case Empty:
                    break;
                case Valid:
                    if (assistFlag&&((AIFlag==AI_MODE&&gameBoard.sideFlag==playerSide)||(AIFlag==NON_AI_MODE)))
                    {
                        drawCell(-1.125+0.25*j, 1.125-0.25*i, Valid);
                    }
                    break;
                default:
                    fatalError(1);
            }
        }
    }
}

void display()
{
    if (!drawable) return;
    drawBoard();
    drawStone();
    glFlush();
    drawable=false;
}

void reshape(int width, int height)
{
    int screenSize=(width<height ? width : height);
    glViewport(0, 0, width, height);
    glLoadIdentity();
    glOrtho(-(GLfloat)width/screenSize, (GLfloat)width/screenSize,
        -(GLfloat)height/screenSize, (GLfloat)height/screenSize,
        -2.0f, 2.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

void initUI(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(50*SIDE_LENGTH, 50*SIDE_LENGTH);
    glutCreateWindow("Othello");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutDisplayFunc(&display);
    glutMouseFunc(&mouseKey);
    glutReshapeFunc(&reshape);
    initDisplay();
    glutMainLoop();
}

