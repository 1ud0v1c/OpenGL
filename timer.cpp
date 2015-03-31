#include "timer.h" 

using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

double Timer::calculateFrameRate() {
	static double framesPerSecond = 0.0f; 
	static double startTime = getTime();
	static double lastTime = getTime(); 
	static double currentFPS = 0.0f; 

	currentTime = getTime();
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
	++framesPerSecond;

	if (currentTime - startTime > 1.0f ) {
		startTime = currentTime;
		currentFPS = framesPerSecond;
		framesPerSecond = 0;
	}
	return currentFPS;
}

double Timer::getTime() {
	auto beginningOfTime = system_clock::now().time_since_epoch();
	auto ms = duration_cast<milliseconds>(beginningOfTime).count();
	return ms * 0.001;
}

