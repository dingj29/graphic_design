#ifndef INC_3GC3_A4_MATHLIB_H
#define INC_3GC3_A4_MATHLIB_H
#include <glm/glm.hpp>

class mathlib {
public:
    static glm::vec3 get_mouse_ray(int mouse_x, int mouse_y, int win_width, int win_height);
    //static glm::vec3 ray_box(float vertices[8][3], glm::vec3 ray, glm::vec3 origin, glm::vec3 pos);
    static float ray_box(float vertices[8][3], glm::vec3 ray, glm::vec3 origin, glm::vec3 pos);

private:
    mathlib();
};


#endif //INC_3GC3_A4_MATHLIB_H
