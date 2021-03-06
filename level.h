#ifndef LEVEL_H
#define LEVEL_H

#include "gameObject.h"
#include <map>
#include "gameSphere.h"
#include "player.h"
#include "camera.h"
#include "particles.h"
#include "gameCube.h"
#include "partLevel.h"
#include <iostream>
#include <vector>
#include <array>
#include "partLevel.h"

class Level {
	public:
		Level();
		Level(std::map<std::string,GLuint> programms);
		void makeObject();
		void draw();
		void init();
		void update(float time,GLFWwindow *window, float dt);
		void addObject(GameObject *o, int part);
		void setType(GLuint type);
		std::vector<GameObject*> getObjects();
		Camera getCamera();
		Player* getPlayer();
		void loadLevel(const std::string path);
		void loadNextPart();
		int getCurrentLevel();
		void makeObject(int part);
		void addParticle(Particles* particle);
		void resetLevel();

	private:
		std::map<std::string,GLuint> programms;
		std::vector<Particles*> particlesTransmitter;
		std::vector<GameObject*> objects;
		std::array <PartLevel,3 > parts;
		glm::vec3 lastTouched;
		Player* player;
		Camera camera;
		float gravity;
		int currentLevel;
		int currentLevelFile;
		int currentPart;
		int nextPart;
		int numberOfChange;
		int line,column;
		float sizeRoad = 117.2f*2;
		std::vector<int> tabLevel;
		GameObject *road;
		GameObject *bonus;
		GameObject *wall;

};

#endif
