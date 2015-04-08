#ifndef SKYBOX_H
#define SKYBOX_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp> 
#include <glm/gtc/constants.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#define SKYBOX_SIZE 1000

class Skybox {
	public:
		Skybox();
		Skybox(GLuint program, std::string top, std::string bottom, std::string left, std::string right, std::string front, std::string back);
		void loadCubemap();
		GLuint getProgramm();
		void init();
		void draw();
		void update(glm::vec3 position);

	private:
		GLuint skyboxVAO, skyboxVBO;
		GLuint program;
		GLuint textureID;
		std::vector<std::string> _faces;
};

#endif
