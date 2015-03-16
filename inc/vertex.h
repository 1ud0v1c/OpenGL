#ifndef VERTEX_H 
#define VERTEX_H 

#include <iostream>
#include <vector>

class Vertex {
	public:
		Vertex(std::vector<float> pos, std::vector<float> col);

	private:
		std::vector<float> _positions;
		std::vector<float> _colors;
		std::vector<float> _normals;
		std::vector<float> _uvs;
};

#endif
