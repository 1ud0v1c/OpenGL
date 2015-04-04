#ifndef PARTICLE_H
#define PARTICLE_H
#include <GL/glew.h> // must be included before gl.h
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <math.h>
class Particle {
	public:
		Particle(GLuint programm,unsigned int maxParticles, glm::vec3 pos, glm::vec3 color,int cycle);
		void makeObject();
		int getCycle();
		void draw();
		glm::vec3 sphereDirection(double theta, double phi);
		Particle(Particle *p);
		void update(float dt);
		float time;
	private:
		glm::vec3 pos;
		glm::vec3 color;
		GLuint programm;
		float speed;
		float size;
		unsigned int maxParticles;
		GLuint vao;
		int cycle;
		GLuint timeID;
};
#endif
