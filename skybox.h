#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

class Skybox {
	public:
		Skybox(std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back);
		void loadCubemap();

	private:
		GLuint textureID;
		std::vector<std::string> _faces;
};

#endif
