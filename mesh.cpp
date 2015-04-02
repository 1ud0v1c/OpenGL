#include "mesh.h"

void Mesh::addVertex(Vertex v) {
	vbos.push_back(v);
}

void Mesh::addIbo(unsigned int pos) {
	ibos.push_back(pos);
}

void Mesh::addIbos(unsigned int pos, unsigned int pos2, unsigned int pos3) {
	ibos.push_back(pos);
	ibos.push_back(pos2);
	ibos.push_back(pos3);
}

std::vector<unsigned int> Mesh::getIbos() {
	return ibos;
}

std::vector<glm::vec3> Mesh::getPositions() {
	int i;
	std::vector<glm::vec3> positions;
	for (i = 0; i < vbos.size(); i++) {
		positions.push_back(vbos[i].getPosition());	
	}
	return positions;
}

std::vector<glm::vec4> Mesh::getColors() {
	int i;
	std::vector<glm::vec4> colors;
	for (i = 0; i < vbos.size(); i++) {
		colors.push_back(vbos[i].getColor());	
	}
	return colors;
}

std::vector<glm::vec2> Mesh::getUvs() {
	int i;
	std::vector<glm::vec2> uvs;
	for (i = 0; i < vbos.size(); i++) {
		std::vector<glm::vec2> tmp = vbos[i].getUv();
		uvs.insert(uvs.end(),tmp.begin(),tmp.end());
	}
	return uvs;
}

std::vector<glm::vec3> Mesh::getNormals() {
	int i;
	std::vector<glm::vec3> normals;
	for (i = 0; i < vbos.size(); i++) {
		normals.push_back(vbos[i].getNormal());	
	}
	return normals;
}

