#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "error.h"

class Light {
	public:
		Light();
		Light(GLuint programm);
		void draw();
		void init();

	private:
		GLuint programm;

};

#endif
