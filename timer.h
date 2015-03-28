#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
	public:
		double calculateFrameRate();
		double getTime();
	private:
		double deltaTime = 0;
		double currentTime = 0;
};

#endif
