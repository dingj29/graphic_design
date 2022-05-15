#ifdef __APPLE__
#  define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <list>
#include "particle.h"
using namespace std;
// Define the gloable variables
std::vector<Particle> particles = {};

#define PI 3.14159265

int horizontalView = 0;
int verticalView = 0;
int init_amount = 1;
double fraction = 0.3;
bool apply_fraction = false;
int fps = 20;
float gravity_constant = 0.015;
bool animate = true;
int animatedistance = 0;
bool LIGHTING_TOGGLE = false;
bool particle_camera = false;
bool catch_particle = false;
int particle_index = -1;
GLUquadric *gluQuadric;
//1 rubber 2 gold 3 Emerald 4 for floor:perl
// some materials example
float ambient[5][4]= {{0.0f,0.05f,0.05f,1.0f },
                      { 0.24725f, 0.1995f, 0.0745f, 1.0f },
                      { 0.0215f, 0.1745f, 0.0215f, 0.55f },
                      { 0.25f, 0.20725f, 0.20725f, 0.922f },
                      { 0.0f, 0.0f, 0.0f, 1.0f } };
float diffuse[5][4] = {{0.4f,0.5f,0.5f,1.0f },
                       {0.75164f, 0.60648f, 0.22648f, 1.0f },
                       {0.07568f, 0.61424f, 0.07568f, 0.55f },
                       {1.0f, 0.829f, 0.829f, 0.922f },
                       {0.01f, 0.01f, 0.01f, 1.0f} };
float specular[5][4] = {{0.04f,0.7f,0.7f,1.0f },
                        {0.628281f, 0.555802f, 0.366065f, 1.0f },
                        {0.633f, 0.727811f, 0.633f, 0.55f },
                        {0.296648f, 0.296648f, 0.296648f, 0.922f },
                        {0.50f, 0.50f, 0.50f, 1.0f } };
float shine[5]= {10.0f,51.2f,76.8f,11.264f,32.0f};

float light0[4][4] = {{100.0f, 100.0f, 50.0f, 1.0f},//pos amb dif spc
                      {0.8f,0.8f,0.8f,1.0f},
                      {0.8f, 0.2f, 0.8f, 1.0f},
                      {0.0f, 0.0f, 0.5f, 0.0f}};
float light1[4][4] = {{100.0f, 100.0f, 50.0f, 1.0f},//pos amb dif spc
                      {0.8f,0.8f,0.8f,1.0f},
                      {0.2f, 0.8f, 0.2f, 1.0f},
                      {0.0f, 0.5f, 0.0f, 0.0f}};
int light0_pos = 0;
int light1_pos = 0;

float cannon_x = 0;
float cannon_y = 0;

// Function that generate random Float number
float randomFloat(float upperBound) {
    return static_cast <float> (rand()) / static_cast <float> (RAND_MAX / upperBound);
}

// Function that generate random integer
int randomInt(int upperBound) {
    return rand() % upperBound;
}

// Function that draw the 3D plane and the cylinder canno and offer them material
void drawGround() {
    glPushMatrix();
    glColor3f(0, 1, 1);
    if (LIGHTING_TOGGLE == true) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[3]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[3]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[3]);
        glMaterialf(GL_FRONT, GL_SHININESS, shine[3]);
    }
    glTranslated(0, 0, -80);
    glutSolidCube(160);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    if (LIGHTING_TOGGLE == true) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[4]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[4]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[4]);
        glMaterialf(GL_FRONT, GL_SHININESS, shine[4]);
    }
    glRotated(cannon_x, 0, 1, 0);
    glRotated(cannon_y, 1, 0, 0);
    if(gluQuadric == NULL)
        gluQuadric = gluNewQuadric();
    gluCylinder(gluQuadric,2,2,8,5,5);
    glPopMatrix();
}

