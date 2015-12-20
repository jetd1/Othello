#include "display.h"
#include <cmath>

inline void setVertexColor(double x, double y)
{
    double p = pow(((pow(x, 8) + pow(y, 8)) / 2.0), 0.125) / FLOOR_SHADE_SIZE;
    double temp = (p < 2) ? (-(p - 2)*(p - 2) + 1) : 1.0;
    glColor3d(temp, temp, temp);
}

void initDisplay()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GLUT_MULTISAMPLE);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_NORMALIZE);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);

    GLfloat ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specref);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 10);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    GLfloat light_0_position[] = {0.0, 0.0, 40.0, 1.0};
    GLfloat light_1_position[] = {20.0, 20.0, 20.0, 1.0};
    GLfloat light_2_position[] = {20.0, -20.0, 20.0, 1.0};
    GLfloat light_3_position[] = {-20.0, 0.0, 20.0, 1.0};
    GLfloat light_0_dir[] = {0.0, 0.0, -1.0};
    GLfloat light_1_dir[] = {-20.0, -20.0, -17.0};
    GLfloat light_2_dir[] = {-20.0, 20.0, -17.0};
    GLfloat light_3_dir[] = {20.0, 0.0, -17.0};

    GLfloat color_white[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat color_black[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat color_red[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat color_green[] = {0.0, 1.0, 0.0, 1.0};
    GLfloat color_blue[] = {0.0, 0.0, 1.0, 1.0};
    GLfloat ambientLight[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat diffuseLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat globalAmbient[] = {0.3f, 0.3f, 0.3f, 1.0f};

    glLightfv(GL_LIGHT1, GL_POSITION, light_1_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_1_dir);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color_red);
    glLightfv(GL_LIGHT1, GL_SPECULAR, color_red);
    glLightfv(GL_LIGHT2, GL_POSITION, light_2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_2_dir);
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, color_green);
    glLightfv(GL_LIGHT2, GL_SPECULAR, color_green);
    glLightfv(GL_LIGHT3, GL_POSITION, light_3_position);
    glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, light_3_dir);
    glLightfv(GL_LIGHT3, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, color_blue);
    glLightfv(GL_LIGHT3, GL_SPECULAR, color_blue);
    glLightfv(GL_LIGHT0, GL_POSITION, light_0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_0_dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.5);
    glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, 90.0);
    glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 0.5);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 30);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
}

void Fog()
{
    if (Game::status == Pause)
    {
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_EXP2);
        glFogf(GL_FOG_DENSITY, 0.15f);
        glFogfv(GL_FOG_COLOR, fogColorPause);
    }
    else if (Game::status == Lifting)
    {
        glEnable(GL_FOG);
        glFogi(GL_FOG_MODE, GL_EXP);
        glFogf(GL_FOG_DENSITY, fogDensity);
        glFogfv(GL_FOG_COLOR, fogColorFocus);
    }
    else glDisable(GL_FOG);
}

void Lights()
{
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT0);
}

void drawStone()
{
    if (Game::status == Idle) return;
    for (auto stone : stoneList)
    {
        if (stone.getColor() == Valid)
        {
            if (Game::AIFlag && !Game::board == Game::humanSide) continue;
            if ((Game::status == Playing) && Game::assistFlag)
            {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                glTranslated(stone.getX(), stone.getY(), stone.getZ());

                glTranslated(0.0, 0.0, 0.0001);
                if (~Game::board == Black) glColor3d(0.2, 0.2, 0.2);
                if (~Game::board == White) glColor3d(0.8, 0.8, 0.8);
                glBegin(GL_QUADS);
                glVertex3d(-STONE_INTERVAL / 2.0, -STONE_INTERVAL / 2.0, 0.0);
                glVertex3d(-STONE_INTERVAL / 2.0, STONE_INTERVAL / 2.0, 0.0);
                glVertex3d(STONE_INTERVAL / 2.0, STONE_INTERVAL / 2.0, 0.0);
                glVertex3d(STONE_INTERVAL / 2.0, -STONE_INTERVAL / 2.0, 0.0);
                glEnd();
                glPopMatrix();
            }
            continue;
        }
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslated(stone.getX(), stone.getY(), stone.getZ());
        glRotated((atan2(stone.getAxisy(), stone.getAxisx() / M_PI) * 180 - 90), 0.0, 0.0, 1.0);
        if ((stone.getAxisy() != 0.0) && (stone.getAxisx() != 0.0))
            glRotated((atan2(stone.getAxisz(), sqrt(stone.getAxisx()*stone.getAxisx() + stone.getAxisy()*stone.getAxisy()))) * 180 / M_PI, stone.getAxisy(), -stone.getAxisx(), 0.0);
        glRotated(stone.getAngle(), 0.0, 1.0, 0.0);
        glTranslated(0.0, 0.0, STONE_HEIGHT / 4);

        if (stone.getColor() == White) { glScaled(1.0, 1.0, -1.0); glTranslated(0.0, 0.0, -STONE_HEIGHT / 2); }
        glPushMatrix();
        glTranslated(0.0, 0.0, STONE_HEIGHT / 4);
        glColor3d(0.0, 0.0, 0.0);
        glutSolidCylinder(STONE_RADIUS, STONE_HEIGHT / 2, CYSIDES, 1);
        glPopMatrix();
        glTranslated(0.0, 0.0, -STONE_HEIGHT / 4);
        glColor3d(1.0, 1.0, 1.0);
        glutSolidCylinder(STONE_RADIUS, STONE_HEIGHT / 2, CYSIDES, 1);
        glPopMatrix();
    }
}

