#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>
#include <irrKlang.h>
#include "camera.h"
#include "level.h"
#include "gameObject.h"
#include "hud.h"
#include "skybox.h"
#include "player.h"
#include "particles.h"
#include "light.h"

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
		void addParticle(Particles* particle);
		bool isOver();
	
	private:
		Camera camera;
		HUD hud;
		std::vector<GameObject*> objects;
		std::vector<Particles*> particlesTransmitter;
		std::map<std::string,GLuint> transID;
		std::map<std::string,GLuint> viewID;
		std::map<std::string,GLuint> projID;
		std::map<std::string,GLuint> timeID;
		std::map<std::string,GLuint> programms;
		Level level;
		Skybox skybox;
		ISoundEngine *soundEngine;
		Light light;

};

#endif
