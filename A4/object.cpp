#include "object.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
//#include <glut.h>
//#include "glm/gtc/matrix_transform.hpp"
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

#include <string>
#include <fstream>
#include <iostream>


#define OUT_BOXED_MULTIPLIER 1.1f
#define BOX_MULTIPLIER 0.5f

#define CUBE_SIZE 0.9f
#define SPHERE_SIZE 0.47f
#define CONE_BASE 0.45f
#define CONE_HEIGHT 0.9f
#define TORUS_INNER 0.25f
#define TORUS_OUTER 0.45f
#define TEAPOT_SIZE 0.45f
#define TETRAHEDRON_SIZE 0.7f
GLfloat cubeVertices[8][3] = {
        { -1, 1, -1 },
        { -1, -1, -1 },
        { 1, -1, -1 },
        { 1, 1, -1 },


        { -1, 1, 1 },
        { -1, -1, 1 },
        { 1, -1, 1 },
        { 1, 1, 1 },
};

unsigned int cubeTriangles[12][3] = {
        // Back face
        { 0, 2, 1 },
        { 0, 3, 2 },

        // Left face
        { 0, 1, 4 },
        { 1, 5, 4 },

        // Front face
        { 4, 5, 6 },
        { 4, 6, 7 },

        // Right face
        { 6, 3, 7 },
        { 2, 3, 6 },

        // Top face
        { 0, 4, 3 },
        { 3, 4, 7 },

        // Bottom face
        { 1, 2, 5 },
        { 2, 6, 5 }
};

Object::Object(Material mat, Shape shape) {
    this->setPosition(1.0f, 1.0f, 1.0f);
    this->setOrientation(0.0f, 0.0f, 0.0f);
    this->setScale(1.0f, 1.0f, 1.0f);
    this->obj_material = mat;
    this->obj_shape = shape;
    this->is_selected = false;
    this->cat = model();
}

void Object::setPosition(float x, float y, float z)
{
	this->position[0] = x;
	this->position[1] = y;
	this->position[2] = z;
}

void Object::setOrientation(float x, float y, float z)
{
	this->orientation[0] = x;
	this->orientation[1] = y;
	this->orientation[2] = z;
}

void Object::setScale(float x, float y, float z)
{
	this->scale[0] = x;
	this->scale[1] = y;
	this->scale[2] = z;
}

static void
drawBox(GLfloat size, GLenum type)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;

  for (i = 5; i >= 0; i--) {
    glBegin(type);
    glNormal3fv(&n[i][0]);
    glTexCoord2f(1,1);
    glVertex3fv(&v[faces[i][0]][0]);
    glTexCoord2f(0,1);
    glVertex3fv(&v[faces[i][1]][0]);
    glTexCoord2f(1,0);
    glVertex3fv(&v[faces[i][2]][0]);
    glTexCoord2f(0,0);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}

void APIENTRY
glutSolidCubeMod(GLdouble size)
{
  drawBox(size, GL_QUADS);
}



void Object::setAmb(float x, float y, float z, float a) {
	float mat_ambient[4] = { x, y, z, a };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
   
}

void Object::setDiff(float x, float y, float z, float a) {
	float mat_diffuse[4] = { x, y, z, a };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_diffuse);
    
}

void Object::setSpec(float x, float y, float z, float a) {
	float mat_specular[4] = { x, y, z, a };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_specular);
   
}

void Object::setShin(float s)
{
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, s);
}

void Object::apply_obj_mat() {
	switch (this->obj_material)
	{
	case EMERALD:
		setAmb(0.10, 0.19, 0.17, 0.80);
		setDiff(0.07568f, 0.61424f, 0.07568f, 0.55f);
		setSpec(0.633f, 0.727811f, 0.633f, 0.55f);
		setShin(76.8f);
		break;
	case BRASS:
		setAmb(0.329412f, 0.223529f, 0.027451f, 1.0f);
		setDiff(0.780392f, 0.568627f, 0.113725f, 1.0f);
		setSpec(0.992157f, 0.941176f, 0.807843f, 1.0f);
		setShin(27.8974f);
		break;
	case BRONZE:
		setAmb(0.25f, 0.148f, 0.06475f, 1.0f);
		setDiff(0.4f, 0.2368f, 0.1036f, 1.0f);
		setSpec(0.774597f, 0.458561f, 0.200621f, 1.0f);
		setShin(76.8f);
		break;
	case GOLD:
		setAmb(0.24725f, 0.1995f, 0.0745f, 1.0f);
		setDiff(0.75164f, 0.60648f, 0.22648f, 1.0f);
		setSpec(0.628281f, 0.555802f, 0.366065f, 1.0f);
		setShin(51.2f);
		break;
	case COPPER:
		setAmb(0.2295f, 0.08825f, 0.0275f, 1.0f);
		setDiff(0.5508f, 0.2118f, 0.066f, 1.0f);
		setSpec(0.580594f, 0.223257f, 0.0695701f, 1.0f);
		setShin(51.2f);
		break;
	case CYAN_PLASTIC:
		setAmb(0.0f, 0.1f, 0.06f, 1.0f);
		setDiff(0.0f, 0.50980392f, 0.50980392f, 1.0f);
		setSpec(0.50196078f, 0.50196078f, 0.50196078f, 1.0f);
		setShin(32.0f);
		break;
	default:
		break;
	}
}

