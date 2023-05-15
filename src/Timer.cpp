#include "Timer.h"

Timer::Timer()
	: m_startTicks{}
	, m_pausedTicks{}
	, m_started{}
	, m_paused{}
{
}

Timer::~Timer()
{
}

void Timer::start()
{
	m_started = true;
	m_paused = false;

	m_startTicks = SDL_GetTicks64();
	m_pausedTicks = 0;
}

void Timer::stop()
{
	m_started = false;
	m_paused = false;

	m_startTicks = 0;
	m_pausedTicks = 0;
}

void Timer::pause()
{
	if (m_started && !m_paused)
	{
		m_paused = true;

		m_pausedTicks = SDL_GetTicks64() - m_startTicks;
		m_startTicks = 0;
	}
}

void Timer::unpause()
{
	if (m_started && m_paused)
	{
		m_paused = false;

		m_started = SDL_GetTicks64() - m_pausedTicks;
		m_pausedTicks = 0;
	}
}

Uint64 Timer::getTicks()
{
	Uint64 time{};
	if (m_started)
	{
		if (m_paused)
		{
			time = m_pausedTicks;
		}
		else
		{
			time = SDL_GetTicks64() - m_startTicks;
		}
	}

	return time;
}

bool Timer::isStarted()
{
	return m_started;
}

bool Timer::isPaused()
{
	return m_paused;
}