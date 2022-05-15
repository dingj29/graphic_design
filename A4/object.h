#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <vector>
#include "model.h"
enum Shape
{
	CUBE = 1, SPHERE = 2, CONE = 3, TORUS = 4, TEAPOT = 5, TETRAHEDRON = 6, CAT = 7
};


enum Material
{
	EMERALD = 1, BRASS = 2, BRONZE = 3, GOLD = 4, COPPER = 5, CYAN_PLASTIC = 6
};

class Object {
public:
	float position[3];
	float orientation[3];
	float scale[3];
        float vertices[8][3];
	Shape obj_shape;
	Material obj_material;
	bool is_selected;
	Object(Material mat, Shape shap);
	void setPosition(float x, float y, float z);
	void setOrientation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void apply_obj_mat();
    void update_vertices();
	void render_obj(bool selected);
	//add
	//void draw_box();
        static void drawBox(GLfloat size, GLenum type);

private:
	model cat;
        void setAmb(float x, float y, float z, float a);
        void setDiff(float x, float y, float z, float a);
        void setSpec(float x, float y, float z, float a);
        void setShin(float s);
	void draw_box();
};