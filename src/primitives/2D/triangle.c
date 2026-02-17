#include "primitives/object.h"

static unsigned int VAO = 0, VBO = 0;

Object2D triangle(){

    if (VAO == 0){
        float vertices[] = {
            0.0f,  0.0f, 0.0f,  // placer devant la caméra
           -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
        };
    } 

}