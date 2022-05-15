#include "mathlib.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtx/intersect.hpp>
#include <math.h>
#include <cstdio>
#include <vector>
#include <algorithm>
//#include <glut.h>

#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


#define Detect_Epsilon 0.0001f
using namespace glm;

unsigned int cubeSufaceTriangles[6][4] = {
        // Back face
        { 0, 2, 3, 1 },
        // Left face
        { 0, 1, 4 ,5 },

        // Front face
        { 4, 5 ,7 ,6 },

        // Right face
        { 6, 3, 7, 2 },

        // Top face
        { 0, 4, 3, 7 },

        // Bottom face
        { 1, 2, 5, 6 },
};


vec3 mathlib::get_mouse_ray(int mouse_x, int mouse_y, int win_width, int win_height) {
    float proj_mat_float[16];
    float view_mat_float[16];
    glGetFloatv(GL_PROJECTION_MATRIX, proj_mat_float);
    glGetFloatv(GL_MODELVIEW_MATRIX, view_mat_float);
    mat4 proj_mat = make_mat4(proj_mat_float);
    mat4 view_mat = make_mat4(view_mat_float);
    float x = ( 2.0f * mouse_x ) / win_width - 1.0f;
    float y = 1.0f - ( 2.0f * mouse_y ) / win_height;
    float z = 1.0f;
    // normalised device space
    vec3 ray_nds = vec3( x, y, z );
    // clip space
    vec4 ray_clip = vec4( ray_nds.x, ray_nds.y, -1.0, 1.0 );
    // eye space
    vec4 ray_eye = inverse( proj_mat ) * ray_clip;
    ray_eye      = vec4( ray_eye.x, ray_eye.y, -1.0, 0.0 );
    // world space
    vec3 ray_wor = vec3( inverse( view_mat ) * ray_eye );
    // don't forget to normalise the vector at some point
    ray_wor = normalize( ray_wor );
    return ray_wor;
}

float mathlib::ray_box(float vertices[8][3], vec3 ray, vec3 origin, vec3 pos) {
    float dis = -1.0f;
    std::vector<float> distance;
    std::vector<vec3> location;
    vec3 final_pos(0.0f, 0.0f, 0.0f);
    for (int i = 0; i < 6; i++){
        vec3 p1 = make_vec3(vertices[cubeSufaceTriangles[i][0]]);
        vec3 p2 = make_vec3(vertices[cubeSufaceTriangles[i][1]]);
        vec3 p3 = make_vec3(vertices[cubeSufaceTriangles[i][2]]);
        vec3 p4 = make_vec3(vertices[cubeSufaceTriangles[i][2]]);
        vec3 normal = triangleNormal(p1,p2,p3);

        vec3 diagonal_vector = p3 - p1;
        vec3 middle_point = p1 + diagonal_vector * 0.5f;

        vec3 intersect_loc = origin - ray * dot(origin - middle_point, normal) / dot(ray, normal);

        float max_x = std::max({p1.x, p2.x, p3.x, p4.x});
        float min_x = std::min({p1.x, p2.x, p3.x, p4.x});
        float max_y = std::max({p1.y, p2.y, p3.y, p4.y});
        float min_y = std::min({p1.y, p2.y, p3.y, p4.y});
        float max_z = std::max({p1.z, p2.z, p3.z, p4.z});
        float min_z = std::min({p1.z, p2.z, p3.z, p4.z});
        bool hit_x = (intersect_loc.x < max_x && intersect_loc.x > min_x) || (abs(max_x - intersect_loc.x) < Detect_Epsilon && abs(min_x - intersect_loc.x) < Detect_Epsilon);
        bool hit_y = (intersect_loc.y < max_y && intersect_loc.y > min_y) || (abs(max_y - intersect_loc.y) < Detect_Epsilon && abs(min_y - intersect_loc.y) < Detect_Epsilon);
        bool hit_z = (intersect_loc.z < max_z && intersect_loc.z > min_z) || (abs(max_z - intersect_loc.z) < Detect_Epsilon && abs(min_z - intersect_loc.z) < Detect_Epsilon);
        if (hit_x && hit_y && hit_z) {
            float len = abs(glm::length(origin - intersect_loc));
            if (len < dis || dis == -1.0f) {
                dis = len;
            }
        }
    }

    return dis;
}
