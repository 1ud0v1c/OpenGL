#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include "camera.h"
#include "level.h"
#include "gameObject.h"
#include "hud.h"
#include "skybox.h"
#include <irrKlang.h>
using namespace irrklang;

class Scene {
	public:
		Scene();
		Scene(GLuint programm);
		~Scene();
		void draw();
		void makeObject();
		void setType(GLuint type);
		void init(std::map<std::string,GLuint> programms, ISoundEngine *soundEngine);
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
		ISoundEngine *soundEngine;

};

#endif
