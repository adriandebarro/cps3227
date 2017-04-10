#pragma once
#include <chrono>
#include <iostream>

namespace OpenMPExcercises
{
	namespace Common
	{
		inline static void TakeCurrentTime(double &p_clock)
		{
			p_clock = omp_get_wtime();
		}

		double static ComputeTime(double &p_startingTime, double &p_endingTime)
		{
			double prol = 0;
			return  p_endingTime - p_startingTime;
		}
	}
}
