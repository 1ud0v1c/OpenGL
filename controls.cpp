#include "controls.h"

Controls::Controls(GLFWwindow* win, Camera* cam) {
	window = win;
	camera = cam;
}


int Controls::handleActions() {
	int running = 1;
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
		running = 0;
	}
	if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
		camera->setRadius(camera->getRadius()-0.05);
	}
	if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->setRadius(camera->getRadius()+0.05);
	}
	if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera->setRadius(camera->getRadius()-0.05);
	}
	if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera->setRadius(camera->getRadius()+0.05);
	}

	if(glfwGetKey(window,GLFW_KEY_L) == GLFW_PRESS) {
		if(isWireframeActive) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			isWireframeActive = false;
		} else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			isWireframeActive = true;
		}
	}
	return running;
}
