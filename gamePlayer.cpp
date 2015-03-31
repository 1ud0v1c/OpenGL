#include "gamePlayer.h"

GamePlayer::GamePlayer(const std::string &name,GLuint &programm,std::vector<float> &offset) : GameObject(name, programm, offset){
     lives = 3;
     score = 0;
}

int GamePlayer::getLives(){
     return lives;
}

void GamePlayer::modifyLives(int value){
     lives += value;
}

void GamePlayer::modifyScore(double value){
     score += value;
}
