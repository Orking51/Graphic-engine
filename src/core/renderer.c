#include "renderer.h"
#include "graphics/mesh.h"
#include "graphics/shader.h"
#include "primitives/primitives.h"
#include "configuration.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Ressources globales du renderer */

static unsigned int shader;

static WindowConfig winCfg;
RendererConfig rendCfg;
CameraConfig camCfg;
LightConfig LightCfg;

/* ========================= INIT ========================= */


void renderer_init(WindowConfig windowCfg)
{
    winCfg = windowCfg;

    renderer_config_defaults(&rendCfg);
    camera_config_defaults(&camCfg);
    light_config_defaults(&LightCfg);

    shader = shader_create("../shaders/basic.vert", "../shaders/basic.frag");

    if (rendCfg.enableDepthTest)
        glEnable(GL_DEPTH_TEST);

    if (rendCfg.enableBlend){
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    glDisable(GL_CULL_FACE);

    shader_use(shader);
    glUniform3fv(glGetUniformLocation(shader, "lightPos"), 1, LightCfg.lightPos);
    glUniform3fv(glGetUniformLocation(shader, "lightColor"), 1, LightCfg.lightColor);
    glUniform3fv(glGetUniformLocation(shader, "objectColor"), 1, LightCfg.objectColor);
}

void compute_model_matrix(const Object3D* obj, float time, float model[16])
{
    float cx = cos(time * 0.0);
    float sx = sin(time * 0.0);

    float cy = cos(time * 0.0);
    float sy = sin(time * 0.0);

    float cz = cos(time * 0.0); 
    float sz = sin(time * 0.0);

    // Rotation
    model[0] = cz*cy*obj->scale[0]; model[1] = cz*sy*sx - sz*cx; model[2] = cz*sy*cx + sz*sx; model[3] = 0.0;
    model[4] = sz*cy*obj->scale[1]; model[5] = sz*sy*sx + cz*cx; model[6] = sz*sy*cx - cz*sx; model[7] = 0.0;
    model[8] = -sy*obj->scale[2];   model[9] = cy*sx;            model[10]= cy*cx;            model[11]= 0.0;

    // Translation
    model[12] = obj->position[0];
    model[13] = obj->position[1];
    model[14] = obj->position[2];
    model[15] = 1.0;
}


static void compute_view_matrix(float view[16])
{
    view[0] = 1; view[1] = 0; view[2] = 0; view[3] = 0;
    view[4] = 0; view[5] = 1; view[6] = 0; view[7] = -1.25f;
    view[8] = 0; view[9] = 0; view[10]= 1; view[11]= -3;
    view[12]= 0; view[13]= 0; view[14]= 0; view[15]= 1;
}

static void compute_projection_matrix(float proj[16])
{
    float rad = camCfg.fov * 3.1415926f / 180.0f;
    float tanHalf = tanf(rad / 2.0f);
    float aspect = (float)winCfg.width / (float)winCfg.height;

    proj[0] = 1.0f/(aspect*tanHalf);   proj[1] = 0;            proj[2] = 0;                                                                         proj[3] = 0;
    proj[4] = 0;                       proj[5] = 1.0f/tanHalf; proj[6] = 0;                                                                         proj[7] = 0;
    proj[8] = 0;                       proj[9] = 0;            proj[10]= -(camCfg.farPlane+camCfg.nearPlane)/(camCfg.farPlane-camCfg.nearPlane);    proj[11]= -1;
    proj[12]= 0;                       proj[13]= 0;            proj[14]= -(2*camCfg.farPlane*camCfg.nearPlane)/(camCfg.farPlane-camCfg.nearPlane);  proj[15]= 0;
}

void renderer_draw(Object3D** objects, int count)
{

    shader_use(shader);

    float view[16], proj[16];
    compute_view_matrix(view);
    compute_projection_matrix(proj);
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_TRUE, view);
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, proj);
    float time = glfwGetTime();

    for (int i = 0; i < count; i++) {
        float model[16];
        compute_model_matrix(objects[i], time, model); // prend position/rotation/scale

        glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, model);
        mesh_draw(&objects[i]->mesh);
    }

}

/* ========================= CLEAR ========================= */

void renderer_clear(void)
{
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/* ========================= SHUTDOWN ========================= */

void renderer_shutdown(Object3D** objects, int objectCount)
{
    // Détruire tous les objets
    for (int i = 0; i < objectCount; i++)
    {
        mesh_destroy(&objects[i]->mesh);
    }

    objectCount = 0;

    shader_destroy(shader);
}




/*
static unsigned int VAO = 0, VBO = 0;

void renderer_draw_test_triangle(void)
{
    if (VAO == 0)
    {
        float vertices[] = {
             0.0f,  0.0f, 0.0f,  // placer devant la caméra
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f
        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    shader_use(shader);

    glEnableVertexAttribArray(0);


    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);

}

*/