#ifndef MESH_H
#define MESH_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include "vertex.h"

class Mesh {
	public:
		void addVertex(Vertex v);
		void addIbos(unsigned int pos, unsigned int pos2, unsigned int pos3);
		std::vector<unsigned int> getIbos();
		std::vector<glm::vec3> getPositions();
		std::vector<glm::vec4> getColors();
		std::vector<glm::vec2> getUvs();

	private:
		std::vector<Vertex> vbos;
		std::vector<unsigned int> ibos;
};

#endif
