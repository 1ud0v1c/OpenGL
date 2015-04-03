#ifndef GAME_SPHERE_H
#define GAME_SPHERE_H

#include "gameObject.h"

class GameSphere : public GameObject {
	public:
		GameSphere(const std::string &name,GLuint &programm, double R, glm::vec3 color, std::vector<glm::vec3> &offset, const std::string t="");
		~GameSphere();
		void makeObject();
		void draw();
		glm::vec3 spherePoint(double theta, double phi, double R);

	private:
		double R;
		glm::vec3 colorValue;
};

#endif
