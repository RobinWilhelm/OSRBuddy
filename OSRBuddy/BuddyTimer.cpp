#include "osrb_pch.h"
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

StopWatch::StopWatch()
{
	m_starttime = std::chrono::system_clock::now();
	m_accumulatedtime = 0ms;
	m_running = false;
}

StopWatch::~StopWatch()
{
}

void StopWatch::Start()
{
	if (m_running)
		return;

	m_starttime = std::chrono::system_clock::now();
	m_running = true;
}

void StopWatch::Stop()
{
	if (!m_running)
		return;

	m_accumulatedtime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_starttime);
	m_running = false;
}

void StopWatch::Reset()
{	 
	m_starttime = std::chrono::system_clock::now();
	m_accumulatedtime = 0ms;
}

std::chrono::milliseconds StopWatch::GetElapsedTime()
{
	std::chrono::milliseconds totalTime = m_accumulatedtime;
	if (m_running)
		totalTime += std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - m_starttime);

	return totalTime;
}
