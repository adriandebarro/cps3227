#pragma once 

#include <omp.h>
#include <math.h>

#include "../Common/Common.h"
#include "./Excercise.h"

namespace OpenMPExcercises
{
	namespace Excercises
	{
		class Example2 : public Excercise
		{
		private:

		public:
			float CurveValue(float p_currentX)
			{
				return p_currentX * p_currentX + 2 * sin(p_currentX);
			}


			float NaiveIntegration(int p_start, int p_end, int p_steps)
			{
				float finalRes = 0;
				float deltaX = (float)(p_end - p_start) / p_steps;
				float currentStep = 0.0f;

				currentStep = p_start;

				finalRes = CurveValue(p_start) + CurveValue(p_end);
				finalRes /= 2;

				for (int indexX = 0; indexX < p_steps; indexX++)
				{
					currentStep += deltaX;
					finalRes += CurveValue(currentStep);
				}

				finalRes *= (deltaX);

				return finalRes;
			}
			
			void NaiveTrapezoidal()
			{
				double result = NaiveIntegration(0, 5, 9000000);
				std::cout << "Naive trapezoidal is equal " << result << std::endl;
			}

			void CoarseParallelisedTrapezoidal()
			{
				int numberThreads = 5;
				int start = 0;
				int end = 5;
				int steps = 9000000;

				double reductionFinal = 0;

				//checking that the amount of divisions is a multiple of the number of threads
				steps = (steps / numberThreads) * numberThreads;

				//finding the batch size of each thread
				int divisionSize = steps / numberThreads;


				float deltaSize = (float)(end - start) / steps;
				double *partialResult = new double[numberThreads];

				#pragma omp parallel num_threads(numberThreads) //reduction(+: reductionFinal)
				{
					int threadID = omp_get_thread_num();

					int numberSamples = steps / numberThreads;

					int startingPoint = start + threadID * divisionSize * deltaSize;
					int endingPoint = startingPoint + divisionSize *   deltaSize;

					partialResult[threadID] = NaiveIntegration(startingPoint, endingPoint, numberSamples );
					//reductionFinal = NaiveIntegration(startingPoint, endingPoint, numberSamples);
					//std::cout << "Thread " << omp_get_thread_num() << " is ready" <<  std::endl;
				}	

				double finalResult = 0;

				for (int index = 0; index < numberThreads; index++)
				{
					reductionFinal += partialResult[index];
				}

				std::cout << "Parallel trapezoidal is equal " << reductionFinal << std::endl;
			}

			void FineParallelisedTrapezoidal()
			{

				double finalRes = 0;
				omp_set_num_threads(10);
				finalRes = FineParallelisedIntegration(0, 5, 9000000);
				std::cout << "Parallel trapezoidal is equal " << finalRes << std::endl;
			}


			double FineParallelisedIntegration(int p_start, int p_end, int p_steps)
			{
				float deltaX = (float)(p_end - p_start) / (float)p_steps;
				float x = 0;
				double finalResult = CurveValue(p_start) + CurveValue(p_end);
				finalResult /= 2;

				#pragma omp parallel for private(x) reduction(+: finalResult)
				for (int index = 0; index < p_steps; index++)
				{
					x = p_start + index * deltaX;
					finalResult += CurveValue(x);
				}

				finalResult *= deltaX;
				return finalResult;
			}

			virtual void ExecuteExcercise()
			{
				omp_set_num_threads(10);
				double startingClock, endingClock;

				Common::TakeCurrentTime(startingClock);
				NaiveTrapezoidal();
				Common::TakeCurrentTime(endingClock);

				double naiveTimeTaken = Common::ComputeTime(startingClock, endingClock);

				std::cout << "Time taken naive " << naiveTimeTaken << std::endl;

				Common::TakeCurrentTime(startingClock);
				CoarseParallelisedTrapezoidal();
				Common::TakeCurrentTime(endingClock);

				double parallelisedTrapezoidal = Common::ComputeTime(startingClock, endingClock);
				
				std::cout << "Time taken parallelised " << parallelisedTrapezoidal << std::endl;

				Common::TakeCurrentTime(startingClock);
				FineParallelisedTrapezoidal();
				Common::TakeCurrentTime(endingClock);

				double fineParallelisedTrapezoidal = Common::ComputeTime(startingClock, endingClock);

				std::cout << "Time taken parallelised " << fineParallelisedTrapezoidal << std::endl;
			
			}

		};
	}
}
