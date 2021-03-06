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
#define NBPOSITIONS 5

class Player {
	public:
		Player(float gravity,std::map<std::string , GLuint> programms);
		~Player();
		void modifyLives(int value);
		void changePos(double x, double y, double z);
		void update(float time,GLFWwindow *window, float dt, std::vector<GameObject*> objects, int currentLevel, int nbLine);
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
		void updatePos(GLFWwindow *window,float dt, int nbLine);
		void resetPlayer();
		glm::vec3 getOffsetCamera();
		int getCptScoreBonus();

	private:
		int cptScoreBonus = 0;
		int lives;
		double score;
		float speed;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 up;
		glm::vec3 lastTouched;
		float gravity;
		float positions[NBPOSITIONS];
		bool pressed[2];
		int currentPositionIndex;
		std::array<GameObject *,2> playerObject;
		int currentPlayerIndex;
		float timerChangePlayer;
		std::map<std::string , GLuint> programms;
		float invicibleTime;
		bool isInvicible = false;
		float horizontalAngle = 3.14f;
		float verticalAngle = 3.14/8.0f;
		float distance = 10;
		float dy = 0;
		bool isJumping = false;
		glm::vec3 offset;

};
#endif