void drawBackGround()
{
    glEnable(GL_LIGHTING);
    glBegin(GL_QUAD_STRIP);
    glColor3d(1.0, 1.0, 1.0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(-FLOOR_SIZE, -FLOOR_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(-FLOOR_CENTER_SIZE, -FLOOR_CENTER_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(-FLOOR_SIZE, FLOOR_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(-FLOOR_CENTER_SIZE, FLOOR_CENTER_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(FLOOR_SIZE, FLOOR_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(FLOOR_CENTER_SIZE, FLOOR_CENTER_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(FLOOR_SIZE, -FLOOR_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(FLOOR_CENTER_SIZE, -FLOOR_CENTER_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(-FLOOR_SIZE, -FLOOR_SIZE, 0);
    glNormal3d(0.0, 0.0, 1.0);
    glVertex3i(-FLOOR_CENTER_SIZE, -FLOOR_CENTER_SIZE, 0);
    glEnd();

    glBegin(GL_QUADS);
    for (double i = -FLOOR_CENTER_SIZE; i < FLOOR_CENTER_SIZE; i += FLOOR_GRID_SIZE)
    {
        for (double j = -FLOOR_CENTER_SIZE; j < FLOOR_CENTER_SIZE; j += FLOOR_GRID_SIZE)
        {
            setVertexColor(i, j);
            glVertex3d(i, j, 0);
            setVertexColor(i, j + FLOOR_GRID_SIZE);
            glVertex3d(i, j + FLOOR_GRID_SIZE, 0);
            setVertexColor(i + FLOOR_GRID_SIZE, j + FLOOR_GRID_SIZE);
            glVertex3d(i + FLOOR_GRID_SIZE, j + FLOOR_GRID_SIZE, 0);
            setVertexColor(i + FLOOR_GRID_SIZE, j);
            glVertex3d(i + FLOOR_GRID_SIZE, j, 0);
        }
    }
    glEnd();
    glDisable(GL_LIGHTING);

}

void drawCursor()
{
    if (Game::status != Playing) return;

    glEnable(GL_LIGHTING);
    glTranslated(0.0, 0.0, 0.01);

    double alignx = int(floatingx * BOARD_SIZE + BOARD_SIZE) / (BOARD_SIZE + 0.0) - 1.0;
    double aligny = int(floatingy * BOARD_SIZE + BOARD_SIZE) / (BOARD_SIZE + 0.0) - 1.0;
    double tiny = 1.0 / BOARD_SIZE;

    if (alignx < -0.5) return;
    if (aligny < -0.5) return;
    if (alignx > 0.5 - 1.0 / BOARD_SIZE) return;
    if (aligny > 0.5 - 1.0 / BOARD_SIZE) return;
    glBegin(GL_QUAD_STRIP);
    glColor4d(0.0, 1.0, 1.0, 0.7);
    glVertex3d(alignx, aligny, 0.0);
    glVertex3d(alignx + tiny, aligny, 0.0);
    glVertex3d(alignx, aligny + tiny, 0.0);
    glVertex3d(alignx + tiny, aligny + tiny, 0.0);
    glEnd();
}

void drawTable()
{
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_LIGHTING);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
    glPushMatrix();
    glTranslated(0.0, 0.0, TABLE_HEIGHT);
    glScaled(TABLE_SIZE, TABLE_SIZE, TABLE_THICKNESS);
    glColor4d(0.6, 0.6, 0.6, 1.0);
    glutWireCube(1);
    glColor4d(1.0, 1.0, 1.0, 0.6);
    glutSolidCube(1);
    glTranslated(0.0, 0.0, 0.5);
    double scaleCoeffiency = BOARD_SIZE * STONE_INTERVAL / TABLE_SIZE;
    glScaled(scaleCoeffiency, scaleCoeffiency, scaleCoeffiency);
    glLineWidth(3);
    glBegin(GL_LINES);
    for (double i = 1.0; i < BOARD_SIZE; ++i)
    {
        glVertex3d(i / BOARD_SIZE - 0.5, -0.5, 0.0);
        glVertex3d(i / BOARD_SIZE - 0.5, 0.5, 0.0);
    }
    glEnd();

    glBegin(GL_LINES);
    for (double i = 1.0; i < BOARD_SIZE; ++i)
    {
        glVertex3d(-0.5, i / BOARD_SIZE - 0.5, 0.0);
        glVertex3d(0.5, i / BOARD_SIZE - 0.5, 0.0);
    }
    glEnd();
    drawCursor();
    glPopMatrix();
}

void display()
{
    glClearColor(backGroundColor, backGroundColor, backGroundColor, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Fog();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (Game::status == Lifting) gluLookAt(zoom * cos(theta / 180.0 * M_PI) * sin(fai / 180.0 * M_PI) + xcenter,
        zoom * sin(theta / 180.0 * M_PI) * sin(fai / 180.0 * M_PI) + ycenter,
        zoom * cos(fai / 180.0 * M_PI) + zcenter,
        xcenter, ycenter, zcenter,
        0.0, 0.0, 1.0);
    else gluLookAt(zoom * cos(theta / 180.0 * M_PI) * sin(fai / 180.0 * M_PI),
        zoom * sin(theta / 180.0 * M_PI) * sin(fai / 180.0 * M_PI),
        zoom * cos(fai / 180.0 * M_PI),
        0.0, 0.0, TABLE_HEIGHT + TABLE_THICKNESS / 2,
        0.0, 0.0, 1.0);
    Lights();
    drawBackGround();
    drawTable();
    drawStone();
    if (Game::status == Pause)
    {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_LIGHTING);
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glColor4d(1.0, 0.0, 0.0, 0.8);
        glRectd(-0.3, 0.3, 0.3, 0.5);
        glColor4d(1.0, 1.0, 0.0, 0.8);
        glRectd(-0.3, 0.0, 0.3, 0.2);
        glColor4d(0.0, 1.0, 0.0, 0.8);
        glRectd(-0.3, -0.3, 0.3, -0.1);
        glColor4d(0.0, 0.0, 1.0, 0.8);
        glRectd(-0.3, -0.6, 0.3, -0.4);

        glColor4d(0.0, 0.0, 0.0, 0.9);

        glRasterPos2d(-0.07, 0.38);
        for (int k = 0; k < 4; ++k)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s_Save[k]);

        glRasterPos2d(-0.07, 0.08);
        for (int k = 0; k < 4; ++k)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s_Load[k]);

        glRasterPos2d(-0.19, -0.22);
        for (int k = 0; k < 13; ++k)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s_Save_and_Quit[k]);

        glRasterPos2d(-0.25, -0.52);
        for (int k = 0; k < 19; ++k)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s_Quit_without_saving[k]);

        glPopMatrix();

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);
    }
    glutSwapBuffers();
}

void reshape(int width, int height)
{
    screenSize = (width < height ? width : height);
    screenWidth = width;
    screenHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-(GLfloat)screenWidth / screenSize, (GLfloat)screenWidth / screenSize,
        -(GLfloat)screenHeight / screenSize, (GLfloat)screenHeight / screenSize,
        1.0f, 1000.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    glutPostRedisplay();
}

void displayThread(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(screenSize, screenSize);
    glutCreateWindow("JetOthello");
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
    glutDisplayFunc(&display);
    glutMouseFunc(&mouseKey);
    glutMotionFunc(&mouseMotion);
    glutPassiveMotionFunc(&mouseMotion);
    glutReshapeFunc(&reshape);
    glutKeyboardFunc(&keyboardCallback);
    glutSpecialFunc(&skeyboardCallback);
    glutKeyboardUpFunc(&keyboardUpCallback);
    glutSpecialUpFunc(&skeyboardUpCallback);
    initDisplay();
    refreshModel(false);
    glutTimerFunc(0, &timerCallback, 0);
    glutMainLoop();
}
