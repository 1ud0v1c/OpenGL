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
		GameObject(const std::string &name, GLuint &programm, std::vector<glm::vec3> &offset, const std::string &textureName="");
		~GameObject();
		virtual void draw();
		virtual void makeObject();
		void  moveObject(glm::vec3 pos);
		glm::vec3 translation;
		void setType(GLuint type);
		void setUnit(int unit);
		GLuint getProgramm();
		std::string getName();

		glm::vec3 getCenter();
		int getRadius();
		bool isColliding(GameObject* go);
		bool loadOBJ(const std::string  &path);

	protected:
		int unit=0;
		GLuint vao;
		GLuint programm;
		std::string _name;
		Mesh mesh;
		std::vector<glm::vec3> offset;
		std::string textureName;
		GLuint type;
		GLuint texture;
		GLuint textureID;
		int radius;
};
#endif