void Object::render_obj(bool selected) {
	glPushMatrix();

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDisable(GL_LIGHTING);
    //only draw when selected
    if (selected) {
        draw_box();
    }
    //draw_box();
    glEnable(GL_LIGHTING);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	// Perform transformation before rendering
    glTranslatef(this->position[0], this->position[1], this->position[2]);
    glRotatef(this->orientation[1], 0, 1, 0);
    glRotatef(this->orientation[0], 1, 0, 0);
    glRotatef(this->orientation[2], 0, 0, 1);
	glScalef(this->scale[0], this->scale[1], this->scale[2]);

	glPushMatrix();
	switch (this->obj_shape)
	{
	case CUBE:
        	apply_obj_mat();
        	//glTranslatef(1, 1, 0);
		glutSolidCubeMod(CUBE_SIZE);
		break;
	case SPHERE:
        	apply_obj_mat();
		glutSolidSphere(SPHERE_SIZE, 100, 100);
		break;
	case CONE:
        	apply_obj_mat();
		glRotatef(-90, 1, 0, 0);
		glTranslatef(0, 0, -0.5F);
		glutSolidCone(CONE_BASE, CONE_HEIGHT, 100, 100);
		break;
	case TORUS:
        	apply_obj_mat();
		glRotatef(-90, 1, 0, 0);
		glutSolidTorus(0.25, 0.45, 100, 100);
		break;
	case TEAPOT:
        	apply_obj_mat();
		glFrontFace(GL_CW);
		glutSolidTeapot(TEAPOT_SIZE);
		glFrontFace(GL_CCW);
		break;
	case TETRAHEDRON:
        	apply_obj_mat();
		glRotatef(90, 0, 0, 1);
		glTranslatef(-0.25, 0, 0);
		glScalef(TETRAHEDRON_SIZE, TETRAHEDRON_SIZE, TETRAHEDRON_SIZE);
		glutSolidTetrahedron();
		break;
    case CAT:
        apply_obj_mat();
        glPushMatrix();
        glTranslatef(0, -0.8, 0);
        glPushMatrix();
        glRotated(270,1,0,0);
        glRotated(90,0,0,1);
        glScalef(0.05f,0.05f,0.05f);
//        glColor3fv(utli::get_color(this->color));
        glCallList(this->cat.list);
        glPopMatrix();
        glPopMatrix();
        break;
	}
	glPopMatrix();
	glPopMatrix();
}

void Object::update_vertices() {

    switch (this->obj_shape)//apply translation and scaling
    {
        case CUBE:
        case SPHERE:
        case CONE:
        case TETRAHEDRON:
            for (int i = 0; i < 8; i++) {
                this->vertices[i][0] = (cubeVertices[i][0] * BOX_MULTIPLIER * this->scale[0]);
                this->vertices[i][1] = (cubeVertices[i][1] * BOX_MULTIPLIER * this->scale[1]);
                this->vertices[i][2] = (cubeVertices[i][2] * BOX_MULTIPLIER * this->scale[2]);
            }
            break;
        case TORUS:
            for (int i = 0; i < 8; i++) {
                this->vertices[i][0] = (cubeVertices[i][0] * BOX_MULTIPLIER * 1.5f * this->scale[0]);
                this->vertices[i][1] = (cubeVertices[i][1] * BOX_MULTIPLIER * 0.9f * this->scale[1]);
                this->vertices[i][2] = (cubeVertices[i][2] * BOX_MULTIPLIER * 1.5f * this->scale[2]);
            }
            break;
        case TEAPOT:
            for (int i = 0; i < 8; i++) {
                this->vertices[i][0] = (cubeVertices[i][0] * BOX_MULTIPLIER * 1.5f * this->scale[0]);
                this->vertices[i][1] = (cubeVertices[i][1] * BOX_MULTIPLIER * 0.8f * this->scale[1]);
                this->vertices[i][2] = (cubeVertices[i][2] * BOX_MULTIPLIER * 0.9f * this->scale[2]);
            }
            break;
        case CAT:
            for (int i = 0; i < 8; i++) {
                this->vertices[i][0] = (cubeVertices[i][0] * BOX_MULTIPLIER * 1.6f * this->scale[0]);
                this->vertices[i][1] = (cubeVertices[i][1] * BOX_MULTIPLIER * 2.0f * this->scale[1]);
                this->vertices[i][2] = (cubeVertices[i][2] * BOX_MULTIPLIER * 0.9f * this->scale[2]);
            }
            break;
        default:
            break;

    }

    for (int i = 0; i < 8; i++) {
        glm::vec3 temp = glm::make_vec3(this->vertices[i]);
        temp = glm::rotateZ(temp, glm::radians(this->orientation[2]));
        temp = glm::rotateX(temp, glm::radians(this->orientation[0]));
        temp = glm::rotateY(temp, glm::radians(this->orientation[1]));
        this->vertices[i][0] = (temp.x + this->position[0]);
        this->vertices[i][1] = (temp.y + this->position[1]);
        this->vertices[i][2] = (temp.z + this->position[2]);
    }
}
void Object::draw_box() {
    this->update_vertices();
    glFrontFace(GL_CCW);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 3; j++) {
            glVertex3fv(this->vertices[cubeTriangles[i][j]]);
        }

    }
    glEnd();
//    glFrontFace(GL_CW);
}