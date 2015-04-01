#include "player.h"

Player::Player() {
     lives = 3;
     score = 0;
     speed = 3.0f;	
     direction = glm::vec3( cos(0.0f) * sin(3.14f), sin(0.0f), cos(0.0f) * cos(3.14f) );
}

void Player::update(float time,GLFWwindow *window, float dt){

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

