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
	chrono = new GameText("text", programms["text2D"], offset, "hold.DDS", "0", 10, 500, 40);
	lifes = new GameText("text", programms["text2D"], offset, "hold.DDS", out.str().c_str(), 650, 500, 40);
	out << player->getScore(); 
	score = new GameText("text",programms["text2D"], offset, "hold.DDS", out.str().c_str(), 10,10, 40);

	menu = new GameText("text", programms["text2D"], offset, "hold.DDS", "Bienvenue dans RunnerGL, pour lancer", 35, 768/2, 20); 
	menu2 = new GameText("text", programms["text2D"], offset, "hold.DDS", "le jeu, presser R !", 35, 768/2-50, 20);
	menu3 = new GameText("text", programms["text2D"], offset, "hold.DDS", "Echap pour quitter...", 35, 768/2-100, 20);
}

void HUD::update(Level level, float dt) {
	chrono->update(dt);
	lifes->update(level.getPlayer()->getLives());
	score->update(level.getPlayer()->getScore());
}

void HUD::draw() {
	glUseProgram(chrono->getProgramm());
	chrono->draw();
	lifes->draw();
	score->draw();
	glUseProgram(0);
}

void HUD::drawMenu() {
	glUseProgram(chrono->getProgramm());
	menu->draw();
	menu2->draw();
	menu3->draw();
	glUseProgram(0);
}

void HUD::initEnd(Player* p) {
	menu->setText("Vous avez perdu !");
	menu2->setText("Votre score est de : "+std::to_string(p->getScore()));
}

