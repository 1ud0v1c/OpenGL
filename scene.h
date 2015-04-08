#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include "camera.h"
#include "level.h"
#include "gameObject.h"
#include "hud.h"
#include "skybox.h"
#include "player.h"
#include "light.h"


class Scene {
	public:
		Scene();
		Scene(GLuint programm);
		~Scene();
		void draw(GLFWwindow *window);
		void makeObject();
		void setType(GLuint type);
		void restart();
		void init(std::map<std::string,GLuint> programms) ;
		void update(float time,GLFWwindow *window, float dt);
	
	private:
		Camera camera;
		HUD hud;
		std::vector<GameObject*> objects;
		std::map<std::string,GLuint> transID;
		std::map<std::string,GLuint> viewID;
		std::map<std::string,GLuint> projID;
		std::map<std::string,GLuint> timeID;
		std::map<std::string,GLuint> programms;
		Level level;
		Skybox skybox;
		Light light;
		bool isLaunched = false;
		bool isFinished = false;

};

#endif
