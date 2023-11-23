#ifndef TIMER_H
#define TIMER_H

#include <SDL3/SDL_timer.h>

class Timer
{
private:
	Uint64				m_startTicks;
	Uint64				m_pausedTicks;

	bool				m_started;
	bool				m_paused;

public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint64 getTicks();

	bool isStarted();
	bool isPaused();
};

#endif // !TIMER_H
