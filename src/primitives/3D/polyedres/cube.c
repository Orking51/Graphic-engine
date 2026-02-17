#include "primitives/geometry.h"
#include <stdlib.h>

Geometry generate_cube(float size)
{
    Geometry g;
    float s = size / 2.0f; // demi-côté pour centrer sur l'origine

    // 8 sommets du cube
    float vertices[24] = {
        -s, -s, -s,   s, -s, -s,   s,  s, -s,  -s,  s, -s,  // face arrière
        -s, -s,  s,   s, -s,  s,   s,  s,  s,  -s,  s,  s   // face avant
    };

    // Normales pour chaque sommet (6 faces, 4 sommets par face)
    float normals[24] = {
        0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1,   // arrière
        0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1    // avant
    };

    // Indices pour triangles (2 triangles par face, 6 faces)
    unsigned int indices[36] = {
        0,1,2, 2,3,0,   // arrière
        4,5,6, 6,7,4,   // avant
        3,2,6, 6,7,3,   // haut
        0,1,5, 5,4,0,   // bas
        1,2,6, 6,5,1,   // droite
        0,3,7, 7,4,0    // gauche
    };

    // Allocation dynamique pour retourner proprement
    g.vertexCount = 8;
    g.indexCount  = 36;

    g.vertices = (float*)malloc(sizeof(float) * 8 * 3);
    g.normals  = (float*)malloc(sizeof(float) * 8 * 3);
    g.indices  = (unsigned int*)malloc(sizeof(unsigned int) * 36);

    // Copie les données
    for(int i=0; i<24; i++) g.vertices[i] = vertices[i];
    for(int i=0; i<24; i++) g.normals[i]  = normals[i];
    for(int i=0; i<36; i++) g.indices[i]  = indices[i];

    return g;
}
