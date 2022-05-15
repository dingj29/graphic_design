#include "particle.h"

Particle::Particle(double* pos, double* dir, int spd, double* ang, int size, double* rgb, int material, int age, int shape) {
    for (int i = 0; i <= 2; i++) {
        this->pos[i] = pos[i];
        this->dir[i] = dir[i];
        this->ang[i] = ang[i];
        this->rgb[i] = rgb[i];
    }
    this->spd = spd;
    this->size = size;
    this->shape = shape;
    this->material = material; //mat = 0, rubber particles: hitting floor will jump, 1 anti-gravity, 2 superglue ball: hit the floor will stop
    this->age = age;
}
// [2] is for up or down
void Particle::move() {
    for (int i = 0; i <= 2; i++) {
        this->pos[i] = this->pos[i] + this->spd * this->dir[i];
    }
    if (this->pos[2] <= 0) {
        this->pos[2] = 0;
        switch (this->material) {
            case 0:
            case 1:
                this->dir[2] = -this->dir[2];
                break;
            case 2:
                this->spd = 0;
                this->dir[2] = 0;
                break;
        }

    }
}

void Particle::move_with_fract(double fraction) {
    for (int i = 0; i <= 2; i++) {
        this->pos[i] = this->pos[i] + this->spd * this->dir[i];
    }
    if (this->pos[2] <= 0) {
        this->pos[2] = 0;
        switch (this->material) {
            case 0:
            case 1:
                this->dir[2] = -this->dir[2];
                break;
            case 2:
                this->spd = 0;
                this->dir[2] = 0;
                break;
        }
        this->spd = this->spd * (1 - fraction);
    }
}

// let the particle to fall by modifying the y component
void Particle::apply_grav(float grav) {
    if (this->material == 1) {
        return;
    }
    this->dir[2] = this->dir[2] - grav;
}

bool Particle::check_delet() {
    this->age = this->age - 1;
    if (this->age < 0) {
        return true;
    }
    return false;
}
