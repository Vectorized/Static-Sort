/*
 Copyright (c) 2016 Kang Yue Sheng Benjamin
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef timer_h
#define timer_h

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

class Timer
{
	inline unsigned long long getEpochMicroseconds()
	{
#ifdef WIN32
		/* Windows */
		FILETIME ft;
		LARGE_INTEGER li;
		/* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601 (UTC) and copy it
		 * to a LARGE_INTEGER structure. */
		GetSystemTimeAsFileTime(&ft);
		li.LowPart = ft.dwLowDateTime;
		li.HighPart = ft.dwHighDateTime;
		
		unsigned long long ret = li.QuadPart;
		ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
		ret /= 10; /* From 100 nano seconds (1e-7) to microsecond (1e-6) intervals */
		
		return ret;
#else
		/* Linux */
		struct timeval tv;
		gettimeofday(&tv, NULL);
		unsigned long long ret = tv.tv_usec;
		/* Adds the seconds after converting them to microseconds (1e-6) */
		ret += (tv.tv_sec * 1000000);
		return ret;
#endif
	}
	unsigned long long startEpochMicroSeconds;
	unsigned long long stopEpochMicroSeconds;

public:

	inline void start()
	{
		stopEpochMicroSeconds = 0;
		startEpochMicroSeconds = getEpochMicroseconds();
	}
	
	inline void stop()
	{
		stopEpochMicroSeconds = getEpochMicroseconds();
	}	

	inline Timer(): startEpochMicroSeconds(0), stopEpochMicroSeconds(0) {}
	
	inline double getElapsedMilliseconds()
	{
		return (stopEpochMicroSeconds - startEpochMicroSeconds) / 1000.0;
	}
};

#endif