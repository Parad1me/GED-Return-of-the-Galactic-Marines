#pragma once
#include <string>
#include <Windows.h>

using namespace std;

class timer
{
public:
	unsigned __int64 getFRAME();
	unsigned int getCurrentTimeMS();
	string getFPSstring();
	string getMSstring();
	void setTimerIntervalMS(float interv);
	void updateTime(float *deltaTime);
	double getMS();
	int getFPS();
	bool intervalHasPassed();
	bool init();
	timer();
private:
	void updateMS();
	unsigned __int64 currentFrame;
	unsigned __int64 lastFrame;
	LARGE_INTEGER ticksPerSecond;
	LARGE_INTEGER timeLast;
	LARGE_INTEGER timeCurrent;
	stringstream ss;
	double ms;
	double currentMS;
	float timeInterval;
	int fps;
};