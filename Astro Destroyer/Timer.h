#ifndef TIMER_HEADER
#define TIMER_HEADER
#include <iostream>
#include <SDL.h>

class Timer {
public:
	Timer();

	void resetTicksTimer();
	int GetTicks();

private:
	int startTicks;
};
#endif // !TIMER_HEADER

