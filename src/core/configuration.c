#include "configuration.h"

void window_config_defaults(WindowConfig* cfg)
{
    cfg->width  = 800;
    cfg->height = 600;
    cfg->title  = "Moteur Graphique";
}

void renderer_config_defaults(RendererConfig* cfg)
{
    cfg->enableDepthTest = 1;
    cfg->enableBlend     = 1;
    cfg->enableCulling   = 0;
}

void camera_config_defaults(CameraConfig* cfg)
{
    cfg->fov       = 90.0f;
    cfg->nearPlane = 0.1f;
    cfg->farPlane  = 100.0f;
}

void light_config_defaults(LightConfig* cfg)
{
    cfg->lightPos[0]   =  0.0f;  //x
    cfg->lightPos[1]   =  0.5f;  //y
    cfg->lightPos[2]   =  1.5f;  //z

    cfg->lightColor[0] = 0.74f;  //r 
    cfg->lightColor[1] = 0.5f;  //g
    cfg->lightColor[2] = 0.37f;  //b

    cfg->objectColor[0]= 0.12f;  //r
    cfg->objectColor[1]= 0.53f;  //g
    cfg->objectColor[2]= 0.85f;  //b
}


