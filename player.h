#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <iostream>
#include "gameObject.h"
#include "gameSphere.h"
#include <map>

class Player {
	public:
		Player(float gravity,std::map<std::string , GLuint> programms);
		~Player();
		int getLives();
		void modifyLives(int value);
		void modifyScore(double value);
		void changePos(double x, double y, double z);
		glm::vec3 getPos();
		void update(float time,GLFWwindow *window, float dt, std::vector<GameObject*> &objects );
		glm::vec3 getUp();
		glm::vec3 getDir();
		void init();
		void movePlayer();
		void draw();
		glm::vec3 getOffset();

	private:
		int lives;
		double score;
		float speed;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 up;
		float gravity;
		GameObject *playerObject;
		std::map<std::string , GLuint> programms;

		float horizontalAngle = 3.14f;
		float verticalAngle = 0.0f;
		float initialFoV = 45.0f;
		float dy = 0;
		bool isJumping = false;
		glm::vec3 offset;
};
#endif
