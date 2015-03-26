#ifndef GLFWMINIMAL_H
#define GLFWMINIMAL_H

#define WINDOW_WITH 1024
#define WINDOW_HEIGHT 800

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "mesh.h"

void init();
void initGLFW();
void initGLEW();
void init_shaders(std::string* tempv, std::string* tempf, GLint* lengthv, GLint* lengthf, GLuint* shaderID);
void renderFrame();

inline glm::vec3 torusPoint(double theta, double phi, double R, double r);
void makeATexturedTorus(Mesh *mesh, double R, double r, int nbBins);
void make_resources();
void make_shaders(std::string* tempv, std::string* tempf, GLint* lengthv, GLint* lengthf);

glm::vec3 getLightDir();
#endif
