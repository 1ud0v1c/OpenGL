#ifndef SOUDNGAMEENGINE_H
#define SOUDNGAMEENGINE_H

#include <irrKlang.h>
#include <string>
using namespace irrklang;

class SoundGameEngine {
	public:
		SoundGameEngine();
		static void play(const std::string &name, bool repeat=false);

		static ISoundEngine *soundEngine;
	private:


};

#endif
