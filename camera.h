#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include "glfwMinimal.h"

class Camera {
	public:
		Camera();
		glm::mat4 getView();
		glm::mat4 getProjection();
		void update();
		void setRadius(GLfloat rad);
		GLfloat getRadius();
		void moveCamera(int direction);
		void handleDeltaTime(GLfloat currentFrame);
		static void callback(GLFWwindow* window, double xpos, double ypos);
		void mouseCallback(GLFWwindow* window, double xpos, double ypos);

	private:
		float initialFoV = 45.0f;
		bool firstMouse = true;

		GLfloat lastX;
		GLfloat lastY;
		GLfloat yaw;
		GLfloat pitch;
		GLfloat speed = 0.05;
		GLfloat radius = 3.5f;
		GLfloat lastFrame = 0; 

		glm::mat4 view;
		glm::mat4 projection;

		glm::vec3 cameraPos;
		glm::vec3 cameraFront;
		glm::vec3 cameraUp;

		glm::vec3 cameraTarget;
		glm::vec3 cameraDirection;
};

#endif
