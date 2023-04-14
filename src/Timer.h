#ifndef TIMER_H
#define TIMER_H

#include <SDL_timer.h>

class Timer
{
private:
	Uint32				m_startTicks;
	Uint32				m_pausedTicks;
	
	bool				m_started;
	bool				m_paused;

public:
	Timer();
	~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();
};

#endif // !TIMER_H