#ifndef CONTROLS_H
#define CONTROLS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glfwMinimal.h"
#include "camera.h"

class Controls {
	public:
		Controls(GLFWwindow* win, Camera* cam, bool hideCursor);
		int handleActions(GLfloat currentFrame);

	private:
		bool isWireframeActive;
		Camera *camera;
		GLFWwindow *window;
};

#endif
