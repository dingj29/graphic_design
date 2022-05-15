//
// Created by WILL on 2021/11/15.
//
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/freeglut.h>
#endif

#include "Obstacle.h"
#include "utli.h"
Obstacle::Obstacle(float x, float y, float z, int color) : Object(x, y, z, color)
{
    this->type = OBSTACLE;
}

// Obstacle renderer (parent renderer with parameters)
//void Obstacle::render()
//{
//    // Basic for now, to be replaced by obj loader
//    Object::render(0.5, 0.5, 1, 0.75);
//}

void Obstacle::render_prototype(int width) {
    glPushMatrix();
    glColor3fv(utli::get_color(this->color));
    glTranslated(this->positionX,(float ) width / 2,this->positionZ);
    glutWireCube(width);
    glPopMatrix();
}

void Obstacle::set_color(int color) {
    this->color = color;
}

