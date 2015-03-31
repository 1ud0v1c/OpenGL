#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <sstream>
#include "utils.h"
#include "mesh.h"

class GameObject {
	public:
		GameObject(const std::string &name, GLuint &programm, std::vector<float> &offset);
		~GameObject();
		virtual void draw();
		virtual void makeObject()=0;
		glm::mat4 moveObject();
		glm::vec3 translation;
		void setType(GLuint type);
		void setUnit(int unit);
		GLuint getProgramm();
		std::string getName();
	protected:
		int unit=0;
		GLuint vao;
		GLuint programm;
		std::string _name;
		Mesh mesh;
		std::vector<float> offset;

		GLuint type;
		GLuint texture;
		GLuint textureID;
		unsigned int vertexCount=0;
};
#endif
