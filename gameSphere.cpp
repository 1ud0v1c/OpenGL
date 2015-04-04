#include "gameSphere.h"
#include <iostream>

GameSphere::GameSphere(const std::string &name, GLuint &programm,double R,glm::vec3 color,std::vector<glm::vec3> &offset,const std::string t) : GameObject(name,programm,offset,t) {
	this->R = R;
	radius = R;
	this->colorValue = color;
}

void GameSphere::draw() {
	GameObject::draw();
}

void GameSphere::makeObject() {
	int nbBins = 50;

	for(int indexT = 0; indexT < nbBins; indexT++) {
		for(int indexP = 0;indexP < nbBins; indexP++) {
			double phi = -glm::pi<float>()/2 + indexP*glm::pi<float>()/(nbBins-1);
			double theta = 2*indexT*glm::pi<float>()/nbBins;

			Vertex tmp;
			tmp.addPosition(spherePoint(theta,phi,R));
			tmp.addColor(colorValue[0], colorValue[1], colorValue[2], 1);

			tmp.addUv(glm::vec2(0,0), glm::vec2(0,1), glm::vec2(1,1));
			tmp.addUv(glm::vec2(0,0), glm::vec2(1,1), glm::vec2(1,0));
			
			mesh.addVertex(tmp);
		}
	}

	for(int indexT = 0; indexT < nbBins; indexT++) {
		for(int indexP =0;indexP < nbBins-1; indexP++) {
			mesh.addIbos(indexT*nbBins+indexP, ((indexT+1)%nbBins)*nbBins+indexP, indexT*nbBins+(indexP+1));
			mesh.addIbos(((indexT+1)%nbBins)*nbBins+indexP, indexT*nbBins+(indexP+1), ((indexT+1)%nbBins)*nbBins+(indexP+1));
		}
	}

	GameObject::makeObject();
}

glm::vec3 GameSphere::spherePoint(double theta, double phi, double R) {
	float x,y,z;
	x = R*glm::cos(theta)*glm::cos(phi);
	y = R*glm::cos(phi)*glm::sin(theta);
	z = R*glm::sin(phi);
	return glm::vec3(x,y,z);
}

GameSphere::~GameSphere() { 

}

