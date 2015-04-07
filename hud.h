#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <map>
#include "gameText.h"
#include "level.h"
#include "player.h"

class HUD {
	public:
		HUD();
		HUD(std::map<std::string,GLuint> programms);
		void init(Level level); 
		void update(Level level, float dt);
		void draw();
		void drawMenu();
		void drawEnd();
		void initEnd(Player* p);

	protected:
		Level level;
		GameText *menu, *menu2, *menu3;
		GameText *chrono;
		GameText *lifes;
		GameText *score;
		std::map<std::string,GLuint> programms;
};

#endif
