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
	//	Particles* transmitter = new Particles(programms["particle"],new Particle(programms["particle"],100,glm::vec3(3,0,0),glm::vec3(1,0,1),10));
	//	addParticle(transmitter);
	light = Light(programms["minimal"]);
}

void Scene::restart() {
	hud = HUD(programms);
	hud.init(level);
	skybox = Skybox(programms["skybox"], "star-top.tga", "star-bot.tga", "star-left.tga", "star-right.tga", "star-front.tga", "star-back.tga");
	skybox.init();
	light = Light(programms["minimal"]);
	level.resetLevel();
}

void Scene::update(float time,GLFWwindow *window, float dt) {
	if(!isLaunched) {
		if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_R) == GLFW_RELEASE){
			isLaunched = true;
		}
	} 
	else {
		if(!isFinished) {
			if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_R) == GLFW_RELEASE){
				isLaunched = false;
			}
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
			skybox.update(level.getPlayer()->getPos());
			light.update(level.getPlayer()->getPos());
			hud.update(level, dt);

			if(level.getPlayer()->getLives()<=0) {
				isFinished = true;	
				SoundGameEngine::stop();
				SoundGameEngine::play("game_over_evil.ogg",false);
			}
		} else {
			hud.initEnd(level.getPlayer());
		}
	}
}

void Scene::setType(GLuint type) {
	level.setType(type);
}

void Scene::draw(GLFWwindow *window) {
	if(!isLaunched) {
		hud.drawMenu();
	} else if(isFinished) {
		hud.drawMenu();
		if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS && glfwGetKey(window,GLFW_KEY_R) == GLFW_RELEASE){
			isFinished = false;
			restart();
		}
	}else {
		light.draw();
		level.draw();
		skybox.draw();
		hud.draw();
	}
}

void Scene::makeObject() {
	level.makeObject();
}

Scene::~Scene() {

}
