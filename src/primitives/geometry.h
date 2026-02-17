#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct {
    float* vertices;      // positions x, y, z
    float* normals;       // normales x, y, z
    unsigned int* indices; // indices des triangles
    int vertexCount;      // nombre de vertices (vbo)
    int indexCount;       // nombre d'indices (ebo)
} Geometry;

// Fonction pour libérer la mémoire CPU
void geometry_free(Geometry* g);

#endif
