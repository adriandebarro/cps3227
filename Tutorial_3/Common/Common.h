#pragma once
#include <chrono>
#include <iostream>

namespace OpenMPExcercises
{
	namespace Common
	{
		inline static void TakeCurrentTime(clock_t &p_clock)
		{
			p_clock = clock();
		}

		double static ComputeTime(clock_t &p_startingTime, clock_t &p_endingTime)
		{
			double prol = 0;
			clock_t timeTaken = p_endingTime - p_startingTime;
			prol = timeTaken / (double) CLOCKS_PER_SEC;
			return prol;
		}
	}
}
