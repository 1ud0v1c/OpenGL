#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

char *read_tga(const char *filename, int& width, int& height);
GLuint loadTGATexture(const std::string& imagepath, int width=256,int height=256,GLenum wrap_s=GL_REPEAT, GLenum wrap_t=GL_REPEAT, GLenum mag_filter=GL_LINEAR, GLenum min_filter=GL_LINEAR_MIPMAP_LINEAR, bool anisotropy=false);
std::string file_contents(const std::string &file, int* size);
static short le_short(unsigned char *bytes);
GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint loadDDS(const char * imagepath);
glm::vec3 getMaxPosition(std::vector<glm::vec3> positions);
glm::vec3 getMinPosition(std::vector<glm::vec3> positions);

#endif
