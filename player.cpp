#include "player.h"

Player::Player(float gravity, std::map<std::string , GLuint> programms) {
     lives = 100;
     score = 0;
     speed = 10.0f;
     invicibleTime = 0;
     this->programms = programms;

     std::vector<glm::vec3> offsetVect;
     offsetVect.push_back(glm::vec3(0.0f,-1.0f,0.0f));
//   playerObject = new GameSphere("sphere",programms["player"],0.25,glm::vec3(1,1,1),offsetVect,"checkerboard.tga",true);
	 playerObject = new GameObject("player",programms["player"], offsetVect,"roat_texture_256.tga",true);
	 playerObject->loadOBJ("character/character.obj");
	 this->gravity = gravity;
	 direction = glm::vec3( cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle) );
	 this->offset = offsetVect[0];
	 currentPositionIndex = 0;
	 positions[0] = 0.0f;
	 positions[1] = 4.4f;
	 positions[2] = 8.8f;
	 pressed[0] = false;
	 pressed[1] = false;
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

	updatePos(window,dt);
	score += dt;

	if(invicibleTime < 1 && isInvicible==true) {
		invicibleTime += dt;
	}else {
		isInvicible = false;
		invicibleTime = 0;
	}

	int index = 0;
	for(auto object : objects) {
		if(object->getName()!="road") {
			if(playerObject->isColliding(object)) {
				//	std::cout << object->getName() << " touch" <<std::endl;
				if(object->getName() == "wall" && isInvicible==false){
					SoundGameEngine::play("hit_wall.ogg",false);
					lives -= 1;
					isInvicible = true;
				}else if(object->getName() == "bonusLife"){
					lives += 1;
				}else if(object->getName() == "bonusScore"){

					SoundGameEngine::play("bonus2.ogg",false);
					std::cout << "touch bonus" <<std::endl;
					score += 250.0;
				}else if(object->getName() == "bonusSpeed"){
					speed += 1.0f;
				}
			} else {

			}
		}
		index++;
	}
	movePlayer();
}

int Player::getLives(){
	return lives;
}

void Player::updatePos(GLFWwindow *window,float dt) {

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
	if (glfwGetKey( window,GLFW_KEY_UP ) == GLFW_PRESS){
		position -= direction * dt * speed;
	}
	// Move backward
	if (glfwGetKey( window,GLFW_KEY_DOWN ) == GLFW_PRESS){
		position += direction * dt * speed;
	}
	// Strafe right
	if (glfwGetKey( window,GLFW_KEY_RIGHT ) == GLFW_PRESS && glfwGetKey( window,GLFW_KEY_RIGHT ) == GLFW_RELEASE){
		currentPositionIndex--;
		if(currentPositionIndex < 0){
			currentPositionIndex = 0;
		}
		std::cout << "position" << currentPositionIndex << " " << positions[currentPositionIndex] << std::endl;
		position = glm::vec3(positions[currentPositionIndex],position.y,position.z);
	}
	// Strafe left
	if (glfwGetKey( window,GLFW_KEY_LEFT ) == GLFW_PRESS && glfwGetKey( window,GLFW_KEY_LEFT ) == GLFW_RELEASE ){
		currentPositionIndex++;
		if(currentPositionIndex > 2){
			currentPositionIndex = 2;
		}
		std::cout << "position" << currentPositionIndex << " " << positions[currentPositionIndex] << std::endl;
		position = glm::vec3(positions[currentPositionIndex],position.y,position.z);
	}

	if(glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
		pressR = false;
	}
	if(glfwGetKey(window,GLFW_KEY_R) == GLFW_PRESS && pressR ==  false) {
		isMovingAuto = isMovingAuto ^ true;
		pressR = true;
	}

	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isJumping == false) {
		isJumping = true;
		dy = 20;
	}

	if(isMovingAuto)
		position -= direction * dt * speed;


	direction=	 glm::vec3(
			3*cos(verticalAngle) * sin(horizontalAngle),
			3*sin(verticalAngle),
			3*cos(verticalAngle) * cos(horizontalAngle)
			);

	right = glm::vec3(
			sin(horizontalAngle - 3.14f/2.0f),
			0,
			cos(horizontalAngle - 3.14f/2.0f)
			);

	up = -glm::cross( right, direction );


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

