#include "player.h"

Player::Player(float gravity, std::map<std::string , GLuint> programms) {
	lives = 3;
	score = 0;
	speed = 10.0f;
	invicibleTime = 0;
	this->programms = programms;
	lastTouched = glm::vec3(0,0,0);

	std::vector<glm::vec3> offsetVect;
	offsetVect.push_back(glm::vec3(1.0f,-2.0f,0.0f));
	//   playerObject = new GameSphere("sphere",programms["player"],0.25,glm::vec3(1,1,1),offsetVect,"checkerboard.tga",true);
	int i = 0;
	for(auto &object: playerObject){ 
		object = new GameObject("player",programms["player"], offsetVect,"roat_texture_256.tga",true);
		object->loadOBJ("character/character" + std::to_string(i) + ".obj");
		i++;
	}
	currentPlayerIndex = 0;
	timerChangePlayer = 0;
	this->gravity = gravity;
	direction = glm::vec3( cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle) );
	this->offset = offsetVect[0];
	currentPositionIndex = 0;

	for(int i=0;i<NBPOSITIONS;i++)
		positions[i] = 4.4f*i;
	pressed[0] = false;
	pressed[1] = false;
}

glm::vec3 Player::getOffset() {
	return offset;
}


glm::vec3 Player::getOffsetCamera() {
	return offset;
}

void Player::init() {
	glUseProgram(programms["player"]);
	for(auto &object: playerObject){ 
		object->makeObject();
	}
	glUseProgram(0);
}

void Player::movePlayer() {
	playerObject[currentPlayerIndex]->moveObject(position);	
}


void Player::resetPlayer() {
	offset = glm::vec3(0,0,0);
	position = glm::vec3(0,0,0);
	lives = 3;
	score = 0;
}


void Player::draw() {
	glUseProgram(programms["player"]);
	playerObject[currentPlayerIndex]->draw();
	glUseProgram(0);
}

void Player::update(float time,GLFWwindow *window, float dt, std::vector<GameObject*> objects, int currentLevel, int nbLine){
	timerChangePlayer+=dt;
	if(timerChangePlayer > 0.033){
		currentPlayerIndex++;
		currentPlayerIndex = currentPlayerIndex%(playerObject.size());
		timerChangePlayer = 0;
	}

	score += dt*(currentLevel*currentLevel)*speed/3;

	updatePos(window,dt,nbLine);
	if(invicibleTime < 1 && isInvicible==true) {
		invicibleTime += dt;
	}else {
		isInvicible = false;
		invicibleTime = 0;
	}

	int index = 0;
	for(auto object : objects) {
		if(object->getName()!="road") {
			if(playerObject[currentPlayerIndex]->isColliding(object)) {
				float x = position.x;
				float maxY = 10000.0f;
				float maxZ = 10000.0f;

				if(object->getName() == "wall" && isInvicible==false) {
					SoundGameEngine::play("../resources/sounds/hit_wall.ogg",false);
					lives -= 1;
					isInvicible = true;
				} else {
					if(object->getName() == "bonusLife") {
						lives += 1;
					} else if(object->getName() == "bonusScore") {
						score += 250.0;
						cptScoreBonus++;
					}else if(object->getName() == "bonusSpeed"){
						speed += 1.0f;
					}

					std::vector<glm::vec3> offsets = object->getOffset(x);

					if (offsets.size() != 0){
						int index=0;

						for (int i=0; i<offsets.size(); i++){
							if (glm::abs(offsets[i].y-position.y) < maxY && glm::abs(offsets[i].z-position.z) < maxZ){
								maxY = offsets[i].y;
								maxZ = offsets[i].z;
								index = i;
							}
						}
						lastTouched = offsets[index];
						object->removeOffset(lastTouched);
						object->resetVBO();
					SoundGameEngine::play("../resources/sounds/bonus2.ogg",false, false, true, 0.5f);
					}
				}
			} 	 
		}
		index++;
	}
	movePlayer();
}

int Player::getLives(){
	return lives;
}

glm::vec3 Player::getLastTouched(){
	return lastTouched;
}

void Player::updatePos(GLFWwindow *window,float dt,int nbLine) {

	float initialFoV = 45.0f;
	double xpos, ypos;

	float mouseSpeed = 0.009f;
	static double lastTime = glfwGetTime();
	glfwGetCursorPos(window, &xpos, &ypos);
	double currentTime = glfwGetTime();
	glfwSetCursorPos(window, 1024/2, 768/2);
	horizontalAngle += mouseSpeed * dt * float(1024/2 - xpos );
	verticalAngle += mouseSpeed * dt * float( 768/2 - ypos );

	direction = glm::vec3(0,0,-3);

	glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f)
			);

	bool stillPressed = false;
	if (glfwGetKey( window,GLFW_KEY_UP ) == GLFW_PRESS){
		stillPressed = true;
		distance += 0.8; 
		if(distance > 20) {
			distance = 20;
		}
		speed += 1; 
		if(speed > 20) {
			speed = 20;
		}
	}

	if(!stillPressed) {
		distance -= 0.2;
		if(distance < 10) {
			distance = 10;
		}
	}

	// Move backward
	if (glfwGetKey( window,GLFW_KEY_DOWN ) == GLFW_PRESS){
		speed -= 1;
		if(speed < 3) {
			speed = 3;
		}
	}
	if(currentPositionIndex+1>nbLine){
		currentPositionIndex = nbLine-1;
		lives--;
	}

	// Strafe right
	if (glfwGetKey( window,GLFW_KEY_RIGHT ) == GLFW_PRESS && glfwGetKey( window,GLFW_KEY_RIGHT ) == GLFW_RELEASE){
		currentPositionIndex--;
		if(currentPositionIndex < 0){
			currentPositionIndex = 0;
		}
	}
	// Strafe left
	if (glfwGetKey( window,GLFW_KEY_LEFT ) == GLFW_PRESS && glfwGetKey( window,GLFW_KEY_LEFT ) == GLFW_RELEASE ){
		currentPositionIndex++;
		if(currentPositionIndex > nbLine-1){
			currentPositionIndex = nbLine-1;
		}
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isJumping == false) {
		isJumping = true;
		dy = 25;
	}

		position = glm::vec3(positions[currentPositionIndex],position.y,position.z);
	position -= direction * dt * speed;


	direction=	 glm::vec3(
			distance*cos(verticalAngle) * sin(horizontalAngle),
			distance*sin(verticalAngle),
			distance*cos(verticalAngle) * cos(horizontalAngle)
			);

	right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f)
			);

	up = glm::cross( right, direction );

	dy -= gravity*dt;
	position.y +=dy*dt;

	if(position.y <0) {
		position.y = 0;
		isJumping = false;
	}

	if(position.x<0) position.x=0;
	if(position.x>8.8) position.x = 8.8f;
}

double Player::getScore(){
	return score;
}

void Player::modifyLives(int value){
	lives += value;
}


void Player::changePos(double x, double y, double z){
	position.x += x;
	position.y += y;
	position.z += z;
}

glm::vec3 Player::getPos(){
	return position;
}

glm::vec3 Player::getDir() {
	return direction;
}

glm::vec3 Player::getUp() {
	return up;
}

int Player::getCptScoreBonus() {
	return cptScoreBonus;
}
