#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <iostream>
#include <cassert>
#include <cmath>
#include <random>
#include <vector>
#include "mathLib2D.h"

using namespace std;

/* Global Variables */
static GLsizei width, height;
int buttonPress = 0;
bool animate = true;
int num_of_points = 8;
float max_growth = 20;
bool feature_color = false;
bool feature_grow_split = false;
Point2D mouseLocation(0.0f, 0.0f, 0);

//for radius
constexpr int RADIUS_MAX = 600;
constexpr int RADIUS_MIN = 30;

//for point
constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_X_MAX = 800;
constexpr int FLOAT_Y_MAX = 600;

//For vector
constexpr int FLOAT_LOW = -100;
constexpr int FLOAT_HIGH = 100;

//For speed
constexpr int FLOAT_MINS = 1;
constexpr int FLOAT_MAXS = 10;

//For size
constexpr int SIZE_MINS = 5;
constexpr int SIZE_MAXS = 10;

//For color
constexpr int COLOR_MIN = 0;
constexpr int COLOR_MAX = 1;

/* Set possible value range for x, y, speed, size and color */
random_device rd;
default_random_engine eng(rd());
uniform_real_distribution<> distr(FLOAT_MIN, FLOAT_X_MAX);
uniform_real_distribution<> distr2(FLOAT_MIN, FLOAT_Y_MAX);

uniform_real_distribution<> vector_distr(FLOAT_LOW, FLOAT_HIGH);

uniform_real_distribution<> speed_distr(FLOAT_MINS, FLOAT_MAXS);

uniform_real_distribution<> size_distr(SIZE_MINS, SIZE_MAXS);

uniform_real_distribution<> color_distr(COLOR_MIN, COLOR_MAX);

uniform_real_distribution<> range_distr(RADIUS_MIN, RADIUS_MAX);

// set the global variable range
float rangeRadius = (float)range_distr(eng);

/* create vectors for Point2D, vector, speedand Color */
vector<Point2D> pointVector;
vector<Vec2D> vectorVector;
vector<float> speedVector;
vector<Color> colorVector;

/* Function which draws a point at x and y*/
void Point2D::drawPoint(float x, float y, float size, float red, float green, float blue) {
	glPointSize(size);
	glColor3f(red, green, blue);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
	glutPostRedisplay();
}

/* Function which generate a vector of speed in float */
void generateSpeed(void) {
	for (int counter = 0; counter < num_of_points; counter++) {
		speedVector.push_back((float)speed_distr(eng));
	}
}

/* Function which generate a vector of Point2D */
void generatePoint2D(void) {
	for (int counter = 0; counter < num_of_points; counter++) {
		pointVector.push_back(Point2D((float)distr(eng), (float)distr2(eng), (float)size_distr(eng)));
	}
}

/* Function which generate a vector of Vec2D */
void generateVector2D(void) {
	for (int counter = 0; counter < num_of_points; counter++) {
		vectorVector.push_back(Vec2D((float)vector_distr(eng), (float)vector_distr(eng)).normalize());
	}
}

/* Function which generate a vector of Color */
void generateColor(void) {
	for (int counter = 0; counter < num_of_points; counter++) {
		colorVector.push_back(Color((float)color_distr(eng), (float)color_distr(eng), (float)color_distr(eng)));
	}
}

/* Function which initialize a set of vectors for particle */
void generate_all(void) {
	generatePoint2D();
	generateVector2D();
	generateSpeed();
	generateColor();
}

/* Function which erase the vectors of a specific indexed. That is, remove a particle. */
void erase_index(int index) {
	pointVector.erase(pointVector.begin() + index);
	vectorVector.erase(vectorVector.begin() + index);
	colorVector.erase(colorVector.begin() + index);
	speedVector.erase(speedVector.begin() + index);
	num_of_points--;

}

/* Function which clear all vectors. This is remove all the particles */
void erase_all(void) {
	pointVector.clear();
	vectorVector.clear();
	speedVector.clear();
	colorVector.clear();
	num_of_points = 0;
}

/* Function which insert a particle by initializing a new member for each vectors */
void insert_point(float x, float y) {
	pointVector.push_back(Point2D(x, y, (float)size_distr(eng)));
	vectorVector.push_back(Vec2D((float)vector_distr(eng), (float)vector_distr(eng)).normalize());
	colorVector.push_back(Color((float)color_distr(eng), (float)color_distr(eng), (float)color_distr(eng)));
	speedVector.push_back((float)speed_distr(eng));
	num_of_points++;
}

