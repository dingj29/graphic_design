#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "object.h"
#include "list"
#include "mathlib.h"
#include "ioHandler.h"
#include "model.h"
#include "PPM.h"
//#include <glut.h>

// OpenGL and GLUT imports
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#define cam_x 20
#define cam_y 20
#define deg_to_rad 0.0174532925f
using namespace std;

const float axisLength = 100;

Material material = COPPER;
int horizontalView = 45;
int verticalView = 45;

int texture_select = 0;

const float initialZoom = 50;

/* If ray picking and select the object, set select_obj to true */
bool free_cam = false;
bool select_obj = false;
static int select_index = -1;

float cameraPos[] = {(sin(horizontalView * deg_to_rad)* cam_x) , (cos(horizontalView * deg_to_rad)* cam_x), (sin(verticalView * deg_to_rad)* cam_y) };

float lightPos1[] = { 5, 8, 1, 1 };
float lightPos2[] = { 1, 8, 5, 1 };
float lightAmb[] = { 0.35, 0.35, 0.35, 1 };
float lightDif[] = { 0.35, 0.35, 0.35, 1 };
float lightSpc[] = { 0.35, 0.35, 0.35, 1 };

int win_width = 600;
int win_height = 600;

enum Direction { LEFT, RIGHT, DOWN, UP, BACK, FRONT };

// Define the list of objects
vector<Object> objects;

glm::vec3 look_at;
glm::vec3 free_pos = {20, 20, 20};

struct Image {
    int mWidth;
    int mHeight;
    GLubyte * mImage;

    void load(char * filename) {
        mImage = LoadPPM(filename, &mWidth, &mHeight);
    }

    void draw(unsigned int x, unsigned int y) {
        glRasterPos2i(x + mWidth, y);
        glPixelZoom(-1, 1);
        glDrawPixels(mWidth, mHeight, GL_RGB, GL_UNSIGNED_BYTE, mImage);
    }

    void texture() {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mImage);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
};

Image marbleTexture;
Image carpetTexture;
Image rockTexture;

static void baseMaterialColor(float r, float g, float b)
{
	float amb[4] = { r, g, b, 1 };
	float dif[4] = { r, g, b, 1 };
	float spc[4] = { r, g, b, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spc);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1);
}



void render_walls()
{
	baseMaterialColor(0.6, 0.6, 0.4);
	glNormal3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, axisLength, 0);
	glVertex3f(0, axisLength, axisLength);
	glVertex3f(0, 0, axisLength);
	glEnd();
	
	baseMaterialColor(0.5, 0.5, 0.3);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(axisLength, 0, 0);
	glVertex3f(axisLength, axisLength, 0);
	glVertex3f(0, axisLength, 0);
	glEnd();
	
	baseMaterialColor(0.5, 0.5, 0.4);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, axisLength);
	glVertex3f(axisLength, 0, axisLength);
	glVertex3f(axisLength, 0, 0);
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
    cameraPos[0] = sin(horizontalView * deg_to_rad)* cam_x;
    cameraPos[1] = sin(verticalView * deg_to_rad)* cam_y;
    cameraPos[2] = cos(horizontalView * deg_to_rad)* cam_x;

	// Position camera looking at origin
    if (free_cam) {
        gluLookAt(
                free_pos.x, free_pos.y, free_pos.z,
                look_at.x, look_at.y, look_at.z,
                0, 1, 0
        );
    }else{
        gluLookAt(
                cameraPos[0], cameraPos[1], cameraPos[2],
                0, 0, 0,
                0, 1, 0
        );
    }

	glPushMatrix();
        
	render_walls();

	// Set light for first light source
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpc);

	// Set light for second light source
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDif);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpc);

	// Depict first light source as tiny bright red sphere
	baseMaterialColor(1, 0.75, 0.75);
	glPushMatrix();
	glTranslatef(lightPos1[0], lightPos1[1], lightPos1[2]);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	// Depict second light source as tiny bright blue sphere
	baseMaterialColor(0.75, 0.75, 1);
	glPushMatrix();
	glTranslatef(lightPos2[0], lightPos2[1], lightPos2[2]);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();

	// Iterate through linear scene graph and draw objects
	for (auto o : objects) {
		glEnable(GL_TEXTURE_2D);
        if (texture_select == 0){
			marbleTexture.texture();
        }else if (texture_select == 1){
            carpetTexture.texture();
        } else {
            rockTexture.texture();
        }
		o.render_obj(o.is_selected);
		glDisable(GL_TEXTURE_2D);
	}
	glPopMatrix();
	glFlush();
	
	// Redraw display area continuously
	glutPostRedisplay();
}

