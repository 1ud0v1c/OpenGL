#ifndef GLFWMINIMAL_H
#define GLFWMINIMAL_H

#define WINDOW_WITH 1024
#define WINDOW_HEIGHT 800

#include <vector>
#include <GL/glew.h>
#include "mesh.h"

inline glm::vec3 torusPoint(double theta, double phi, double R, double r);
void makeATexturedTorus(Mesh *mesh, double R, double r, int nbBins);

glm::vec3 getLightDir();
#endif
