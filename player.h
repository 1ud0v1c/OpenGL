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
#include "soundGameEngine.h"

class Player {
	public:
		Player(float gravity,std::map<std::string , GLuint> programms);
		~Player();
		void modifyLives(int value);
		void changePos(double x, double y, double z);
		void update(float time,GLFWwindow *window, float dt, std::vector<GameObject*> &objects );
		void init();
		void movePlayer();
		void draw();
		glm::vec3 getOffset();
		glm::vec3 getPos();
		glm::vec3 getLastTouched();
		int getLives();
		double getScore();
		glm::vec3 getUp();
		glm::vec3 getDir();
		void updatePos(GLFWwindow *window,float dt);


	private:
		int lives;
		double score;
		float speed;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 up;
		glm::vec3 lastTouched;
		float gravity;
		float positions[3];
		bool pressed[2];
		int currentPositionIndex;
		GameObject *playerObject;
		std::map<std::string , GLuint> programms;
		float invicibleTime;
		bool isInvicible = false;
		float horizontalAngle = 3.14f;
		float verticalAngle = 0.0f;
		float initialFoV = 45.0f;
		float dy = 0;
		bool isJumping = false;
		bool isMovingAuto = false;
		bool pressR = false;
		glm::vec3 offset;
};
#endif
