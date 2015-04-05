#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "camera.h"

Camera::Camera() {
}

void Camera::update(float dt, GLFWwindow *window, glm::vec3 position, glm::vec3 direction, glm::vec3 up,glm::vec3 offset) {

	projection = glm::perspective(initialFoV, 4.0f / 3.0f, 0.1f, 2000.0f);
	view = glm::lookAt(
			  position+direction+offset, // Camera is here
			  position+offset, // and looks here : at the same position, plus "direction"
			  up // Head is up (set to 0,-1,0 to look upside-down)
			  );
}

glm::mat4 Camera::getProjection() {
	return projection;
}
glm::mat4 Camera::getView() {
	return view;
}
