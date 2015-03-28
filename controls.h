#ifndef CONTROLS_H
#define CONTROLS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glfwMinimal.h"
#include "camera.h"
#include "timer.h"

class Controls {
	public:
		Controls(GLFWwindow* win, Camera* cam, bool hideCursor);
		int handleActions(GLfloat currentFrame);
		void getCurrentFPS();

	private:
		bool isWireframeActive;
		Camera *camera;
		GLFWwindow *window;
		Timer timer;
};

#endif
