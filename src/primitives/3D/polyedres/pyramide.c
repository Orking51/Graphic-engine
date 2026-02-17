#include "primitives/geometry.h"
#include "primitives/object.h"
#include <stdlib.h>
#include <math.h>

Geometry generate_pyramid(float baseSize, float height)
{
    Geometry g;

    g.vertexCount = 18;          // 6 triangles * 3 sommets
    g.indexCount  = 18;          // 6 triangles

    g.vertices = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.normals  = (float*)malloc(g.vertexCount * 3 * sizeof(float));
    g.indices  = (unsigned int*)malloc(g.indexCount * sizeof(unsigned int));

    float h2 = height * 0.5f;
    float b2 = baseSize * 0.5f;

    // Positions principales
    float apex[3] = {0.0f, 0.0f,  h2};

    float v0[3] = {-b2, -b2, -h2};
    float v1[3] = { b2, -b2, -h2};
    float v2[3] = { b2,  b2, -h2};
    float v3[3] = {-b2,  b2, -h2};

    int vi = 0;
    int ii = 0;

    // Macro pratique
    #define ADD_VERTEX(px,py,pz,nx,ny,nz) \
        g.vertices[vi] = px; \
        g.vertices[vi+1] = py; \
        g.vertices[vi+2] = pz; \
        g.normals[vi] = nx; \
        g.normals[vi+1] = ny; \
        g.normals[vi+2] = nz; \
        vi += 3;

    // Faces latérales

    float faces[4][2][3] = {
        {{v0[0],v0[1],v0[2]}, {v1[0],v1[1],v1[2]}},
        {{v1[0],v1[1],v1[2]}, {v2[0],v2[1],v2[2]}},
        {{v2[0],v2[1],v2[2]}, {v3[0],v3[1],v3[2]}},
        {{v3[0],v3[1],v3[2]}, {v0[0],v0[1],v0[2]}}
    };

    for(int f = 0; f < 4; ++f)
    {
        float* p0 = faces[f][0];
        float* p1 = faces[f][1];

        // calcul normale face
        float ux = p0[0] - apex[0];
        float uy = p0[1] - apex[1];
        float uz = p0[2] - apex[2];

        float vx = p1[0] - apex[0];
        float vy = p1[1] - apex[1];
        float vz = p1[2] - apex[2];

        float nx = uy*vz - uz*vy;
        float ny = uz*vx - ux*vz;
        float nz = ux*vy - uy*vx;

        float len = sqrtf(nx*nx + ny*ny + nz*nz);
        nx/=len; ny/=len; nz/=len;

        int baseIndex = vi / 3;

        ADD_VERTEX(apex[0],apex[1],apex[2], nx,ny,nz);
        ADD_VERTEX(p0[0],p0[1],p0[2], nx,ny,nz);
        ADD_VERTEX(p1[0],p1[1],p1[2], nx,ny,nz);

        g.indices[ii++] = baseIndex;
        g.indices[ii++] = baseIndex + 1;
        g.indices[ii++] = baseIndex + 2;
    }

    //  Base (2 triangles)
    float nx = 0.0f, ny = 0.0f, nz = -1.0f;

    int baseIndex = vi / 3;

    ADD_VERTEX(v0[0],v0[1],v0[2], nx,ny,nz);
    ADD_VERTEX(v1[0],v1[1],v1[2], nx,ny,nz);
    ADD_VERTEX(v2[0],v2[1],v2[2], nx,ny,nz);

    g.indices[ii++] = baseIndex;
    g.indices[ii++] = baseIndex + 1;
    g.indices[ii++] = baseIndex + 2;

    baseIndex = vi / 3;

    ADD_VERTEX(v0[0],v0[1],v0[2], nx,ny,nz);
    ADD_VERTEX(v2[0],v2[1],v2[2], nx,ny,nz);
    ADD_VERTEX(v3[0],v3[1],v3[2], nx,ny,nz);

    g.indices[ii++] = baseIndex;
    g.indices[ii++] = baseIndex + 1;
    g.indices[ii++] = baseIndex + 2;

    return g;
}


Object3D* create_pyramid(float baseSize, float height)
{
    Object3D* obj = malloc(sizeof(Object3D));

    Geometry g = generate_pyramid(baseSize, height);
    mesh_init(&obj->mesh, &g);   // EBO utilisé ici
    geometry_free(&g);

    obj->position[0] = obj->position[1] = obj->position[2] = 0.0f;
    obj->rotation[0] = obj->rotation[1] = obj->rotation[2] = 0.0f;
    obj->scale[0]    = obj->scale[1]    = obj->scale[2]    = 1.0f;

    return obj;
}