void reshape(int w, int h)
{
    	win_width = w;
    	win_height = w;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, axisLength * 2);
	glMatrixMode(GL_MODELVIEW);
}


void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
        case '1':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                objects.push_back(Object(material, CUBE));
            }
            else {
                material = COPPER;
            }
            break;
        case '2':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                objects.push_back(Object(material, SPHERE));
            }
            else {
                material = BRASS;
            }
            break;
        case '3':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                objects.push_back(Object(material, CONE));
            }
            else {
                material = GOLD;
            }
            break;
        case '4':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                objects.push_back(Object(material, TORUS));
            }
            else {
                material = BRONZE;
            }
            break;
        case '5':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                objects.push_back(Object(material, TEAPOT));
            }
            else {
                material = CYAN_PLASTIC;
            }
            break;
        case '6':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                objects.push_back(Object(material, TETRAHEDRON));
            }
            else {
                material = EMERALD;
            }
            break;
        case '7':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                objects.push_back(Object(material, CAT));
            }
        case 'm':
        case 'M':
            if (select_index == -1) {
                break;
            }
            else {
                for (int i = 0; (unsigned)i < objects.size(); i++) {
                    if (select_index == i) {
                        objects[select_index].obj_material = material;
                    }
                }
                break;
            }
        case 'r':
        case 'R':
            glClear(GL_COLOR_BUFFER_BIT);
            objects.clear();
            break;
        case 'q':
        case 'Q':
            glClear(GL_COLOR_BUFFER_BIT);
            objects.clear();
            exit(0);
            break;
        case 'Y':
        case 'y':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                if (select_index != -1) {
                    objects[select_index].orientation[1] += 2;
                }
            }
            break;
        case 'X':
        case 'x':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                if (select_index != -1) {
                    objects[select_index].orientation[0] += 2;
                }
            }
            break;
        case 'Z':
        case 'z':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
                if (select_index != -1) {
                    objects[select_index].orientation[2] += 2;
                }
            }
            break;
        case 's':
        case 'S':
            if (glutGetModifiers() == GLUT_ACTIVE_ALT){
                ioHandler::saveGame(objects);
                printf("Game Saved \n");
            }else if(glutGetModifiers() == GLUT_ACTIVE_SHIFT){
                vector<Object> loaded = {};
                loaded = ioHandler::loadGame();
                objects.swap(loaded);
                printf("Game Loaded \n");
            } else {
                free_pos.x = free_pos.x - 1;
            }
            break;
        case 'c':
        case 'C':
            free_cam = !free_cam;
            break;
        case 'w':
        case 'W':
            free_pos.x = free_pos.x + 1;
            break;
        case 'a':
        case 'A':
            free_pos.z = free_pos.z + 1;
            break;
        case 'd':
        case 'D':
            free_pos.z = free_pos.z - 1;
            break;
        case 'n':
        case 'N':
            free_pos.y = free_pos.y + 1;
            break;
        case 'b':
        case 'B':
            free_pos.y = free_pos.y - 1;
            break;
        case '8':
            texture_select = 1;
            break;
        case '9':
            texture_select = 2;
            break;
        case '0':
            texture_select = 0;
            break;
        default:
            break;
	}
}

