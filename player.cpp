#include "player.h"

Player::Player(float gravity, std::map<std::string , GLuint> programms) {
	lives = 3;
	score = 0;
	speed = 3.0f;
	this->programms = programms;

	std::vector<glm::vec3> offsetVect;
	offsetVect.push_back(glm::vec3(0.0f,-1.0f,-1.0f));
	playerObject = new GameSphere("sphere",programms["player"],0.25,glm::vec3(1,1,1),offsetVect,"checkerboard.tga");
	this->gravity = gravity;
	direction = glm::vec3( cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle) );
	this->offset = offsetVect[0];
}

glm::vec3 Player::getOffset() {
	return offset;
}

void Player::init() {
	glUseProgram(programms["player"]);
	playerObject->makeObject();
	glUseProgram(0);
}

void Player::movePlayer() {
	playerObject->moveObject(position);	
}

void Player::draw() {

	glUseProgram(programms["player"]);
	playerObject->draw();

	glUseProgram(0);
}

void Player::update(float time,GLFWwindow *window, float dt, std::vector<GameObject*> &objects){


	float initialFoV = 45.0f;
	double xpos, ypos;

	float mouseSpeed = 0.009f;
	static double lastTime = glfwGetTime();
	glfwGetCursorPos(window, &xpos, &ypos);
	double currentTime = glfwGetTime();
	glfwSetCursorPos(window, 1024/2, 768/2);
	horizontalAngle += mouseSpeed * dt * float(1024/2 - xpos );
	verticalAngle += mouseSpeed * dt * float( 768/2 - ypos );


	direction=	 glm::vec3(
			  3*cos(verticalAngle) * sin(horizontalAngle),
			  3*sin(verticalAngle),
			  3*cos(verticalAngle) * cos(horizontalAngle)
			  );

	glm::vec3 right = glm::vec3(
			  sin(horizontalAngle - 3.14f/2.0f),
			  0,
			  cos(horizontalAngle - 3.14f/2.0f)
			  );

	up = glm::cross( right, direction );
	if (glfwGetKey( window,GLFW_KEY_UP ) == GLFW_PRESS){
		position -= direction * dt * speed;
	}
	// Move backward
	if (glfwGetKey( window,GLFW_KEY_DOWN ) == GLFW_PRESS){
		position += direction * dt * speed;
	}
	// Strafe right
	if (glfwGetKey( window,GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position -= right * dt * speed*2.0f;
	}
	// Strafe left
	if (glfwGetKey( window,GLFW_KEY_LEFT ) == GLFW_PRESS){
		position += right * dt * speed*2.0f;
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isJumping == false) {
		isJumping = true;
		dy = 10;
	}

	dy -= gravity*dt;
	position.y +=dy*dt;

	if(position.y <0) {
		position.y = 0;
		isJumping = false;
	}
	movePlayer();
}

int Player::getLives(){
	return lives;
}

void Player::modifyLives(int value){
	lives += value;
}

void Player::modifyScore(double value){
	score += value;
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

