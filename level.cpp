#include <iostream>
#include "level.h"

Level::Level(std::map<std::string,GLuint> programms) {
	this->programms = programms;
}

Level::Level() {

}

void loadLevel() {

}

void Level::init() {
	currentLevel = 0;
	gravity = 9.81f;
	std::vector<glm::vec3> offset;
	offset.push_back(glm::vec3(0.0f,-2.0f,0.0f));
	offset.push_back(glm::vec3(0.0f,-2.0f,4.4f));
	offset.push_back(glm::vec3(0.0f,-2.0f,8.8f));

	player = new Player(gravity,programms);
	player->init();
	addObject(new GameSphere("sphere",programms["minimal"],0.25,glm::vec3(1,1,1),offset,"checkerboard.tga"));
	GameObject *wall = new GameObject("wall",programms["minimal"], offset, "brick2.tga");
	wall->loadOBJ("wall.obj");
	addObject(wall);

	GameObject *road = new GameObject("road",programms["minimal"], offset,"roat_texture_256.tga");
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
	/*     GameObject* temp = objects[0];
	       for (GameObject* obj : objects){
	       if (obj->getName() != temp->getName()){
	       if(obj->isColliding(temp)){
	       std::cout << "yay ! " << obj->getName() << " (" << obj->getRadius() << ") - " <<temp->getName() << "(" << temp->getRadius() << ")" << std::endl;
	       }else {
	       std::cout << "no :( " << obj->getName() << "(" <<  obj->getRadius() 
	       << " - (" << obj->getCenter().x << " " << obj->getCenter().y << " " << obj->getCenter().z << ")"
	       << ") - " <<temp->getName() << "("  << temp->getRadius() 
	       << " - (" << temp->getCenter().x << " " << temp->getCenter().y << " " << temp->getCenter().z << ")"
	       << ")" << std::endl;
	       }

	       }
	       temp = obj;
	       }*/
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

