// Standard C++ library imports
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include <vector>
#include <iostream>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

// Import object classes
#include "src/Player.h"
#include "src/Lane.h"
#include "src/Obstacle.h"
#include "src/lighting.h"
#include "src/utli.h"
// Static global values for display dimensions
static int DISPLAY_WIDTH = 500;
static int DISPLAY_HEIGHT = 500;
static int DISPLAY_OFFSET_WIDTH;
static int DISPLAY_OFFSET_HEIGHT;

std::string player_model = "resource/cat.obj";

Player player = NULL;
Lane lane_left = NULL;
Lane lane_middle = NULL;
Lane lane_right = NULL;

// Player object always in the middle of the screen

static const float LANE_POS_INCREMENT = 9;

static int score;
static char scoreMessage[64] = { '\0' };
bool animate = true;
float gravity_constant = 0.04;
bool is_jump;

void drawLane()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    lane_left.render(player.positionZ);
    lane_middle.render(player.positionZ);
    lane_right.render(player.positionZ);
}

void movePlayer(int val)
{
    if (animate) {
        player.move();
        if (is_jump) {
            player.jump();
            player.apply_grav(gravity_constant);
        }
    }
    glutTimerFunc(1000 / 60, movePlayer, 0);
}

void check_collision() {
    if (player.positionX == -9) {
        if (lane_left.detect_collision(player.positionY, player.positionZ)) {
            score = 0;
            player.positionZ = 0;
        }
    }
    if (player.positionX == 0) {
        if (lane_middle.detect_collision(player.positionY, player.positionZ)) {
            score = 0;
            player.positionZ = 0;
        }
    }
    if (player.positionX == 9) {
        if (lane_right.detect_collision(player.positionY, player.positionZ)) {
            score = 0;
            player.positionZ = 0;
        }
    }
}

void showScore()
{
    // Calculate score
    score = (int)floor(player.positionZ / 3);

    // Position raster text below above the player
    glRasterPos3f(player.positionX + 15, player.positionY + 20, player.positionZ);

    // Populate score display message
    memset(scoreMessage, '\0', sizeof(scoreMessage));
    snprintf(scoreMessage, sizeof(scoreMessage),
        "Score: %d", score);

    // Populate raster image to display text
    glColor3f(1, 1, 1);
    for (int i = 0; i < strlen(scoreMessage); i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,
            scoreMessage[i]);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        player.positionX, player.positionY + 20, player.positionZ - 60,
        player.positionX, player.positionY, player.positionZ + 20,
        0, 1, 0
    );

    drawLane();
//    player.render();
    player.obj_render();
    showScore();
    check_collision();
    glFlush();
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
    case 27:
        exit(0);
        break;
    case 'p':
    case 'P':
        animate = !animate;
        break;
    case ' ':
        is_jump = true;
        player.reset();
        break;
    case '1':
        player.set_color(4);
        break;
    case '2':
        player.set_color(5);
        break;
    case '3':
        player.set_color(6);
        break;
    case 'r':
    case 'R':
        score = 0;
        player.positionZ = 0;
        break;
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (player.positionX > -1 * LANE_POS_INCREMENT)
            player.positionX -= LANE_POS_INCREMENT;
        break;
    case GLUT_KEY_LEFT:
        if (player.positionX < LANE_POS_INCREMENT)
            player.positionX += LANE_POS_INCREMENT;
        break;
    }
}

void init() {
    //GLUT init
    DISPLAY_OFFSET_WIDTH =
        ((glutGet(GLUT_SCREEN_WIDTH) - DISPLAY_WIDTH) / 2);
    DISPLAY_OFFSET_HEIGHT =
        ((glutGet(GLUT_SCREEN_HEIGHT) - DISPLAY_HEIGHT) / 2);

    glutInitWindowSize(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    glutInitWindowPosition(DISPLAY_OFFSET_WIDTH,
        DISPLAY_OFFSET_HEIGHT);

    glutCreateWindow("Prototype");
    utli::init();
    // class init
    player = Player(0, 0, 0, 0);

    player.load_obj(const_cast<char *>(player_model.c_str()));
    lane_left = Lane(-6, 0, 0, 1);
    lane_left.init(6, 100, 50, 100, 10000);

    lane_middle = Lane(3, 0, 0, 1);
    lane_middle.init(6, 100, 50, 100, 10000);


    lane_right = Lane(12, 0, 0, 1);
    lane_right.init(6, 100, 50, 100, 10000);

}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutTimerFunc(1000 / 60, movePlayer, 0);
    glutMainLoop();

    return 0;
}
