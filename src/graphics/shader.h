#ifndef SHADER_H
#define SHADER_H

unsigned int shader_create(const char* vertex_src, const char* fragment_src);
char* shader_load_file(const char* path);
void shader_use(unsigned int shader);
void shader_destroy(unsigned int shader);

#endif
