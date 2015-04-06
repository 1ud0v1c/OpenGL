#include "partLevel.h"

PartLevel::PartLevel() {
}

PartLevel::PartLevel(std::map<std::string,GLuint> programms) {
	this->programms = programms;

}

void PartLevel::initOffset(std::vector< std::vector<glm::vec3> > &offsets) {
	std::copy(offsets.begin(),offsets.end(),this->offsets.begin());
}

void PartLevel::init() {

	GameObject* wall = new GameObject("wall",programms["minimal"], offWall, "brick2.tga",false);
	wall->loadOBJ("wall.obj");

	GameObject* road = new GameObject("road",programms["minimal"], offRoad,"roat_texture_256.tga",false,glm::pi<float>()*90/180);
	road->loadOBJ("road.obj");


	GameObject* bonus = new GameObject("bonusScore",programms["minimal"], offBonus, "brick2.tga",false);
	bonus->loadOBJ("bonus_score.obj");

	objects.push_back(wall);
	objects.push_back(road);
	objects.push_back(bonus);


}



void PartLevel::setOffset(std::vector< std::vector<glm::vec3> > &offsets) {

	std::copy(offsets.begin(),offsets.end(),this->offsets.begin());
	int i=0;
	for(auto off : this->offsets) {
		objects[i]->setOffset(off);
		i++;
	}
}


void PartLevel::makePart() {
	for(auto o : objects) {
		o->makeObject();
	}
}

void PartLevel::draw() {

	for(auto o : objects) {
		o->draw();
	}
}
