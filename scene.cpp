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
     hud = HUD(programms);
	 hud.init(level);
	 skybox = Skybox(programms["skybox"], "star-top.tga", "star-bot.tga", "star-left.tga", "star-right.tga", "star-front.tga", "star-back.tga");
	 skybox.init();
	 ///	light = Light(programms["minimal"]);
}



void Scene::update(float time,GLFWwindow *window, float dt) {
	level.update(time,window,dt);
	Camera camera = level.getCamera();
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
	hud.update(level, dt);
	skybox.update(level.getPlayer()->getPos());
}

void Scene::setType(GLuint type) {
	level.setType(type);
}

void Scene::draw() {
	level.draw();
	hud.draw();
	skybox.draw();
}

void Scene::makeObject() {
	level.makeObject();
}

Player* Scene::getPlayer(){
	return level.getPlayer();
}

Scene::~Scene() {

}
