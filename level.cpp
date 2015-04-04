#include <iostream>
#include "level.h"

Level::Level(std::map<std::string,GLuint> programms) {
	this->programms = programms;
}

Level::Level() {

}

void Level::loadLevel(const std::string path) {
	std::ifstream data_input; 
	data_input.open(path);
	double d;

	std::vector<double> v;
	data_input >> line;
	data_input >> column;
	while (data_input >> d) { 
		tabLevel.push_back(d); 
	} 


}

void Level::init() {
	currentLevel = 0;
	gravity = 9.81f;
	std::vector<glm::vec3> offsetRoad;
	offsetRoad.push_back(glm::vec3(0.0f,-2.0f,0.0f));
	offsetRoad.push_back(glm::vec3(0.0f,-2.0f,4.4f));
	offsetRoad.push_back(glm::vec3(0.0f,-2.0f,8.8f));

	std::vector<glm::vec3> offset;
	offset.push_back(glm::vec3(0.0f,-1.0f,0.0f));
	offset.push_back(glm::vec3(0.0f,-1.0f,4.4f));
//	offset.push_back(glm::vec3(0.0f,-1.0f,8.8f));

	loadLevel("./level/level0.txt");

/*	int j = 0;
	int i=0;
	for(auto pos : tabLevel) {
		if(pos==1) {
			offset.push_back(glm::vec3(-178.0f/2 + j*178/15,-1.0f,4.4f*i));
		}
		j++;

		if(j==column) {
			i++;
			j=0;
		}
	}*/

	player = new Player(gravity,programms);
	player->init();
	GameObject *wall = new GameObject("wall",programms["minimal"], offset, "brick2.tga");
	wall->loadOBJ("wall.obj");
	addObject(wall);

	GameObject *road = new GameObject("road",programms["minimal"], offsetRoad,"roat_texture_256.tga");
	road->loadOBJ("road.obj");
	addObject(road);


}

void Level::addObject(GameObject *object)  {
	objects.push_back(object);
}

std::vector<GameObject*> Level::getObjects() {
	return objects;
}

void Level::update(float time,GLFWwindow *window, float dt) {
	player->update(time,window,dt, objects);
	camera.update(time,window,player->getPos(),player->getDir(), player->getUp(), player->getOffset());
}

void Level::setType(GLuint type) {
	for(auto o : objects) {
		o->setType(type);
	}
}


void Level::makeObject() {
	for(auto o : objects) {
		o->makeObject();
	}
}

void Level::draw() {
	glUseProgram(programms["minimal"]);
	//	light.draw();
	glUseProgram(0);
	for(auto o : objects) {
		glUseProgram(o->getProgramm());
		o->draw();
		glUseProgram(0);
	}
	player->draw();
}

Camera Level::getCamera() {
	return camera;
}

Player* Level::getPlayer() {
	return player; 
}

