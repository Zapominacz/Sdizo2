#pragma once
#include "stdafx.h"

class Timer {
private:
	LARGE_INTEGER performanceCountStart;
	LARGE_INTEGER performanceCountEnd;
	LARGE_INTEGER cumulativeSum;
	int count;
public:
	Timer(void);
	~Timer(void);
	void startTimer(void);
	void stopTimer(void);
	void nextMeasure(void);
	void printAvgTime(void);
};