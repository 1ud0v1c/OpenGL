#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <map>
#include "gameText.h"
#include "level.h"

class HUD {
	public:
		HUD();
		HUD(std::map<std::string,GLuint> programms);
		void init(Level level); 
		void update(Level level, float dt);
		void draw();

	protected:
		Level level;
		GameText *chrono;
		GameText *lifes;
		std::map<std::string,GLuint> programms;

};

#endif
