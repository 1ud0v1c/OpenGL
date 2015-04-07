#ifndef SOUDNGAMEENGINE_H
#define SOUDNGAMEENGINE_H

#include <irrKlang.h>
#include <string>

using namespace irrklang;

class SoundGameEngine {
	public:
		static ISoundEngine *soundEngine;
		SoundGameEngine();
		static void play(const std::string &name, bool repeat=false);
		static void stop();

	private:

};

#endif
