#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <GL/glew.h> // must be included before gl.h
#include <GLFW/glfw3.h>
#include <fstream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "scene.h"
#include "gameText.h"

class Game {
	public:
		Game();
		~Game();
		void initGLFW();
		void initGLEW();
		void init();
		void make_resources();
		void renderFrame();
		GLuint createShaders(const std::string & vertex, const std::string & fragment);
		void run();
		void shutDown(int i);
	private:
		const int width = 1024, height = 800;
		GLuint programm;
		GLFWwindow *window;
		Scene scene;
		GLuint MatrixID;
		GLuint type;
		GLuint diffuseID;
		std::map<std::string,GLuint> programms;
};

#endif 
