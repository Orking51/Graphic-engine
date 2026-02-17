cmake_minimum_required(VERSION 3.16)

project(moteur_graphique C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(moteur
    src/main.c

    src/core/window.c
    src/core/renderer.c
    src/core/configuration.c
    src/core/scene.c

    src/graphics/shader.c
    src/graphics/mesh.c

    src/primitives/geometry.c
    src/primitives/3D/cone.c
    src/primitives/3D/spheres/sphere_uv.c
    src/primitives/3D/spheres/icosphere.c
    src/primitives/3D/spheres/cube_sphere.c
    src/primitives/3D/polyedres/cube.c
    src/primitives/3D/polyedres/pyramide.c
    src/primitives/2D/triangle.c

    external/glad/src/glad.c
)


target_include_directories(moteur PRIVATE
    src
    shaders
    external/glad/include
)

target_link_libraries(moteur
    glfw
    GL
    m
)