/* Fuction which move a particle in one place to another by its vector and speed */
void moveAll() {
	for (int i = 0; i < num_of_points; i++) {
		pointVector[i] = vectorVector[i].multiply(speedVector[i]).movePoint(pointVector[i]);
	}
}

/* Function which reset the particle vector towards the mouse cursor or away from mouse cursor */
void attrackOrRepulse() {
	if (buttonPress == 1) {
		for (int i = 0; i < num_of_points; i++) {
			if (mouseLocation.distanceTo(pointVector[i]) < rangeRadius) {
				vectorVector[i] = Vec2D::createVector(pointVector[i], mouseLocation).normalize();
			}
		}
	}
	if (buttonPress == 2) {
		for (int i = 0; i < num_of_points; i++) {
			if (mouseLocation.distanceTo(pointVector[i]) < rangeRadius) {
				vectorVector[i] = Vec2D::createVector(mouseLocation, pointVector[i]).normalize();
			}
		}
	}
}

/* Function for mouse action */
void mouse(int button, int state, int mX, int mY)
{
	if (state == GLUT_DOWN)
	{
		if (button == GLUT_LEFT_BUTTON) {
			buttonPress = 1;
			attrackOrRepulse();
		}
		else
		{
			buttonPress = 2;
			attrackOrRepulse();
		}
	}
}

/* Function which shows the motion to drag the particle or to repulse continously */
void motion(int mX, int mY) {
	mouseLocation.mX = mX;
	mouseLocation.mY = height - mY;
	attrackOrRepulse();
}

/* Function which update the mouse cursor location synchronously */
void passive(int mX, int mY) {
	mouseLocation.mX = mX;
	mouseLocation.mY = height - mY;
}

/* Function which let particle to bounce off the edge of sreen */
void bounce_off_edge(void) {
	for (int i = 0; i < num_of_points; i++) {
		if ((pointVector[i].mY <= 5 && vectorVector[i].mX > 0) || (pointVector[i].mX <= 5 && vectorVector[i].mY > 0)) {
			float temp = vectorVector[i].mX;
			vectorVector[i].mX = abs(vectorVector[i].mY);
			vectorVector[i].mY = abs(temp);
		}
		if ((pointVector[i].mY <= 5 && vectorVector[i].mX < 0) || (pointVector[i].mX >= (width - 5) && vectorVector[i].mY > 0)) {
			float temp = vectorVector[i].mX;
			vectorVector[i].mX = -abs(vectorVector[i].mY);
			vectorVector[i].mY = abs(temp);
		}
		if ((pointVector[i].mX <= 5 && vectorVector[i].mY < 0) || (pointVector[i].mY >= (height - 5) && vectorVector[i].mX > 0)) {
			float temp = vectorVector[i].mX;
			vectorVector[i].mX = abs(vectorVector[i].mY);
			vectorVector[i].mY = -abs(temp);
		}
		if ((pointVector[i].mX >= (width - 5) && vectorVector[i].mY < 0) || (pointVector[i].mY >= (height - 5) && vectorVector[i].mX < 0)) {
			float temp = vectorVector[i].mX;
			vectorVector[i].mX = -abs(vectorVector[i].mY);
			vectorVector[i].mY = -abs(temp);
		}
	}
}

/* Function which change the color of particle when mouse cursor approach */
void clash_color_change(void) {
	if (feature_color) {
		for (int i = 0; i < num_of_points; i++) {
			if (abs(pointVector[i].mX - mouseLocation.mX) < 2 && abs(pointVector[i].mY - mouseLocation.mY) < 2) {
				colorVector[i] = Color((float)color_distr(eng), (float)color_distr(eng), (float)color_distr(eng));
			}
		}
	}
}

/*Function which call drawPoint to draw the particles to the screen*/
void drawScene(void) {
	for (int i = 0; i < num_of_points; i++) {
		pointVector[i].drawPoint(pointVector[i].mX, pointVector[i].mY, pointVector[i].size, colorVector[i].myRed, colorVector
			[i].myGreen, colorVector[i].myBlue);
	}
}

/* Display Function */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	bounce_off_edge();
	clash_color_change();
	drawScene();
	//glutPostRedisplay();
	glutSwapBuffers();
}

