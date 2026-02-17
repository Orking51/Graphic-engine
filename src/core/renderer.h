#ifndef RENDERER_H
#define RENDERER_H

#include "configuration.h"
#include "graphics/mesh.h"
#include "primitives/object.h"


void renderer_init(WindowConfig Windowcfg);
void renderer_draw(Object3D** objects, int count);
void renderer_draw_test_triangle(void);
void renderer_clear(void);
void renderer_shutdown(Object3D** objects, int objectCount);

#endif
