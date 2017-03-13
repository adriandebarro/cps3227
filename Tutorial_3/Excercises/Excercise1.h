#pragma once 
#include "../stdafx.h"

#include <iostream>
#include "./Excercise.h"

namespace OpenMPExcercises
{
	namespace Excercises
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	An example 1. Hello World Exampole </summary>
		///
		/// <remarks>	Adrian, 13/03/2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		class Example1 : public Excercise
		{
		private:

		public:
			virtual void ExecuteExcercise()
			{
				std::cout << "Hello and welcome to the world of OpenMP" << std::endl;

				#pragma omp parallel num_threads(5)
				{
					std::cout << "This is the thread ID" << omp_get_thread_num() << std::endl;
				}
			}
		};
	}
}
