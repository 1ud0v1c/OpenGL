#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp> 
#include <iostream>
#include <vector>

class Vertex {
	public:
		glm::vec3 getPosition(); 
		glm::vec4 getColor(); 
		glm::vec3 getNormal();
		std::vector<glm::vec2> getUv();

		void addPosition(int x, int y, int z);
		void addPosition(glm::vec3 pos);
		void addColor(float r, float g, float b, float o);
		void addUv(glm::vec2 pos, glm::vec2 pos2, glm::vec2 pos3);
		void addUv(glm::vec2 pos);
		void addNormal(int x, int y, int z);
		void addNormal(glm::vec3 norm);

	private:
		glm::vec3 position;
		glm::vec4 color;
		std::vector<glm::vec2> uv;

		glm::vec3 normal;
		glm::vec3 tangent;
};

#endif
