#include <iostream>
#include "level.h"

Level::Level(std::map<std::string,GLuint> programms) {
	this->programms = programms;
	currentPart = 0;
	numberOfChange = 0;
	nextPart = 0;
	for(int i=0;i<parts.size();i++) {
		parts[i] = PartLevel(programms);
	}
	lastTouched = glm::vec3(0,0,0);
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

void Level::loadNextPart() {
	currentPart = nextPart;
	nextPart++;
	numberOfChange++;

	if(nextPart==3) nextPart = 0;


	std::vector<glm::vec3> offset;
	std::vector<glm::vec3> offsetRoad;
	offsetRoad.push_back(glm::vec3(0.0f,-2.0f,numberOfChange*sizeRoad));
	offsetRoad.push_back(glm::vec3(4.4f,-2.0f,numberOfChange*sizeRoad));
	offsetRoad.push_back(glm::vec3(8.8f,-2.0f,numberOfChange*sizeRoad));
	std::vector<glm::vec3> offsetBonus;




	int j = 0;
	int i=0;
	for(auto pos : tabLevel) {
		if(pos==1) {
			offset.push_back(glm::vec3(4.4f*i+1.0f,-1.0f, -sizeRoad/2+j*sizeRoad/column+sizeRoad*numberOfChange));
		}
		j++;

		if(j==column) {
			i++;
			j=0;
		}
	}

	for(auto pos : tabLevel) {
		if(pos==0) {
			offsetBonus.push_back(glm::vec3(i*5-16,-1.0f,-sizeRoad/2 + j*sizeRoad/column+sizeRoad*numberOfChange));
		}
		j++;

		if(j==column) {
			i++;
			j=0;
		}
	}


		std::map<std::string, std::vector<glm::vec3> > offsets;
	offsets["wall"] = offset;
	offsets["road"] = offsetRoad;
	offsets["bonus"] = offsetBonus;

	parts[nextPart].setOffset(offsets);

	parts[nextPart].makePart();
	Particles* transmitter = new Particles(programms["particle"],new Particle(programms["particle"],100,offset[0],glm::vec3(1,0,1),10));
	addParticle(transmitter);


	parts[currentPart].makePart();
}

void Level::init() {
	currentLevel = 0;
	gravity = 9.81f;
	std::vector<glm::vec3> offsetRoad;
	offsetRoad.push_back(glm::vec3(0.0f,-2.0f,0.0f));
	offsetRoad.push_back(glm::vec3(4.4f,-2.0f,0.0f));
	offsetRoad.push_back(glm::vec3(8.8f,-2.0f,0.0f));

	std::vector<glm::vec3> offset;

	loadLevel("./level/level0.txt");

	int j = 0;
	int i=0;
	for(auto pos : tabLevel) {
		if(pos==1) {
			offset.push_back(glm::vec3(4.4f*i+1.0f,-1.0f,-sizeRoad/2 + j*sizeRoad/column));
		}
		j++;

		if(j==column) {
			i++;
			j=0;
		}
	}

	std::vector<glm::vec3> offsetBonus;

	for(auto pos : tabLevel) {
		if(pos==0) {
			offsetBonus.push_back(glm::vec3(i*5-16,-1.0f,-sizeRoad/2 + j*sizeRoad/column+sizeRoad*numberOfChange));
		}
		j++;

		if(j==column) {
			i++;
			j=0;
		}
	}

	
	player = new Player(gravity*10,programms);
	player->init();



		std::map<std::string, std::vector<glm::vec3> > offsets;
	offsets["wall"] = offset;
	offsets["road"] = offsetRoad;
	offsets["bonus"] = offsetBonus;

	for(int i=0;i<parts.size();i++) {

		parts[i].init();

	}
	parts[currentPart].setOffset(offsets);
	parts[currentPart].makePart();
	loadNextPart();

}

void Level::addObject(GameObject *object,int part)  {
//	partLevel[part].push_back(object);
}

std::vector<GameObject*> Level::getObjects() {
	return objects;
}

void Level::update(float time,GLFWwindow *window, float dt) {
	player->update(time,window,dt, parts[currentPart].getVector());
	glm::vec3 touched = player->getLastTouched();
	if (touched.x != lastTouched.x && touched.y != lastTouched.y && touched.z != lastTouched.z){
		std::cout << "COUCOU" << std::endl;
		lastTouched = touched;
		particlesTransmitter[0]->setPosition(lastTouched);

	}
	camera.update(time,window,player->getPos(),player->getDir(), player->getUp(), player->getOffset());
	if(player->getPos().z > numberOfChange*sizeRoad-sizeRoad/2) {
		loadNextPart();
	}
	for(Particles* particles : particlesTransmitter){
		particles->update(dt);
	}
}

void Level::setType(GLuint type) {
/*	for(auto o : parts) {
>>>>>>> cb5e8b15a610b08e1b18aa9558942c44473ceabc
		o->setType(type);
	}*/
}

void Level::makeObject(int part) {

		parts[part].makePart();
	for(Particles* particles : particlesTransmitter){
		particles->make();
	}
}


void Level::makeObject() {

		parts[currentPart].makePart();

	for(Particles* particles : particlesTransmitter){
		particles->make();
	}
}

void Level::draw() {
	glUseProgram(programms["minimal"]);
	//	light.draw();
	glUseProgram(0);
	parts[currentPart].draw();
	glUseProgram(0);
	parts[nextPart].draw();
	glUseProgram(0);


	player->draw();
	for(Particles* particles : particlesTransmitter){
		particles->draw();
	}

}

void Level::addParticle(Particles* particles){
	particlesTransmitter.push_back(particles);
}


Camera Level::getCamera() {
	return camera;
}

Player* Level::getPlayer() {
	return player; 
}

