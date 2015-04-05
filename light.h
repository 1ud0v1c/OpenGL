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
		void update(glm::vec3 pos);

	private:
		GLuint programm;
		glm::vec3 ambientColor ; //Color (0.2, 0.2, 0.2)
		glm::vec3 lightColor0 ;
		glm::vec3 lightPos0 ; //Positioned at (4, 0, 8)
		glm::vec3 lightColor1; //Color (0.5, 0.2, 0.2)
		glm::vec3 lightPos1;
		glm::vec3 lightdir;

};

#endif
