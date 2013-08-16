#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>
#include "Timer.h"

using namespace std;

timer::timer()
{
	ms = 0;
	fps = 0;
	lastFrame = 0;
	currentFrame = 0;
	currentMS = 0;
}

bool timer::init()
{
	if(QueryPerformanceFrequency(&ticksPerSecond))
	{
		 QueryPerformanceCounter(&timeCurrent);
		 timeLast = timeCurrent;
	}
	else
	{
		return false;
	}
	return true;
}

bool timer::intervalHasPassed()
{
	if(currentMS >= timeInterval)
	{
		fps = ((1000 / currentMS) * (currentFrame - lastFrame));
		lastFrame = currentFrame;
		currentMS = 0;
		return true;
	}
	return false;
}

string timer::getFPSstring()
{
	ss.str(std::string());
	ss << "FPS: " << fps;
	return ss.str();
}

string timer::getMSstring()
{
	ss.str(std::string());
	ss << "MS: " << getMS();
	return ss.str();
}

int timer::getFPS()
{
	return (1000 / ms);
}

double timer::getMS()
{
	return ms;
}

unsigned __int64 timer::getFRAME()
{
	return currentFrame;
} 

unsigned int timer::getCurrentTimeMS()
{
	return static_cast<unsigned int>(timeCurrent.QuadPart / (ticksPerSecond.QuadPart / 1000));
}

void timer::setTimerIntervalMS(float interv)
{
	timeInterval = interv;
}

void timer::updateMS()
{
	currentFrame++;
	QueryPerformanceCounter(&timeCurrent);
	ms = static_cast<double>(timeCurrent.QuadPart - timeLast.QuadPart) / (static_cast<double>(ticksPerSecond.QuadPart)/1000);
	timeLast = timeCurrent;
	
	currentMS += ms;
}

void timer::updateTime(float *deltaTime)
{
	updateMS();
	*deltaTime = static_cast<float>(ms / 100);
}