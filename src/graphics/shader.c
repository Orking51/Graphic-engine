#include "shader.h"
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void check_compile_errors(unsigned int shader, const char* type)
{
    int success;
    char infoLog[512];

    if (strcmp(type, "PROGRAM") != 0)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            printf("Shader compile error (%s):\n%s\n", type, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infoLog);
            printf("Program link error:\n%s\n", infoLog);
        }
    }
}

char* shader_load_file(const char* path)
{
    FILE* f = fopen(path, "rb");
    if (!f) {
        printf("FAILED TO LOAD SHADER: %s\n", path);
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);

    char* buffer = malloc(len + 1);
    fread(buffer, 1, len, f);
    buffer[len] = '\0';

    fclose(f);
    return buffer;
}

unsigned int shader_create(const char* vertex_path, const char* fragment_path)
{

    const char* vertex_src = shader_load_file(vertex_path);
    const char* fragment_src = shader_load_file(fragment_path);

    if (!vertex_src) printf("Vertex shader source is NULL\n");
    if (!fragment_src) printf("Fragment shader source is NULL\n");

    printf("VERTEX SOURCE:\n%s\n", vertex_src);
    printf("FRAGMENT SOURCE:\n%s\n", fragment_src);


    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_src, NULL);
    glCompileShader(vertex);
    check_compile_errors(vertex, "VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_src, NULL);
    glCompileShader(fragment);
    check_compile_errors(fragment, "FRAGMENT");

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);
    check_compile_errors(program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    printf("Shader program ID = %u\n", program);

    return program;
}


void shader_use(unsigned int shader)
{
    glUseProgram(shader);
}

void shader_destroy(unsigned int shader)
{
    glDeleteProgram(shader);
}



//mat3(transpose(inverse(model))) * aNormal;
//gl_Position = projection * view * model * vec4(aPos, 1.0);

/*
vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 result = diff * lightColor * objectColor;
    FragColor = vec4(result, 1.0);
*/