#ifndef OBJECT_H
#define OBJECT_H

#include "../graphics/mesh.h"

typedef struct {
    Mesh mesh;         
    float position[3];
    float rotation[3]; // en radians
    float scale[3];
} Object3D;

typedef struct {
    Mesh mesh;  
    float position[3];
    float rotation[3]; // en radians
    float scale[3];
} Object2D;

#endif