#ifndef PARTLEVEL_H
#define PARTLEVEL_H

#include "gameObject.h"
#include <map>
#include <vector>
#include <algorithm>

class PartLevel {
	public:
		PartLevel(std::map<std::string,GLuint> programms);
		PartLevel();
		void makePart();
		void setOffset(std::vector< std::vector<glm::vec3> > &offsets);
		void draw();
		void init();
		void initOffset(std::vector< std::vector<glm::vec3> > &offsets);

	private:
		std::map<std::string,GLuint> programms;
		std::vector<glm::vec3> offRoad;
		std::vector<glm::vec3> offBonus;
		std::vector<glm::vec3> offWall;

		std::vector< std::vector<glm::vec3> > offsets;
		std::vector< GameObject* > objects;


};






#endif
