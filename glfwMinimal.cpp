#include <iostream>
#include <fstream>
#include <cmath>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include "glfwMinimal.h"
#include "game.h"
#include "utils.h"
#include "camera.h"
#include "controls.h"
#include "text2D.h"

using namespace std;

GLuint programId;
GLuint vao;
unsigned int longueurIndex;
float uTime = 0.0;
Camera *cam = new Camera();

int main(void) {
	int running = 1;
	float diff = 0.005;
	longueurIndex=0;
	Game game;
	game.init();
	Controls controls(glfwGetCurrentContext(),cam,true);
	game.run();
}


inline glm::vec3 torusPoint(double theta, double phi, double R, double r) {
	float x, y,z;

	x = (R+r*cos(theta))*cos(phi);
	y = (R+r*cos(theta))*sin(phi);
	z = r*sin(theta);

	return glm::vec3(x,y,z); 
}


void makeATexturedTorus(Mesh *mesh, double R, double r, int nbBins) {
	int i=0,j=0;
	for (double theta=0; theta <= 2*M_PI; theta+=2*M_PI/nbBins){
		for (double phi=0; phi < 2*M_PI; phi+=2*M_PI/nbBins){
			int index = (i+1)%nbBins;
			int indexj = (j+1)%nbBins;

			Vertex tmp;
			tmp.addPosition(torusPoint(theta,phi,R,r));
			tmp.addColor(1,0,0,1);
			tmp.addUv(glm::vec2(0,0), glm::vec2(0,1), glm::vec2(1,1));
			tmp.addUv(glm::vec2(0,0), glm::vec2(1,1), glm::vec2(1,0));

			mesh->addIbos(i*nbBins+j, i*nbBins+indexj, index*nbBins+j);
			mesh->addIbos(index*nbBins+j, i*nbBins+indexj, index*nbBins+indexj);
			mesh->addVertex(tmp);

			longueurIndex+=6;
			j++;
		}
		j=0;
		i++;
	}
}

glm::vec3 getLightDir() {
	// glm::mat4 rotL=glm::rotate(glm::mat4(), -cam->getCamX(), glm::vec3(1,0,0));
	// rotL=glm::rotate(rotL, -cam->getCamZ(), glm::vec3(0,0,1));
	glm::mat4 rotL;
	glm::vec3 lightdirn=glm::normalize(glm::mat3(rotL)*glm::vec3(0.4,0.6,0.4));
	return lightdirn;
}
