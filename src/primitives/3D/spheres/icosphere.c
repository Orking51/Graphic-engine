#include "primitives/geometry.h"
#include "primitives/object.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359f

typedef struct {
    float x, y, z;
} Vec3;

static Vec3 vec3_normalize(Vec3 v) {
    float len = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    Vec3 r = { v.x/len, v.y/len, v.z/len };
    return r;
}

static Vec3 vec3_midpoint(Vec3 a, Vec3 b) {
    Vec3 m = { (a.x + b.x)/2.0f, (a.y + b.y)/2.0f, (a.z + b.z)/2.0f };
    return m;
}

// Structure pour garder les faces temporairement
typedef struct {
    int v1, v2, v3;
} Triangle;

Geometry generate_icosphere(float radius, int subdivisions)
{
    Geometry g;
    // Icosahedron constants
    const float t = (1.0 + sqrtf(5.0)) / 2.0;

    // 12 vertices of icosahedron
    Vec3 verts[12] = {
        {-1,  t,  0}, { 1,  t,  0}, {-1, -t,  0}, { 1, -t,  0},
        { 0, -1,  t}, { 0,  1,  t}, { 0, -1, -t}, { 0,  1, -t},
        { t,  0, -1}, { t,  0,  1}, {-t,  0, -1}, {-t,  0,  1}
    };

    for(int i = 0; i < 12; ++i)
        verts[i] = vec3_normalize(verts[i]);

    // 20 faces
    Triangle faces[20] = {
        {0,11,5}, {0,5,1}, {0,1,7}, {0,7,10}, {0,10,11},
        {1,5,9}, {5,11,4}, {11,10,2}, {10,7,6}, {7,1,8},
        {3,9,4}, {3,4,2}, {3,2,6}, {3,6,8}, {3,8,9},
        {4,9,5}, {2,4,11}, {6,2,10}, {8,6,7}, {9,8,1}
    };

    // On va stocker temporairement les vertices dynamiquement
    int maxVerts = 12 + 1000 * subdivisions * subdivisions; // estimation
    Vec3* vertList = malloc(maxVerts * sizeof(Vec3));
    int vertCount = 12;
    for(int i = 0; i < 12; ++i) vertList[i] = verts[i];

    int maxFaces = 20 * pow(4, subdivisions); // estimation
    Triangle* faceList = malloc(maxFaces * sizeof(Triangle));
    int faceCount = 20;
    for(int i = 0; i < 20; ++i) faceList[i] = faces[i];

    // Subdivision
    for(int s = 0; s < subdivisions; ++s)
    {
        int currentFaceCount = faceCount;
        Triangle* newFaces = malloc(4 * currentFaceCount * sizeof(Triangle));
        int nf = 0;

        for(int i = 0; i < currentFaceCount; ++i)
        {
            Triangle f = faceList[i];
            Vec3 a = vertList[f.v1];
            Vec3 b = vertList[f.v2];
            Vec3 c = vertList[f.v3];

            Vec3 ab = vec3_normalize(vec3_midpoint(a, b));
            Vec3 bc = vec3_normalize(vec3_midpoint(b, c));
            Vec3 ca = vec3_normalize(vec3_midpoint(c, a));

            int abIndex = vertCount++; vertList[abIndex] = ab;
            int bcIndex = vertCount++; vertList[bcIndex] = bc;
            int caIndex = vertCount++; vertList[caIndex] = ca;

            newFaces[nf++] = (Triangle){f.v1, abIndex, caIndex};
            newFaces[nf++] = (Triangle){f.v2, bcIndex, abIndex};
            newFaces[nf++] = (Triangle){f.v3, caIndex, bcIndex};
            newFaces[nf++] = (Triangle){abIndex, bcIndex, caIndex};
        }

        free(faceList);
        faceList = newFaces;
        faceCount = nf;
    }

    // Maintenant on crée le Geometry final
    g.vertexCount = vertCount;
    g.indexCount  = faceCount * 3;
    g.vertices = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.normals  = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.indices  = (unsigned int*)malloc(g.indexCount * sizeof(unsigned int));

    for(int i = 0; i < vertCount; ++i) {
        g.vertices[i*3 + 0] = vertList[i].x * radius;
        g.vertices[i*3 + 1] = vertList[i].y * radius;
        g.vertices[i*3 + 2] = vertList[i].z * radius;

        g.normals[i*3 + 0] = vertList[i].x;
        g.normals[i*3 + 1] = vertList[i].y;
        g.normals[i*3 + 2] = vertList[i].z;
    }

    for(int i = 0; i < faceCount; ++i) {
        g.indices[i*3 + 0] = faceList[i].v1;
        g.indices[i*3 + 1] = faceList[i].v2;
        g.indices[i*3 + 2] = faceList[i].v3;
    }

    free(vertList);
    free(faceList);

    return g;
}

Object3D* create_icosphere(float radius, int subdivisions) {
    Object3D* obj = malloc(sizeof(Object3D));
    Geometry g = generate_icosphere(radius, subdivisions);
    mesh_init(&obj->mesh, &g);
    geometry_free(&g);

    obj->position[0] = obj->position[1] = obj->position[2] = 0.0f;
    obj->rotation[0] = obj->rotation[1] = obj->rotation[2] = 0.0f;
    obj->scale[0] = obj->scale[1] = obj->scale[2] = 1.0f;

    return obj;
}
