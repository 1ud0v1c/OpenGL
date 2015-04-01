#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include <map>
#include "camera.h"
#include "gameObject.h"

class Scene {
	public:
		Scene();
		Scene(GLuint programm);
		~Scene();
		void addObject(GameObject *object);
		void draw();
		void makeObject();
		void setType(GLuint type);
		void init(std::map<std::string,GLuint> programms);
		void update(float time,GLFWwindow *window, float dt);
	private:
		std::vector<GameObject*> objects;
		Camera camera;
		std::map<std::string,GLuint> transID;
		std::map<std::string,GLuint> viewID;
		std::map<std::string,GLuint> projID;
		std::map<std::string,GLuint> timeID;
		std::map<std::string,GLuint> programms;
};

#endif
