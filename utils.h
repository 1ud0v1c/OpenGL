#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>

char *read_tga(const char *filename, int& width, int& height);
std::string file_contents(const char* file, int* size);
static short le_short(unsigned char *bytes);
bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec2> & out_uvs, std::vector<glm::vec3> & out_normals);

#endif