// Function that draw each particles based on the parameters
void drawParticle(double red, double green, double blue, double pos0, double pos1,
    double pos2, double ang0, double ang1, double ang2, int size, int shape, int mat) {
    glColor3f(red, green, blue);
    glPushMatrix();
    glTranslated(pos0, pos1, pos2);
    glRotatef(animatedistance, ang0, ang1, ang2);
    if (LIGHTING_TOGGLE == true) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient[mat]);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse[mat]);
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular[mat]);
        glMaterialf(GL_FRONT, GL_SHININESS, shine[mat]);
    }
    if (shape % 2 == 1) {
        glNormal3f(0.25f,0.25f,0.5f);
        glutSolidSphere(size, 10, 10);
    }
    else {
        glNormal3f(0.0f,0.1f,0.9f);
        glutSolidCube(size);
    }
    glPopMatrix();
}

// Function that iterate the vector and call drawParticle
void drawScene(void) {
    for (auto p : particles) {
        drawParticle(p.rgb[0], p.rgb[1], p.rgb[2], p.pos[0], p.pos[1], p.pos[2], p.ang[0], p.ang[1], p.ang[2], p.size, p.shape, p.material);
    }
}

// The main display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (particle_camera && !catch_particle) {
        gluLookAt(particles[0].pos[0], particles[0].pos[1], particles[0].pos[2], 0, 0, 40, 0, 0, 1);
    }
    else {
        gluLookAt(150, 0, 120, 0, 0, 40, 0, 0, 1);
    }
    glPushMatrix();
    if (!particle_camera){
        glRotated(verticalView, 0, 1, 0);
        glRotated(horizontalView, 0, 0, 1);
    }

    if (LIGHTING_TOGGLE == true) {
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        light0[0][0] = light0_pos;
        glLightfv(GL_LIGHT0, GL_POSITION, light0[0]);
        glLightfv(GL_LIGHT0, GL_AMBIENT, light0[1]);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0[2]);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0[3]);

        light1[0][1] = light1_pos;
        glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_POSITION, light1[0]);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1[1]);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, light1[2]);
        glLightfv(GL_LIGHT1, GL_SPECULAR, light1[3]);
    }
    else {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }
    drawGround();
    drawScene();
    glPopMatrix();
    glutSwapBuffers();
}

// The resize function
void handleReshape(int w, int h) {// no use currently, just copied from tut4
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 1, 1, 500);
    glutPostRedisplay();
    glMatrixMode(GL_MODELVIEW);
}

// Function that call constructor of Particle class by passing parameters and adding the created particle objects to the vector. 
void add_particals(int amount) {
    for (int i = 0; i < amount; ++i) {//spawn particals.
        double temp_pos[3] = { 0,0,4 };
        double vertical_spd = randomFloat(0.5) + 0.5;
        double temp_dir[3] = { randomFloat(0.2) - 0.1 + vertical_spd * (cannon_x/45.0f), randomFloat(0.2) - 0.1 - vertical_spd * (cannon_y/45.0f),
                               vertical_spd };
        double temp_rot[3] = { randomFloat(2),randomFloat(2),randomFloat(2) };
        double temp_col[3] = { randomFloat(1),randomFloat(1),randomFloat(1) };
        Particle temp = Particle(temp_pos, temp_dir, randomInt(4) + 1, temp_rot,
            randomInt(3), temp_col, randomInt(3),
            randomInt(100) + 700, randomInt(5));
        if (catch_particle) {
            particles.insert(particles.begin(), temp);
            particle_index = 0;
            catch_particle = false;
        }
        particles.push_back(temp);
    }
}

// the Init function
void init() {
    srand(time(nullptr));
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(300, 300);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("A3");
    add_particals(init_amount);

}

// Function that move the particles around, apply gravity. Also check to delete if a particle reaches it predetermined limit
void moveAll(void) {
    for (int i = 0; i < static_cast<int>(particles.size()); i++) {
        if (particles[i].check_delet()) {
            if (particle_camera && i == particle_index){
                particle_camera = false;
            }
            particles.erase(particles.begin() + i);
            i--;
        }
        else {
            particles[i].check_delet();
            if (apply_fraction) {
                particles[i].move_with_fract(fraction);
            }
            else
            {
                particles[i].move();
            }
            particles[i].apply_grav(gravity_constant);
        }
    }
}

// Clear all the particles
void erase_all() {
    particles.clear();
}

// The animation function
void animation(int value) {
    if (animate) {
        animatedistance += 1;
        add_particals(1);
    }
    moveAll();
    glutPostRedisplay();
    glutTimerFunc(700 / fps, animation, 0);
}

