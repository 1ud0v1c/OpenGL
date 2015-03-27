#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include "glfwMinimal.h"

class Camera {
	public:
		glm::mat4 getView();
		glm::mat4 getProjection();
		void update();
		void setRadius(GLfloat rad);
		GLfloat getRadius();
		GLfloat getCamX();
		GLfloat getCamZ();

	private:
		float initialFoV = 45.0f;

		GLfloat radius = 3.5f;
		GLfloat camX = sin(glfwGetTime())*radius;
		GLfloat camZ = cos(glfwGetTime())*radius;

		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;
};

#endif
