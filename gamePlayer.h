#ifndef GAME_PLAYER_H
#define GAME_PLAYER_H

#include "gameObject.h"

class GamePlayer : public GameObject {
	public:
	     GamePlayer(const std::string &name, GLuint &programm, std::vector<float> &offset);
	     ~GamePlayer();
	     int getLives();
	     void modifyLives(int value);
	     void modifyScore(double value);
	
	private:
	     int lives;
	     double score;
};
#endif
