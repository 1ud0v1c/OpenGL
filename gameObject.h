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
#include <glm/gtx/rotate_vector.hpp>
#include <sstream>
#include <algorithm>
#include "utils.h"
#include "mesh.h"
#include <algorithm>

class GameObject {

	public:
		GameObject(const std::string &name, GLuint &programm, std::vector<glm::vec3> &offset, const std::string &textureName="",bool isDynamiv=false,float angle=0);
		~GameObject();
		virtual void draw();
		virtual void makeObject();
		void  moveObject(glm::vec3 pos);
		glm::vec3 translation;
		void setType(GLuint type);
		void setUnit(int unit);
		GLuint getProgramm();
		std::vector<glm::vec3> getOffset(float x);
		void removeOffset(glm::vec3 off);
		std::string getName();

		std::vector<glm::vec3>  initCenter();
		void rotate(float angle);
		void resetVBO();
		double getRadius();
		bool isColliding(GameObject* go);
		bool loadOBJ(const std::string  &path);
		bool is_Dynamic();
		void setOffset(std::vector<glm::vec3> &newOffset);
	

	protected:
		int unit=0;
		GLuint vao;
		GLuint programm;
		std::string _name;
		Mesh mesh;
		std::vector<glm::vec3> offset;
		std::vector<glm::vec3> points;
		std::string textureName;
		GLuint type;
		GLuint texture;
		GLuint textureID;
		GLuint instanceVBO;
		double radius;
		glm::vec3 position;
		bool isDynamic;
		float angle;
		glm::vec3 size;
};
#endif
