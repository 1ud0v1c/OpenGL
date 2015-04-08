#include "soundGameEngine.h"
#include <iostream>
using namespace irrklang;

ISoundEngine *SoundGameEngine::soundEngine = createIrrKlangDevice();

ISoundEngine *SoundGameEngine::soundEngineNoise = createIrrKlangDevice();
SoundGameEngine::SoundGameEngine() {

}

void SoundGameEngine::play(const std::string &name, bool repeat, bool paused, bool tracked, float level) {
	ISound *sound = soundEngine->play2D(name.c_str(),repeat,paused,tracked);
	if(sound)
		sound->setVolume(level);
}


void SoundGameEngine::stop() {
	soundEngine->stopAllSounds();
	soundEngine->removeAllSoundSources();
	soundEngine->update();
}