/* Keyboard Function */
void kbd(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
		glClear(GL_COLOR_BUFFER_BIT);
		erase_all();
		exit(0);
		break;
	case 'a':
	case 'A':
		insert_point(mouseLocation.mX, mouseLocation.mY);
		break;
	case 'd':
	case 'D':
		if (num_of_points > 0) {
			int index_found = 0;
			float min_distance = pointVector[0].fastDistanceTo(mouseLocation);
			for (int i = 1; i < num_of_points; i++) {
				if (pointVector[i].fastDistanceTo(mouseLocation) < min_distance) {
					min_distance = pointVector[i].fastDistanceTo(mouseLocation);
					index_found = i;
				}
			}
			erase_index(index_found);
		}
		else {
			cout << "YOU HAVE ZERO ELEMENT!" << endl;
			break;
		}
	case '+':
		if (rangeRadius <= 600) {
			rangeRadius += 30;
			break;
		}
		break;
	case '-':
		if (rangeRadius >= 30) {
			rangeRadius -= 30;
			break;
		}
		break;
	case 'p':
		animate = !animate;
		break;
	case 'r':
	case 'R':
		glClear(GL_COLOR_BUFFER_BIT);
		erase_all();
		num_of_points = 8;
		generate_all();
		break;
	case 'c':
	case 'C':
		feature_color = !feature_color;
		break;
	case 'g':
	case 'G':
		feature_grow_split = !feature_grow_split;
		break;
	default:
		break;
	}
}

/* Special Function to handle the glut special input like uparrow key and downarrow key */
void special(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		if (num_of_points > 0) {
			for (int i = 0; i < num_of_points; i++) {
				speedVector[i] += 1;
			}
			break;
		}
		break;
	case GLUT_KEY_DOWN:
		if (num_of_points > 0) {
			for (int i = 0; i < num_of_points; i++) {
				if (speedVector[i] > 2) {
					speedVector[i] -= 1;
				}
			}
			break;
		}
		break;
	default:
		break;
	}
}

/* Resize Funtion */
void resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set viewing box dimensions equal to window dimensions.
	glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

	// Pass the size of the OpenGL window to globals.
	width = w;
	height = h;

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* The animation function, call the move all to make particles alive */
void FPS(int val) {
	if (animate) {
		moveAll();
	}
	glutPostRedisplay();
	glutTimerFunc(17, FPS, 0);
}

/* The animation function, to let the particle to grow to a bigger size and
finally split to smaller pariticles*/
void Growth(int val) {
	if (animate && feature_grow_split) {
		for (int i = 0; i < num_of_points; i++) {
			pointVector[i].size += 5;
			if (pointVector[i].size > max_growth) {
				pointVector[i].size = (float)size_distr(eng);
				insert_point(pointVector[i].mX, pointVector[i].mY);
			}
		}
	}
	glutPostRedisplay();
	glutTimerFunc(5000, Growth, 0);
}

/* Show menu */
void showMenu() {
	cout << "Press g or G to activate or deactivate feature grow and split." << endl;
	cout << "Press c or C to activate or deactivate feature mouse change color." << endl;
	cout << "Feature bounce_off_edge is automatically on, and cannot be turned off." << endl;
	cout << "Press p or P to pause or resume the animation." << endl;
	cout << "Press a or A to add new particle at position of mouse." << endl;
	cout << "Press d or D to delete the particle cloest to mouse cursor." << endl;
	cout << "Press r or R to clear the showing box and reset to original state." << endl;
	cout << "Press upward arrow key to globally increase the speed  of particles." << endl;
	cout << "Press downward arrow key to globally decrease the speed of particles." << endl;
	cout << "Press + or - key to increase the global attractve force or repulsive force." << endl;
	cout << "Press q or Q to clear everything and quit the program." << endl;
}

/* Initializer */
void init() {
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("dingj29_assignment2");
	glClearColor(0.0, 0.0, 0.0, 0);
	glColor3f(1.0, 1.0, 1.0);
}

/*Main*/
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	init();
	showMenu();
	generate_all();
	glutReshapeFunc(resize);
	glutKeyboardFunc(kbd);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);
	glutDisplayFunc(display);
	glutTimerFunc(17, FPS, 0);
	glutTimerFunc(5000, Growth, 0);
	glutMainLoop();
	return 0;
}
