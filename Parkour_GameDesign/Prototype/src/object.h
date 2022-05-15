#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <string>

// Enum for easier/safer polymorphic type check
enum ObjectType { PLAYER, OBSTACLE, LANE };

// Generic object (coordinates, type specfier, obj loader logic)
class Object
{
public:
	float positionX;
	float positionY;
	float positionZ;

	int color;
	ObjectType type;
	Object(float x = 0, float y = 0, float z = 0, int color = 0);
	void obj_render();
    bool load_obj(const char *path);

private:


    class Face {
    public:
        int edge;
        int *vertices;
        int *texcoords;
        int normal;

        Face(int edge, int *vertices, int *texcoords, int normal = -1) {
            this->edge = edge;
            this->vertices = vertices;
            this->texcoords = texcoords;
            this->normal = normal;
        }
    };
    GLuint list;
    std::vector<float *> veI;
    std::vector<float *> uvI;
    std::vector<float *> noI;
    std::vector<Face> faces;
};




#endif