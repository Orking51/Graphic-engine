#include "mesh.h"
#include <glad/glad.h>
#include <stdlib.h>

void mesh_init(Mesh* mesh, Geometry* g)
{
    mesh->indexCount = g->indexCount;

    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    
    // Interleave positions et normales
    float* interleaved = malloc(g->vertexCount * 6 * sizeof(float));
    for (int i = 0; i < g->vertexCount; i++)
    {
        interleaved[i*6 + 0] = g->vertices[i*3 + 0];
        interleaved[i*6 + 1] = g->vertices[i*3 + 1];
        interleaved[i*6 + 2] = g->vertices[i*3 + 2];

        interleaved[i*6 + 3] = g->normals[i*3 + 0];
        interleaved[i*6 + 4] = g->normals[i*3 + 1];
        interleaved[i*6 + 5] = g->normals[i*3 + 2];
    }

    glBufferData(GL_ARRAY_BUFFER, g->vertexCount * 6 * sizeof(float),
                 interleaved, GL_STATIC_DRAW);
    free(interleaved);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, g->indexCount * sizeof(unsigned int),
                 g->indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void mesh_draw(Mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
}

void mesh_destroy(Mesh* mesh)
{
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->VBO);
    glDeleteBuffers(1, &mesh->EBO);
}
