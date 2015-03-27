#include "controls.h"

Controls::Controls(GLFWwindow* win, Camera* cam, bool hideCursor) {
	window = win;
	camera = cam;
	if(hideCursor) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}


int Controls::handleActions() {
	int running = 1;
	if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS){
		running = 0;
	}
	if(glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS) {
		camera->moveCamera(1);
	}
	if(glfwGetKey(window,GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->moveCamera(2);
	}
	if(glfwGetKey(window,GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera->moveCamera(3);
	}
	if(glfwGetKey(window,GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera->moveCamera(4);
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
