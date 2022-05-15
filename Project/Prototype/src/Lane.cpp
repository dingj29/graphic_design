//
// Created by WILL on 2021/11/15.
//
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/freeglut.h>
#include <iostream>

#endif

#include "Lane.h"
#include "utli.h"

Lane::Lane(float x, float y, float z, int color) : Object(x, y, z, color) {
    this->type = LANE;
}

void Lane::render(float player_z) {
    float s_pos;
    float e_pos;
    for (auto l:this->l_color){

        if (!(l.end_pos < player_z - 100 || l.start_pos > player_z + 300)){
            if (l.start_pos < player_z - 100) {
                s_pos = player_z - 100;
            }else{
                s_pos = l.start_pos;
            }
            if (l.end_pos > player_z + 300) {
                e_pos = player_z + 300;
            }else{
                e_pos = l.end_pos;
            }
            glBegin(GL_QUADS);
            glColor3fv(utli::get_color(l.color));
            glVertex3f(this->positionX, 0, e_pos);
            glVertex3f(this->positionX, 0, s_pos);
            glVertex3f(this->positionX - (float) this->width, 0, s_pos);
            glVertex3f(this->positionX - (float) this->width, 0, e_pos);
            glEnd();

        }
    }
//    glBegin(GL_QUADS);
//    glColor3f(0.0f,1.0f,0.0f);
//    glVertex3f(this->positionX, 0, player_z + 300);
//    glVertex3f(this->positionX, 0, player_z - 100);
//    glVertex3f(this->positionX - (float) this->width, 0, player_z - 100);
//    glVertex3f(this->positionX - (float) this->width, 0, player_z + 300);
//    glEnd();

    for (auto o:this->obs) {
        if (o.positionZ < player_z + 300 && o.positionZ > player_z - 100) {
            o.render_prototype(this->width);
        }
    }
}

void Lane::init_Obstacle(int amount, int total_length) {
    float interval = (float ) total_length / (float ) amount;
    for (int i = 0; i < amount; ++i) {
        float pos_z = utli::random_float(i*interval, (i + 1)*interval);
        Obstacle temp = Obstacle(this->positionX - ((float) this->width / 2), 0, pos_z);// todo static width
        temp.set_color(utli::random_int(1,3));
        this->obs.push_back(temp);
    }
}

void Lane::set_width(int input_width) {
    this->width = input_width;
}

void Lane::lane_init(float min_length, float max_length, float total_length) {
    float current_pos = 0;
    float random_length;
    while (current_pos < total_length){
        random_length = utli::random_float(min_length, max_length);
        if (current_pos + random_length > total_length){
            random_length = total_length - current_pos;
        }
        lane_color temp{};
        temp.color = utli::random_int(1,3);
        temp.start_pos = current_pos;
        current_pos = current_pos + random_length;
        temp.end_pos = current_pos;
        this->l_color.push_back(temp);
    }
}

void Lane::init(int input_width, int amount, float min_length, float max_length, float total_length) {
    this->set_width(input_width);
    this->init_Obstacle(amount,(int) total_length);
    this->lane_init(min_length, max_length, total_length);
}

bool Lane::detect_collision(float position_y, float position_z) {
    for (auto o : this->obs) {
        if (o.positionZ - 3 < position_z && position_z < o.positionZ + 3 && position_y < o.positionY + 3) {
            return true;
        }
    }
    return false;
}
