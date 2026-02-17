#include "primitives/geometry.h"
#include "primitives/object.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359f

Geometry generate_uv_sphere(float radius, int sectors, int stacks)
{
    Geometry g;

    g.vertexCount = (stacks + 1) * (sectors + 1);
    g.indexCount  = stacks * sectors * 6;

    g.vertices = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.normals  = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.indices  = (unsigned int*)malloc(g.indexCount * sizeof(unsigned int));

    int vi = 0;
    int ii = 0;

    float sectorStep = 2 * PI / sectors;
    float stackStep  = PI / stacks;

    for(int i = 0; i <= stacks; ++i)
    {
        float stackAngle = PI/2 - i * stackStep;
        float xy = radius * cosf(stackAngle);
        float z  = radius * sinf(stackAngle);

        for(int j = 0; j <= sectors; ++j)
        {
            float sectorAngle = j * sectorStep;

            float x = xy * cosf(sectorAngle);
            float y = xy * sinf(sectorAngle);

            // position
            g.vertices[vi]     = x;
            g.vertices[vi + 1] = y;
            g.vertices[vi + 2] = z;

            // normale
            g.normals[vi]     = x / radius;
            g.normals[vi + 1] = y / radius;
            g.normals[vi + 2] = z / radius;

            vi += 3;
        }
    }

    for(int i = 0; i < stacks; ++i)
    {
        int k1 = i * (sectors + 1);
        int k2 = k1 + sectors + 1;

        for(int j = 0; j < sectors; ++j, ++k1, ++k2)
        {
            if(i != 0)
            {
                g.indices[ii++] = k1;
                g.indices[ii++] = k2;
                g.indices[ii++] = k1 + 1;
            }
            if(i != (stacks - 1))
            {
                g.indices[ii++] = k1 + 1;
                g.indices[ii++] = k2;
                g.indices[ii++] = k2 + 1;
            }
        }
    }

    return g;
}

Object3D* create_uv_sphere(float radius, int slices, int stacks) {
    Object3D* obj = malloc(sizeof(Object3D));
    Geometry g = generate_uv_sphere(radius, slices, stacks);
    printf("Banane %d\n Banane2 %d\n", g.indexCount, g.vertexCount);
    mesh_init(&obj->mesh, &g);
    geometry_free(&g);

    obj->position[0] = obj->position[1] = obj->position[2] = 0.0f;
    obj->rotation[0] = obj->rotation[1] = obj->rotation[2] = 0.0f;
    obj->scale[0] = obj->scale[1] = obj->scale[2] = 1.0f;

    return obj;
}
