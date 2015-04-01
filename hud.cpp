#include "hud.h"

HUD::HUD() {}

HUD::HUD(std::map<std::string,GLuint> programms) {
	this->programms = programms;
}

void HUD::init() {
	std::vector<float> offset;
	text = new GameText("text", programms["text2D"], offset, "hold.DDS", "0");
}

void HUD::update(float dt) {
	text->update(dt);
}

void HUD::draw() {
	glUseProgram(text->getProgramm());
	text->draw();
	glUseProgram(0);
}

