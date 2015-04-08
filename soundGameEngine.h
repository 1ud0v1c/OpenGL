#ifndef SOUDNGAMEENGINE_H
#define SOUDNGAMEENGINE_H

#include <irrKlang.h>
#include <string>
#include <map>
using namespace irrklang;

class SoundGameEngine {
	public:
		static ISoundEngine *soundEngine;
		static ISoundEngine *soundEngineNoise;
		SoundGameEngine();
		static void play(const std::string &name, bool repeat=false, bool paused=false,bool tracked=false,float level=1.0f);
		static void stop();

	private:

};

#endif