// The keyboard function
void kbd(unsigned char key, int x, int y) {
    switch (key) {
    case 'i':
    case 'I':
        light0_pos = std::max(-200, light0_pos - 20);
        break;
    case 'o':
    case 'O':
        light0_pos = std::min(200, light0_pos + 20);
        break;
    case 'y':
    case 'Y':
        light1_pos = std::max(-200, light1_pos - 20);
        break;
    case 'u':
    case 'U':
        light1_pos = std::min(200, light1_pos + 20);
        break;
    case 'w':
    case 'W':
        cannon_x = std::max(-45.0f, cannon_x - 5.0f);
        break;
    case 's':
    case 'S':
        cannon_x = std::min(45.0f, cannon_x + 5.0f);
        break;
    case 'a':
    case 'A':
        cannon_y = std::min(45.0f, cannon_y + 5.0f);
        break;
    case 'd':
    case 'D':
        cannon_y = std::max(-45.0f, cannon_y - 5.0f);
        break;
    case 'q':
    case 'Q':
        glClear(GL_COLOR_BUFFER_BIT);
        erase_all();
        exit(0);
        break;
    case ' ':
        animate = !animate;
        break;
    case 'r':
    case 'R':
        animate = true;
        glClear(GL_COLOR_BUFFER_BIT);
        erase_all();
        break;
    case 'f':
    case 'F':
        apply_fraction = !apply_fraction;
        break;
    case 'l':
    case 'L':
        LIGHTING_TOGGLE = !LIGHTING_TOGGLE;
        break;
    case 'n':
    case 'N':
        if (particle_camera)
        {
            particle_index = -1;
            catch_particle = false;
        }
        else
        {
            catch_particle = true;
        }
        particle_camera = !particle_camera;
        break;
    default:
        break;
    }
}

// The special keyboard function, uparrow,downarrow, leftarrow and rightarrow
void spcialkbd(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        verticalView = std::min(70, verticalView + 5);
        break;
    case GLUT_KEY_DOWN:
        verticalView = std::max(-30, verticalView - 5);
        break;
    case GLUT_KEY_LEFT:
        horizontalView = (horizontalView + 10) % 360;
        break;
    case GLUT_KEY_RIGHT:
        horizontalView = (horizontalView - 10) % 360;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void showMenu() {
    cout << "Pressing f or F to activate or deactivate friction mode" << endl;
    cout << "Pressing upArrow to rotate the scene up about x-axis" << endl;
    cout << "Pressing downArrow to rotate the scene down about x-axis" << endl;
    cout << "Pressing rightArrow to rotate the scene right about y-axis" << endl;
    cout << "Pressing leftArrow to rotate the scene left about y-axis" << endl;
    cout << "Pressing space to pause and resume the simulation" << endl;
    cout << "Pressing r or R to reset the particle system to original state" << endl;
    cout << "Pressing l or L to toggle the light or remove the light" << endl;
    cout << "Pressing n or N to place camera position inside the next particles enters the system" << endl;
    cout << "Pressing w or W to rotate the cannon to back and effects initial particle trajectory" << endl;
    cout << "Pressing s or S to rotate the cannon to front and effects initial particle trajectory" << endl;
    cout << "Pressing a or A to rotate the cannon to left and effects initial particle trajectory" << endl;
    cout << "Pressing d or D to rotate the cannon to right and effects initial particle trajectory" << endl;
    cout << "Pressing o or O to move first light source on it's Y axis to Positive direction" << endl;
    cout << "Pressing i or I to move first light source on it's Y axis to negative direction" << endl;
    cout << "Pressing u or U to move second light source on it's X axis to Positive direction" << endl;
    cout << "Pressing y or Y to move second light source on it's X axis to negative direction" << endl;
}

// The main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    init();
    showMenu();
    glutReshapeFunc(handleReshape);
    glutKeyboardFunc(kbd);
    glutDisplayFunc(display);
    glutSpecialFunc(spcialkbd);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glutTimerFunc(1000 / fps, animation, 0);
    glutMainLoop();
    return 0;
}
