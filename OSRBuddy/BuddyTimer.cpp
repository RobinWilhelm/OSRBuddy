#include "BuddyTimer.h"
#include "Utility.h"
#include <chrono>

using namespace std::literals::chrono_literals;

BuddyTimer::BuddyTimer()
{
	m_basetime = 0ms;
	m_starttime = std::chrono::system_clock::now();
	m_timertime = 0ms;
	m_variation = 0ms;
}

BuddyTimer::BuddyTimer(std::chrono::milliseconds basetime)
{
	m_basetime = basetime;
	m_starttime = std::chrono::system_clock::now();
	m_timertime = 0ms;
	m_variation = 0ms;
}

BuddyTimer::BuddyTimer(std::chrono::milliseconds basetime, std::chrono::milliseconds variation)
{
	m_basetime = basetime;
	m_starttime = std::chrono::system_clock::now();
	m_timertime = 0ms;
	m_variation = variation;
}

bool BuddyTimer::IsReady()
{
	std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	return (current - std::chrono::duration_cast<std::chrono::milliseconds>(m_starttime.time_since_epoch()) >= m_timertime) ? true : false;
}

void BuddyTimer::Reset()
{
	Reset(m_basetime, m_variation);
}

void BuddyTimer::Reset(std::chrono::milliseconds basetime)
{
	Reset(basetime, 0ms);
}

void BuddyTimer::Reset(std::chrono::milliseconds basetime, std::chrono::milliseconds variation)
{
	m_timertime = std::chrono::milliseconds(Utility::GetRandInt32(basetime.count(), (basetime + variation).count()));
	m_starttime = std::chrono::system_clock::now();
}

/*
StopWatch::StopWatch()
{
	Reset();
}

void StopWatch::Start()
{
	std::chrono::milliseconds current = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	m_starttime = current;
}

void StopWatch::Reset()
{	 
	m_starttime = std::chrono::system_clock::now();
	m_totaltime = 0ms;
}
*/
