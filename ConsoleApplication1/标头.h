#pragma once

#include "windows.h"

#include <iostream>
#include<time.h>

class MicrosecondTimer
{
public:
	inline MicrosecondTimer()
	{
		QueryPerformanceFrequency(&freq);
	}
	inline void Start()
	{
		QueryPerformanceCounter(&startCount);
	}
	// 返回微秒 
	inline UINT64 Stop()
	{
		QueryPerformanceCounter(&endCount);
		UINT64 decrease = endCount.QuadPart - startCount.QuadPart;
		double elapsed = decrease / (double)freq.QuadPart;
		return UINT64(elapsed * 1000000);
	}
private:
	LARGE_INTEGER freq;
	LARGE_INTEGER startCount;
	LARGE_INTEGER endCount;
};


class NanosecondTimer
{

public:
	inline NanosecondTimer()
	{
		startT = 0;
		frequency = CalCPUFrequency();
	}
	//得到计算机启动到现在的时钟周期
	static inline  UINT64 GetCPUCycleCount(void)
	{
		//      __asm   _emit   0x0F
		//      __asm   _emit   0x31
		__asm RDTSC
	}

	// 得到CPU的频率
	static inline double CalCPUFrequency()
	{
		LARGE_INTEGER liFreq, liStart, liEnd;
		QueryPerformanceFrequency(&liFreq);
		QueryPerformanceCounter(&liStart);
		UINT64 startCounts = GetCPUCycleCount();
		Sleep(1000);
		QueryPerformanceCounter(&liEnd);
		UINT64 endCounts = GetCPUCycleCount() - startCounts;
		double elapsed = (liEnd.QuadPart - liStart.QuadPart) / (double)(liFreq.QuadPart);     // 微秒级精度
		double freq = endCounts / (elapsed * 1000000);
		return freq;
	}
	inline void Start()
	{
		startT = GetCPUCycleCount();
	}
	inline UINT64 Stop()
	{
		UINT64 endT = GetCPUCycleCount() - startT;
		return UINT64(endT * 1000 / frequency);
	}
	inline double Frequency()
	{
		return frequency;
	}

private:
	UINT64 startT;
	double frequency;   // MHz/s
};


class Mytimer {
	NanosecondTimer NT;
	MicrosecondTimer MT;
	
public:
	Mytimer() {

	}
	inline void Start()
	{
		NT.Start();
		MT.Start();
	}
	inline void  Stop()
	{
		UINT64 ns = 0;
		UINT64 ms = 0;
		ms = MT.Stop();
		ns = NT.Stop();
		static int i = 0;
		printf("%d CPU:%f;  %I64d; %I64d; \r\n",i++%4, NT.CalCPUFrequency(), ns, ms);
	}
}mytimer;