#ifndef LEVEL_H
#define LEVEL_H

#include "gameObject.h"
#include <map>
#include "gameSphere.h"
#include "player.h"
#include "camera.h"
#include "gameCube.h"
#include <iostream>
#include <vector>
#include <array>
#include <irrKlang.h>
using namespace irrklang;

class Level {
	public:
		Level();
		Level(std::map<std::string,GLuint> programms);
		void makeObject();
		void draw();
		void init();
		void update(float time,GLFWwindow *window, float dt);
		void addObject(GameObject *o);
		void setType(GLuint type);
		std::vector<GameObject*> getObjects();
		Camera getCamera();
		Player* getPlayer();
		void loadLevel(const std::string path);
		void nextPart();

	private:
		std::map<std::string,GLuint> programms;
		std::vector<GameObject*> objects;
		std::array < std::vector<GameObject*>,3 > partLevel;
		Player* player;
		Camera camera;
		float gravity;
		int currentLevel;
		int currentPart;
		int numberOfChange;
		int line,column;
		std::vector<int> tabLevel;
};

#endif
