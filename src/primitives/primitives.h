#include "geometry.h" 

#ifndef SPHERE_UV_H
#define SPHERE_UV_H
Object3D* create_uv_sphere(float radius, int sectors, int stacks);
#endif

#ifndef ICOSPHERE_H
#define ICOSPHERE_H
Object3D* create_icosphere(float radius, int subdivisions);
#endif

#ifndef CONE_H
#define CONE_H
Object3D* create_cone(float radius, float height, int sectors);
#endif

#ifndef PYRAMIDE_H
#define PYRAMIDE_H
Object3D* create_pyramid(float baseSize, float height);
#endif

#ifndef CUBE_H
#define CUBE_H
Geometry generate_cube(float size); 
#endif