void specialkbd(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			if (select_index != -1) {
				if (objects[select_index].position[1] < 12) {
					objects[select_index].position[1] += 1;
				}
			}
			break;
		}
		if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
			if (select_index != -1 && objects[select_index].scale[1] <= 6) {
				objects[select_index].scale[1] += 1;
				objects[select_index].scale[2] += 1;
				objects[select_index].scale[0] += 1;
			}
			break;
		}
		else {
			verticalView = std::min(87, verticalView + 3);
			break;
		}
	case GLUT_KEY_DOWN:
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			if (select_index != -1) {
				if (objects[select_index].position[1] > 0) {
					objects[select_index].position[1] -= 1;
				}
			}
                        break;
		}
		if (glutGetModifiers() == GLUT_ACTIVE_ALT) {
			if (select_index != -1 && objects[select_index].scale[1] > 1) {
				objects[select_index].scale[1] -= 1;
				objects[select_index].scale[0] -= 1;
				objects[select_index].scale[2] -= 1;
			}
			break;
		}
		else {
			verticalView = std::max(3, verticalView - 3);
                        break;
		}
	case GLUT_KEY_LEFT:
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			if (select_index != -1) {
				if (objects[select_index].position[0] > 0) {
					objects[select_index].position[0] -= 1;
				}
			}
			break;
		}
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			if (select_index != -1) {
				if (objects[select_index].position[2] < 12) {
					objects[select_index].position[2] += 1;
				}
			}
			break;
		}
		else {
			if (horizontalView > 5) {
				horizontalView = (horizontalView - 3) % 360;
			}
			break;
		}
	case GLUT_KEY_RIGHT:
		if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
			if (select_index != -1) {
				if (objects[select_index].position[0] < 12) {
					objects[select_index].position[0] += 1;
				}
			}
			break;
		}
		if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {
			if (select_index != -1) {
				if (objects[select_index].position[2] > 0) {
					objects[select_index].position[2] -= 1;
				}
			}
			break;
		}
		else {
			if (horizontalView < 85) {
				horizontalView = (horizontalView + 3) % 360;
			}
			break;
		}
	default:
		break;
	}
	glutPostRedisplay();
}

void mouse(int b, int s, int mouse_x, int mouse_y){
    if (objects.size() == 0){
        return;
    }
	if (s == GLUT_DOWN) {
        if (b == GLUT_RIGHT_BUTTON && select_index != -1) {
            objects.erase(objects.begin() + select_index);
            select_index = -1;
        } else {
            glm::vec3 ray = mathlib::get_mouse_ray(mouse_x, mouse_y, win_width, win_height);
            //    printf("|%f,%f,%f|", ray.x, ray.y, ray.z);
//            raypos = ray;
            select_index = -1;
            float min_len = 999999.0f;
            select_obj = false;
            for (int i = 0; (unsigned)i < objects.size(); i++) {
                objects[i].update_vertices();
                float dis = mathlib::ray_box(objects[i].vertices, ray, glm::make_vec3(cameraPos), glm::make_vec3(objects[i].position));
                if (dis != -1.0f) {
                    select_obj = true;
                    if (b == GLUT_LEFT_BUTTON) {
                        if (dis < min_len){
                            select_index = i;
                            min_len = dis;
                        }
                    }
                }
                objects[i].is_selected = false;
            }
            objects[select_index].is_selected = true;
        }
	}
}


void passive_mouse(int x, int y){
	glm::vec3 ray = mathlib::get_mouse_ray(x, y, win_width, win_height);
	ray = ray * 50.0f;
	look_at = ray;
}

void init_obj(){
	objects.push_back(Object(material, CUBE));
	objects[0].setPosition(2.0f,1.0f,3.0f);
	objects.push_back(Object(material, SPHERE));
	objects[1].setPosition(6.0f,8.0f,2.0f);
	objects.push_back(Object(material, TEAPOT));
	objects[2].setPosition(3.0f,3.0f,6.0f);
}

