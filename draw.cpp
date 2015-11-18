#include "elements.h"
#include "draw.h"
#include <cmath>

const int CIRCLE_MAX = 100;

int screenSize = 400;
bool drawable = true;

extern Board gameBoard;
extern bool modeFlag, assistFlag, sideFlag, inputFlag, playerSide;

extern void fatalError(unsigned ErrorCode);

void drawCircle(double x, double y, double r, status s)
{
    switch (s)
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
    for (int i = 0 ;i < CIRCLE_MAX; ++i)
    {
        glVertex2d(x+r*cos(2*M_PI*i/CIRCLE_MAX), y+r*sin(2*M_PI*i/CIRCLE_MAX));
    }
    glEnd();
}

void drawStar(double x, double y, double r, status s)
{
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    for (int i = 0; i < 2; ++i)
    {
        glVertex2d(x+r*cos(i*M_PI_2), y+r*sin(i*M_PI_2));
        glVertex2d(x+r*cos(i*M_PI_2+M_PI), y+r*sin(i*M_PI_2+M_PI));
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
            if (assistFlag && ((modeFlag == AI_MODE&&sideFlag == playerSide) || (modeFlag == NON_AI_MODE)))
            {
                drawStar(x, y, 0.07, Valid);
            }
            break;
        default:
            fatalError(1);
    }
}

void drawBoard()
{
    //Draw background
    glClearColor(0.54, 0.14, 0.0, 0.8);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(0.0,0.0,0.0);
    glLineWidth(3);
    glBegin(GL_LINES);
    for (int i = 1; i < 8; ++i)
    {
        glVertex2d(-1.0, 0.25*i - 1.0);
        glVertex2d(1.0, 0.25*i - 1.0);
    }
    for (int i = 1; i < 8; ++i)
    {
        glVertex2d(0.25*i - 1.0, -1.0);
        glVertex2d(0.25*i - 1.0, 1.0);
    }
    glEnd();
}

void drawChessPieces()
{
    for (int i = 1; i <= SIDE_LENGTH; ++i)
    {
        for (int j = 1; j <= SIDE_LENGTH; ++j)
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
                    if (assistFlag && ((modeFlag == AI_MODE&&sideFlag == playerSide) || (modeFlag == NON_AI_MODE)))
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
	drawChessPieces();
	glFlush();
	drawable = false;
}

void initdraw(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(screenSize, screenSize);
	glutCreateWindow("TEST");
	glutDisplayFunc(&display);
	glutMainLoop();
}

