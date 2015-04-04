#ifndef PARTICLES_H
#define PARTICLES_H
#include <vector>
#include "particle.h"
class Particles {
	public:
		Particles();
		Particles(GLuint programm,Particle *particle);
		void make();
		void update(float dt);
		void draw();
		void addParticle(Particle *particle);
		void redraw();
	private:
		std::vector<Particle*> particles;
		float x,y;
		GLuint programm;
		int cycle;
		float frequency;
		float timer;
};
#endif
