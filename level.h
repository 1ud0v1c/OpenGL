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

	private:
		std::map<std::string,GLuint> programms;
		std::vector<GameObject*> objects;
		Player* player;
		Camera camera;
		float gravity;
		int currentLevel;
		int line,column;
		std::vector<int> tabLevel;
};

#endif
