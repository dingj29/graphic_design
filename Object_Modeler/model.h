//
// Created by WILL on 2021/12/6.
//

#ifndef INC_3GC3_A4_MODEL_H
#define INC_3GC3_A4_MODEL_H


class model {
public:
    void load_object();

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

    model();
};


#endif //INC_3GC3_A4_MODEL_H
