#include "player.h"

Player::Player() {
     lives = 3;
     score = 0;
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

void Player::changeXPos(double value){
     xPos += value;
}

void Player::changeYPos(double value){
     yPos += value;
}

double Player::getXPos(){
     return xPos;
}

double Player::getYPos(){
     return yPos;
}
