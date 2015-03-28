#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "camera.h"

Camera::Camera() {
	obj = this;
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	cameraDirection = glm::normalize(cameraPos - cameraTarget);

	cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
}

void Camera::update() {
	float ratio = (GLfloat)WINDOW_WITH / (GLfloat)WINDOW_HEIGHT;

	view = glm::lookAt(cameraPos, cameraFront, cameraUp); 
	projection = glm::perspective(initialFoV, ratio, 0.1f, 100.0f);
}

void Camera::moveCamera(int direction) {
	switch(direction) {
		case 1:
			cameraPos += speed * cameraFront;
			break;
		case 2:
			cameraPos -= speed * cameraFront;
			break;
		case 3: 
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
			break;
		case 4:
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
			break;
		default:
			break;
	}
}

void Camera::handleDeltaTime(GLfloat currentFrame) {
	GLfloat deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	speed = 5.0f * deltaTime;
}

glm::mat4 Camera::getView() {
	return view;
}

glm::mat4 Camera::getProjection() {
	return projection;
}	

void Camera::setRadius(GLfloat rad) {
	radius = rad;
}

GLfloat Camera::getRadius() {
	return radius;
}

static void Camera::callback(GLFWwindow* window, double xpos, double ypos) {
	obj->mouseCallback(window, xpos, ypos);
}

void Camera::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	GLfloat sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

