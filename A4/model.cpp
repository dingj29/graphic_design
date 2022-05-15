//
// Created by WILL on 2021/12/6.
//
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
#include <vector>
#include "model.h"
#include <fstream>

void model::load_object() {
    std::string line;
    std::vector<std::string> lines;
    std::ifstream in;
    in.open("./res/Cat.obj");
    while (in.peek() != EOF) {
        std::getline(in, line);
        lines.push_back(line);
    }
    in.close();

    float a, b, c;
    for (std::string &line : lines) {
        if (line[0] == 'v') {
            if (line[1] == ' ') {
                sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);
                this->veI.push_back(new float[3]{a, b, c});
            } else if (line[1] == 't') {
                sscanf(line.c_str(), "vt %f %f", &a, &b);
                this->uvI.push_back(new float[2]{a, b});
            } else {
                sscanf(line.c_str(), "vn %f %f %f", &a, &b, &c);
                this->noI.push_back(new float[3]{a, b, c});
            }
        } else if (line[0] == 'f') {
            int v0, v1, v2, t0, t1, t2, n;
            sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
            int *v = new int[3]{v0 - 1, v1 - 1, v2 - 1};
            this->faces.push_back(Face(3, v, nullptr, n - 1));
        }
    }
    this->list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    for (Face &face : this->faces) {
        if (face.normal != -1)
            glNormal3fv(this->noI[face.normal]);
        else
            glDisable(GL_LIGHTING);
        glBegin(GL_POLYGON);
        for (int i = 0; i < face.edge; i++)
            glVertex3fv(this->veI[face.vertices[i]]);
        glEnd();
        if (face.normal == -1)
            glEnable(GL_LIGHTING);
    }
    glEndList();
    for (float *f : this->veI)
        delete f;
    this->veI.clear();
    for (float *f : this->uvI)
        delete f;
    this->uvI.clear();
    for (float *f : this->noI)
        delete f;
    this->noI.clear();
    faces.clear();
}

model::model() {
    this->load_object();
}
