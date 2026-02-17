#include "geometry.h"
#include <stdlib.h>

void geometry_free(Geometry* g)
{
    if (!g) return;

    if (g->vertices) free(g->vertices);
    if (g->normals)  free(g->normals);
    if (g->indices)  free(g->indices);

    g->vertices = NULL;
    g->normals  = NULL;
    g->indices  = NULL;
    g->vertexCount = 0;
    g->indexCount  = 0;
}

