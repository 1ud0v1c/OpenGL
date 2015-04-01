#include "hud.h"

HUD::HUD() {}

HUD::HUD(std::map<std::string,GLuint> programms) {
	this->programms = programms;
}

void HUD::init() {
	std::vector<float> offset;
	chrono = new GameText("text", programms["text2D"], offset, "hold.DDS", "0", 10, 500);
	lifes = new GameText("text", programms["text2D"], offset, "hold.DDS", "3x", 700, 500);
}

void HUD::update(Level &level, float dt) {
	chrono->update(dt);
}

void HUD::draw() {
	glUseProgram(chrono->getProgramm());
	chrono->draw();
	lifes->draw();
	glUseProgram(0);
}

