#include "scene.h"

Scene::Scene() {
}

void Scene::init(std::map<std::string,GLuint> programms) {
	this->programms = programms;
	for( auto programm : programms) {
		glUseProgram(programm.second);
		transID[programm.first] = (glGetUniformLocation(programm.second, "trans"));
		viewID[programm.first] = (glGetUniformLocation(programm.second, "view"));
		projID[programm.first] = (glGetUniformLocation(programm.second, "proj"));
		timeID[programm.first] = (glGetUniformLocation(programm.second, "time"));
	}
	level = Level(programms);
	level.init();
//	light = Light(programms["minimal"]);
}

void Scene::update(float time,GLFWwindow *window, float dt) {
	camera.update(time,window);
	glm::mat4 proj = camera.getProjection();
	glm::mat4 view = camera.getView();
	glm::mat4 ModelMatrix = glm::mat4(1.0);
	for(auto programm : programms) {
		glUseProgram(programm.second);
		glUniformMatrix4fv(transID[programm.first], 1, GL_FALSE, glm::value_ptr(ModelMatrix));
		glUniformMatrix4fv(viewID[programm.first], 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projID[programm.first], 1, GL_FALSE, glm::value_ptr(proj));
	}
	glUseProgram(programms["minimal"]);
	glUniform1f(timeID["minimal"],time);
}

Scene::~Scene() {
}

void Scene::setType(GLuint type) {
		level.setType(type);
}

void Scene::draw() {
	level.draw();
}

void Scene::makeObject() {
	level.makeObject();
}

/*GamePlayer* Scene::getPlayer(){
     for (auto object : objects){
	  if (object->getName() == "Player"){
	       return dynamic_cast<GamePlayer*>(object);
	  }
     }
}*/