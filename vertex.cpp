#include "vertex.h"

glm::vec3 Vertex::getPosition() {
	return position;
}

std::vector<glm::vec2> Vertex::getUv() {
	return uv;
}

glm::vec4 Vertex::getColor() {
	return color;
}

glm::vec3 Vertex::getNormal() {
	return normal;
}

void Vertex::addColor(float r, float g, float b, float o) {	
	color = glm::vec4(r,g,b,o);
}

void Vertex::addPosition(glm::vec3 pos) {
	position = pos;
}

void Vertex::addPosition(int x, int y, int z) {
	position = glm::vec3(x,y,z);
}

void Vertex::addUv(glm::vec2 pos, glm::vec2 pos2, glm::vec2 pos3) {
	uv.push_back(pos);
	uv.push_back(pos2);
	uv.push_back(pos3);
}

void Vertex::addUv(glm::vec2 pos) {
	uv.push_back(pos);
}

void Vertex::addNormal(int x, int y, int z){
	normal = glm::vec3(x,y,z);
}

void Vertex::addNormal(glm::vec3 norm){
	normal = norm;
}

