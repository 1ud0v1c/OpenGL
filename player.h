#ifndef PLAYER_H
#define PLAYER_H

class Player {
	public:
	     Player();
	     ~Player();
	     int getLives();
	     void modifyLives(int value);
	     void modifyScore(double value);
	     void changeXPos(double value);
	     void changeYPos(double value);
	     double getXPos();
	     double getYPos();
	
	private:
	     int lives;
	     double score;
	     double xPos, yPos;
};
#endif
