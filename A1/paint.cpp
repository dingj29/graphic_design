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
#include <stdlib.h>
#include <vector>


using namespace std;

// Point2D class
// 3 fields for colour, 2 for coordinates and 1 for brush size
class Point2D
{
public:
	Point2D(GLfloat x, GLfloat y, float size, float redf, float greenf, float bluef)
	{
		xVal = x; yVal = y;
		mySize = size;
		myRed = redf;
		myGreen = greenf;
		myBlue = bluef;
	}
	void paintPoint(void);
	GLfloat xVal, yVal;
	float mySize;
	float myRed;
	float myBlue;
	float myGreen;
};

/*initially set the colour to white; 
set original brush size to 8; 
create a vector to record the movement of mouse cursor, the vector of points*/ 
float red = 1.0, green = 1.0, blue = 1.0;
float pointSize = 8.0;
vector<Point2D> pointVector;

// To draw a single point on the canvas
void Point2D::paintPoint(void)
{
	glColor3f(myRed, myGreen, myBlue);
	glPointSize(mySize);
	glBegin(GL_POINTS);
	glVertex2f(xVal, yVal);
	glEnd();

}

// the drawing function, iterate through the vector and call paintPoint()
void paintScene(void)
{
	glColor3f(red, green, blue);
	glClear(GL_COLOR_BUFFER_BIT);
	for (Point2D point : pointVector) {
		point.paintPoint();
	}
	glFlush();
}

//Setup the 2D viewing of the canvas(colour mode, model - view, projection etc.)
void myInti(void)
{
	glColor3f(red, green, blue);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
}

// simply display function
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


// mouse clicking callback 
void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		pointVector.push_back(Point2D(x, 600 - y, pointSize, red, green, blue));

	glutPostRedisplay();
}

// moving mouse callback 
void mouseMotion(int x, int y)
{
	pointVector.push_back(Point2D(x, 600 - y, pointSize, red, green, blue));
	glutPostRedisplay();
}

// keyboard interaction with user
void keyListener(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'Q':
		exit(0);
		break;
	case 'r':
		glClear(GL_COLOR_BUFFER_BIT);
		pointVector.clear();
		glFlush();
		break;
	case 'R':
		glClear(GL_COLOR_BUFFER_BIT);
		pointVector.clear();
		glFlush();
		break;
	case '+':
		if (pointSize < 28) {
			pointSize += 5;
		}
		cout << "Current brush size: "<< pointSize << endl;
		break;
	case '-':
		if (pointSize > 3) {
			pointSize-=5;
		}
		cout << "Current brush size: "<< pointSize << endl;
		break;
	case '1':
		red = 1.0;
		green = 0.0;
		blue = 0.0;
		break;
	case '2':
		red = 0.0;
		green = 0.0;
		blue = 1.0;
		break;
	case '3':
		red = 0.0;
		green = 1.0;
		blue = 0.0;
		break;
	case '4':
		red = 1.0;
		green = 1.0;
		blue = 0.0;
		break;
	case '5':
		red = 0.0;
		green = 1.0;
		blue = 1.0;
		break;
	case '6':
		red = 1.0;
		green = 0.0;
		blue = 1.0;
		break;
	case 'e':
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		cout << "Eraser mode: " << pointSize << endl;
		break;
	case 'E':
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		cout << "Eraser mode: " << pointSize << endl;
		break;
	default:
		break;
	}
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(200, 50);
	glutCreateWindow("dingj29_A1_Part2");
	glutDisplayFunc(display);
	glutDisplayFunc(paintScene);
	glutKeyboardFunc(keyListener);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	myInti();
	glutMainLoop();
	return 0;
}
