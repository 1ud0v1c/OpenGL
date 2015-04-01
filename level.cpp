#include "level.h"

Level::Level(std::map<std::string,GLuint> programms) {
	this->programms = programms;
}

Level::Level() {

}

void Level::init() {

	std::vector<float> offset = {-2.0f,0.0f,0.0f};
	player = new Player();
	addObject(new GameSphere("sphere",programms["minimal"],0.25,glm::vec3(1,1,1),offset,"checkerboard.tga"));
}

void Level::addObject(GameObject *object)  {
	objects.push_back(object);
}

void Level::update(float time,GLFWwindow *window, float dt) {
	player->update(time,window,dt);
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
