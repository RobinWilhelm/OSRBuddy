#pragma once
#include <chrono>

class BuddyTimer
{	   
public:	

	BuddyTimer();
	BuddyTimer(std::chrono::milliseconds basetime);
	BuddyTimer(std::chrono::milliseconds basetime, std::chrono::milliseconds variation);

	bool IsReady();
	void Reset();
	void Reset(std::chrono::milliseconds basetime);
	void Reset(std::chrono::milliseconds basetime, std::chrono::milliseconds variation);

private:
	std::chrono::milliseconds m_basetime;
	std::chrono::milliseconds m_variation;

	std::chrono::milliseconds m_timertime;
	std::chrono::system_clock::time_point m_starttime;
};

/*
class StopWatch
{
public:
	StopWatch();

	void Start();
	void Stop();
	void Reset();

private:
	std::chrono::system_clock::time_point m_starttime;
	std::chrono::milliseconds m_totaltime;
};
*/

