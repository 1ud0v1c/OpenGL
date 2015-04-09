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
		void setOffset( std::map<std::string, std::vector<glm::vec3> > &offsets);
		void draw();
		void init();
		void initOffset(std::map<std::string, std::vector<glm::vec3> > &offsets);
		std::vector<GameObject*> getVector();
		int line;
		void resetVBO();

	private:
		std::map<std::string,GLuint> programms;
		std::map<std::string, GameObject*> objects;
		std::map<std::string, std::vector<glm::vec3> > offsets;


};






#endif
