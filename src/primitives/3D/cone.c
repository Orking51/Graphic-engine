#include "primitives/geometry.h"
#include "primitives/object.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359f

Geometry generate_cone(float radius, float height, int sectors)
{
    Geometry g;

    // 1 sommet apex
    // sectors sommets base
    // 1 sommet centre base
    g.vertexCount = 1 + sectors + 1;
    g.indexCount  = sectors * 6; 
    // sectors triangles latéraux (3 indices)
    // sectors triangles base (3 indices)

    g.vertices = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.normals  = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.indices  = (unsigned int*)malloc(g.indexCount * sizeof(unsigned int));

    float halfHeight = height * 0.5f;
    float sectorStep = 2.0f * PI / sectors;

    int vi = 0;
    int ii = 0;

    //      Sommet (apex)
    g.vertices[vi]     = 0.0f;
    g.vertices[vi + 1] = 0.0f;
    g.vertices[vi + 2] = halfHeight;

    // normale approximative vers le haut
    g.normals[vi]     = 0.0f;
    g.normals[vi + 1] = 0.0f;
    g.normals[vi + 2] = 1.0f;

    int apexIndex = 0;
    vi += 3;


    //  Cercle de base
    int baseStartIndex = 1;

    for(int i = 0; i < sectors; ++i)
    {
        float angle = i * sectorStep;

        float x = radius * cosf(angle);
        float y = radius * sinf(angle);
        float z = -halfHeight;

        g.vertices[vi]     = x;
        g.vertices[vi + 1] = y;
        g.vertices[vi + 2] = z;

        // normale latérale (calcul correct)
        float nx = x;
        float ny = y;
        float nz = radius / height;

        float len = sqrtf(nx*nx + ny*ny + nz*nz);
        g.normals[vi]     = nx / len;
        g.normals[vi + 1] = ny / len;
        g.normals[vi + 2] = nz / len;

        vi += 3;
    }

    //      Centre de la base
    int baseCenterIndex = 1 + sectors;

    g.vertices[vi]     = 0.0f;
    g.vertices[vi + 1] = 0.0f;
    g.vertices[vi + 2] = -halfHeight;

    g.normals[vi]     = 0.0f;
    g.normals[vi + 1] = 0.0f;
    g.normals[vi + 2] = -1.0f;

    vi += 3;
    
    //      Indices - côtés
    for(int i = 0; i < sectors; ++i)
    {
        int current = baseStartIndex + i;
        int next    = baseStartIndex + ((i + 1) % sectors);

        g.indices[ii++] = apexIndex;
        g.indices[ii++] = next;
        g.indices[ii++] = current;
    }

    //      Indices - base
    for(int i = 0; i < sectors; ++i)
    {
        int current = baseStartIndex + i;
        int next    = baseStartIndex + ((i + 1) % sectors);

        g.indices[ii++] = baseCenterIndex;
        g.indices[ii++] = current;
        g.indices[ii++] = next;
    }

    return g;
}

Object3D* create_cone(float radius, float height, int sectors)
{
    Object3D* obj = malloc(sizeof(Object3D));

    Geometry g = generate_cone(radius, height, sectors);
    mesh_init(&obj->mesh, &g);
    geometry_free(&g);

    obj->position[0] = obj->position[1] = obj->position[2] = 0.0f;
    obj->rotation[0] = obj->rotation[1] = obj->rotation[2] = 0.0f;
    obj->scale[0]    = obj->scale[1]    = obj->scale[2]    = 1.0f;

    return obj;
}