void showMenu() {
	cout << "Press mouse left button to select object(shown in green box)" <<endl;
        cout << "Press mouse right button to delete selected object" <<endl;
	cout << "Press q,Q to quit." <<endl;
	cout << "Press r,R to clear the scene." <<endl;
	cout << "Press Alt + S to save current scene into a file, make sure you enter the file name" <<endl;
	cout << "Press Shift + S to loaded saved file, make sure you enter the file to load" <<endl;
	cout << "Press Shift + ArrowUp to translate object up" <<endl;
	cout << "Press Shift + ArrowDown to translate object down" <<endl;
	cout << "Press Shift + ArrowLeft to translate object left(along x-axis)" <<endl;
	cout << "Press Shift + ArrowRight to translate object right(along x-axis)" <<endl;
	cout << "Press Ctrl + ArrowLeft to translate object out of the screen(along z-axis)" <<endl;
	cout << "Press Ctrl + ArrowRight to translate object in to the screen(along z-axis)" <<endl;
	cout << "Press Alt + y to rotate the object along y axis" <<endl;
	cout << "Press Alt + x to rotate the object along x axis" <<endl;
	cout << "Press Alt + z  | rotate the object along z axis" <<endl;
	cout << "Press Alt + ArrowUp to apply symmetric scaling to object (getting bigger)" <<endl;
	cout << "Press Alt + ArrowDown  | apply symmetric scaling to object (getting smaller)" <<endl;
	cout << "Press ArrowUp to rotate the scene up" <<endl;
	cout << "Press ArrowDown to rotate the scene down" <<endl;
	cout << "Press ArrowLeft to rotate the scene left" <<endl;
	cout << "Press ArrowRight to rotate the scene right" <<endl;
	cout << "Press 1 - 6 to apply material 1-6 to the selected object" <<endl;
	cout << "Press 8 to apply carpet texture to objects" <<endl;
	cout << "Press 9 to apply rock texture to objects" <<endl;
	cout << "Press 0 to apply marble texture to objects (default is marble)" <<endl;
	cout << "Press m, M to apply material to the selected object" <<endl;
	cout << "Press Alt + 1 to generate a cube at world origin" <<endl;
	cout << "Press Alt + 2 to generate a sphere at world origin" <<endl;
	cout << "Press Alt + 3 to generate a cone at world origin" <<endl;
	cout << "Press Alt + 4 to generate a torus at world origin" <<endl;
	cout << "Press Alt + 5 to generate a teapot at world origin" <<endl;
	cout << "Press Alt + 6 to generate a tetra at world origin" <<endl;
	cout << "Press Alt + 7 to generate a cat at world origin" <<endl;
	cout << "Press c, C to activate or deactivate the camera control mode" <<endl;
	cout << "Press w,s,a,d to shift view near, far, left, right respectively if camera control mode is activate (mouse to control dir)"<<endl;
	cout << "Press n,b to shift view up and down respectively if camera control mode is activate (mouse to control dir)"<<endl;
}

int main(int argc, char** argv)
{
	marbleTexture.load((char *)"marble.ppm");
	carpetTexture.load((char *)"carpet.ppm");
	rockTexture.load((char *)"rock.ppm");
        // init_obj();
	// GLUT initialization
	showMenu();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

	// Set dimensions and position of window
	glutInitWindowSize(win_width, win_height);
	glutInitWindowPosition(
		(glutGet(GLUT_SCREEN_WIDTH) - 500) / 2,
		(glutGet(GLUT_SCREEN_HEIGHT) - 500) / 2);

	// Create window for displaying modeler
	glutCreateWindow("3GC3 - Assignment 4");

	// I/O function bindings
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);
        glutSpecialFunc(specialkbd);
        glutPassiveMotionFunc(passive_mouse);

	// Enable lighting
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	// Enable backface culling
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Main program loop
	glutMainLoop();

	// Exit normally
	return 0;
}
