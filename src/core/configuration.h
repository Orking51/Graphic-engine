#ifndef CONFIGURATION_H
#define CONFIGURATION_H

typedef struct {
    int width;
    int height;
    const char* title;
} WindowConfig;
void window_config_defaults(WindowConfig* cfg);

typedef struct {
    int enableDepthTest;
    int enableBlend;
    int enableCulling;
} RendererConfig;
void renderer_config_defaults(RendererConfig* cfg);

typedef struct {
    float fov;      
    float nearPlane;
    float farPlane;
} CameraConfig;
void camera_config_defaults(CameraConfig* cfg);

typedef struct {
    float lightPos[3];
    float lightColor[3];
    float objectColor[3];
} LightConfig;
void light_config_defaults(LightConfig* cfg);

#endif
