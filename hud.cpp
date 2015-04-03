#include "hud.h"
#include <sstream> 

HUD::HUD() {}

HUD::HUD(std::map<std::string,GLuint> programms) {
	this->programms = programms;
}

void HUD::init(Level level) {
	std::vector<glm::vec3> offset;
	Player *player = level.getPlayer();
	std::ostringstream out;  
	out << player->getLives() << "x"; 
	chrono = new GameText("text", programms["text2D"], offset, "hold.DDS", "0", 10, 500);
	lifes = new GameText("text", programms["text2D"], offset, "hold.DDS", out.str().c_str(), 700, 500);
}

void HUD::update(Level level, float dt) {
	chrono->update(dt);
	lifes->update(level.getPlayer()->getLives());
}

void HUD::draw() {
	glUseProgram(chrono->getProgramm());
	chrono->draw();
	lifes->draw();
	glUseProgram(0);
}

