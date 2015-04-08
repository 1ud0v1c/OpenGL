#include "hud.h"
#include <sstream> 
#include <iomanip>

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
	lifes = new GameText("text", programms["text2D"], offset, "hold.DDS", out.str().c_str(), 660, 500, 40);
	out << player->getScore(); 
	score = new GameText("text",programms["text2D"], offset, "hold.DDS", out.str().c_str(), 10,10, 40);
	out << "Level : " << level.getCurrentLevel();
	levels = new GameText("text",programms["text2D"], offset, "hold.DDS", out.str().c_str(), 500, 10, 30);

	const int shift = 50;
	menu = new GameText("text", programms["text2D"], offset, "hold.DDS", "Bienvenue dans RunnerGL, pour lancer", 35, 768/2+shift, 20); 
	menu2 = new GameText("text", programms["text2D"], offset, "hold.DDS", "le jeu, presser R !", 35, 768/2, 20);
	menu3 = new GameText("text", programms["text2D"], offset, "hold.DDS", "Up/Down : pour gerer la vitesse", 35, 768/2-shift, 20);
	menu4 = new GameText("text", programms["text2D"], offset, "hold.DDS", "Echap pour quitter...", 35, 768/2-shift*2, 20);
}

void HUD::update(Level level, float dt) {
	chrono->update(dt);
	lifes->update(level.getPlayer()->getLives());
	score->update(level.getPlayer()->getScore());
	levels->updateLevels(level.getCurrentLevel());
}

void HUD::draw() {
	glUseProgram(chrono->getProgramm());
	chrono->draw();
	lifes->draw();
	score->draw();
	levels->draw();
	glUseProgram(0);
}

void HUD::drawMenu() {
	glUseProgram(chrono->getProgramm());
	menu->draw();
	menu2->draw();
	menu3->draw();
	menu4->draw();
	glUseProgram(0);
}

void HUD::initEnd(Player* p) {
	menu->setText("Vous avez perdu !");
	std::ostringstream out;  
	out << "Votre score est de : " << std::setprecision(0) << std::fixed << p->getScore(); 
	menu2->setText(out.str());
	menu3->setText("R pour redemarrer");
	menu4->setText("Echap pour quitter...");
}

