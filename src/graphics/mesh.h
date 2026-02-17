#ifndef MESH_H
#define MESH_H

#include "primitives/geometry.h"

typedef struct {
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
    int indexCount; // pour glDrawElements
} Mesh;

void mesh_init(Mesh* mesh, Geometry* g);
void mesh_draw(Mesh* mesh);
void mesh_destroy(Mesh* mesh);

#endif
