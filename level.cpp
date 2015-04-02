#include "level.h"

Level::Level(std::map<std::string,GLuint> programms) {
	this->programms = programms;
}

Level::Level() {

}

void Level::init() {
	gravity = 9.81f;
	std::vector<float> offset = {-2.0f,0.0f,0.0f};
	player = new Player(gravity);
//	 addObject(new GameSphere("sphere",programms["minimal"],0.25,glm::vec3(1,1,1),offset,"checkerboard.tga"));
	GameObject *wall = new GameObject("wall",programms["minimal"], offset);
	wall->loadOBJ("wall.obj");
	addObject(wall);
}

void Level::addObject(GameObject *object)  {
	objects.push_back(object);
}

std::vector<GameObject*> Level::getObjects() {
	return objects;
}

void Level::update(float time,GLFWwindow *window, float dt) {
	player->update(time,window,dt, objects);
	camera.update(time,window,player->getPos(),player->getDir(), player->getUp());
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
}

Camera Level::getCamera() {
	return camera;
}

Player* Level::getPlayer() {
	return player; 
}

