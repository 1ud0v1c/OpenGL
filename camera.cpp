#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "camera.h"

Camera::Camera() {
}
void Camera::update(float dt, GLFWwindow *window) {
	static double lastTime = glfwGetTime();
	glfwGetCursorPos(window, &xpos, &ypos);
	double currentTime = glfwGetTime();
	glfwSetCursorPos(window, 1024/2, 768/2);
	float deltaTime = float(currentTime - lastTime);
	horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
	verticalAngle += mouseSpeed * deltaTime * float( 768/2 - ypos );
	glm::vec3 direction(
			  cos(verticalAngle) * sin(horizontalAngle),
			  sin(verticalAngle),
			  cos(verticalAngle) * cos(horizontalAngle)
			  );
	glm::vec3 right = glm::vec3(
			  sin(horizontalAngle - 3.14f/2.0f),
			  0,
			  cos(horizontalAngle - 3.14f/2.0f)
			  );
	glm::vec3 up = glm::cross( right, direction );
	if (glfwGetKey( window,GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window,GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window,GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window,GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}
	projection = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	view = glm::lookAt(
			  position, // Camera is here
			  position+direction, // and looks here : at the same position, plus "direction"
			  up // Head is up (set to 0,-1,0 to look upside-down)
			  );
	//float FoV = initialFoV - 5 * glfwGetMouseWheel();
	lastTime = currentTime;
}
glm::mat4 Camera::getProjection() {
	return projection;
}
glm::mat4 Camera::getView() {
	return view;
}
