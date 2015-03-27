#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "camera.h"

void Camera::update() {
	float ratio = (GLfloat)WINDOW_WITH / (GLfloat)WINDOW_HEIGHT;
	camX = sin(glfwGetTime())*radius;
	camZ = cos(glfwGetTime())*radius;

	cameraPos    =  glm::vec3(camX, 0.0f, camZ);
	cameraFront  =  glm::vec3(0.0f, 0.0f, 0.0f);
	cameraUp     =  glm::vec3(0.0f, 1.0f,  0.0f);

	view = glm::lookAt(cameraPos, cameraFront, cameraUp); 
	projection = glm::perspective(initialFoV, ratio, 0.1f, 100.0f);
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

GLfloat Camera::getCamX(){
	return camX;
}

GLfloat Camera::getCamZ(){
	return camZ;
}
