#include "soundGameEngine.h"

using namespace irrklang;
ISoundEngine *SoundGameEngine::soundEngine = createIrrKlangDevice();
SoundGameEngine::SoundGameEngine() {

}

void SoundGameEngine::play(const std::string &name, bool repeat) {
	soundEngine->play2D(name.c_str(),repeat);
}

