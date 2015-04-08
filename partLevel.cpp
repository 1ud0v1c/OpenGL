#include "partLevel.h"

PartLevel::PartLevel() {
}

PartLevel::PartLevel(std::map<std::string,GLuint> programms) {
	this->programms = programms;

}

void PartLevel::initOffset(std::map<std::string, std::vector<glm::vec3> >  &offsets) {
	this->offsets = offsets;
}

void PartLevel::init() {

	std::vector<glm::vec3> offWall(0);
	std::vector<glm::vec3> offRoad(0);
	std::vector<glm::vec3> offBonus(0);

	GameObject* wall = new GameObject("wall",programms["minimal"], offWall, "brick2.tga",false);
	wall->loadOBJ("wall.obj");

	GameObject* road = new GameObject("road",programms["minimal"], offRoad,"roat_texture_256.tga",false,glm::pi<float>()*90/180);
	road->loadOBJ("road.obj");


	GameObject* bonus = new GameObject("bonusScore",programms["minimal"], offBonus, "rainbowTexture.tga",false);
	bonus->loadOBJ("sphere.obj");

	objects["wall"] = wall;
	objects["road"] = road;
	objects["bonus"] = bonus;

}



void PartLevel::setOffset(	std::map<std::string, std::vector<glm::vec3> > &offsets) {

	this->offsets = offsets;

	for(auto &object : objects) {
		object.second->setOffset(this->offsets[object.first]); 
	}
}


std::vector<GameObject*> PartLevel::getVector() {
	std::vector<GameObject*> o;
	for(auto object : objects) {
		o.push_back(object.second);
	}
	return o;
}

void PartLevel::resetVBO(){
	for (auto object : objects){
		object.second->resetVBO();
	}

}

void PartLevel::makePart() {
	for(auto o : objects) {
		glUseProgram(o.second->getProgramm());
		o.second->makeObject();
	}
}

void PartLevel::draw() {

	for(auto o : objects) {
		glUseProgram(o.second->getProgramm());
		o.second->draw();
	}
}
