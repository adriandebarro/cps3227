#include <iostream>
#include <omp.h>
#include <random>
#include <thread>

#define USE_ATOMIC_OPERATION

namespace Exercises
{

	template<typename T>
	inline T FetchAndAdd(T *shrVar, T val)
	{
		//built-in atomic operations in g++/gcc
		//https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Atomic-Builtins.html
		#ifdef GCC_EXTENSION
			return __sync_fetch_and_add(shrVar, val);
		#else
			T temp;
			#pragma omp atomic capture
			{ temp = *shrVar; *shrVar += val; }
			return temp;
		#endif
	}
	
	class ProducerConsumer 
	{
	private:
		int m_numberThreads;
		int m_bufferSize;
		int m_maxBound;
		int m_infiniteRepeat;
		int* m_buffer;
		int m_next;

		void StartProducerConsumer(bool p_useAtomicOperations = false)
		{
			int *buffer = new int[m_bufferSize];
			int next = 0;
			int currentIndex = 0;
			bool moreElements = true;

			if(p_useAtomicOperations)
			{
				#pragma omp parallel shared(next, buffer) private(currentIndex, moreElements)
				{
					do
					{				
						#pragma omp single 
						{
							for(int index = 0; index < m_bufferSize; index++ )
							{
								buffer[index] = rand() % m_maxBound;
							}

							next = 0;
						}

						#pragma omp barrier 
						
						//continue looping until the elem
						while(currentIndex < m_bufferSize)
						{
							currentIndex = FetchAndAdd(&next, 1);
							if(currentIndex >= m_bufferSize)
								continue;
							else
							{
								//simulating a long on going computation
								std::cout << "processing element " << currentIndex << " ----- " << omp_get_thread_num() << std::endl;
								std::this_thread::sleep_for(std::chrono::milliseconds(buffer[currentIndex]));
							}
						}
					}
					while(m_infiniteRepeat);
				}
			}
			else
			{
				#pragma omp parallel shared(next, buffer) private(currentIndex, moreElements)
				{
					do
					{				
						#pragma omp single 
						{
							for(int index = 0; index < m_bufferSize; index++ )
							{
								buffer[index] = rand() % m_maxBound;
							}

							next = 0;
						}

						#pragma omp barrier 
						
						while(currentIndex >= 0)
						{
							#pragma omp critical
							{
								if(next < m_bufferSize)
								{
									currentIndex = next;
									next++;
								}
								else
								{
									currentIndex = -1;
								}
							}

							if(currentIndex == -1)
								continue;
							else
							{
								//simulating a long computation going on
								std::cout << "processing element " << currentIndex << " ----- " << omp_get_thread_num() << std::endl;
								std::this_thread::sleep_for(std::chrono::milliseconds(buffer[currentIndex]));
							}
						}
					}
					while(m_infiniteRepeat);
				}
			}

			delete[] buffer;
		}

	public:

		ProducerConsumer(int p_numberThreads = 10, int p_bufferSize = 100, int p_maxBound = 1000, bool p_infiniteRepeat = false)  
			: m_numberThreads(p_numberThreads),
			  m_bufferSize(p_bufferSize),
			  m_maxBound(p_maxBound),
			  m_infiniteRepeat(p_infiniteRepeat)
		{}	

		void ExecuteExample()
		{
			omp_set_num_threads(1);
			std::cout << "Commencing sequential Producer-Consumer simulation "<< omp_get_num_threads() << std::endl;
			StartProducerConsumer();
			omp_set_num_threads(10);
			std::cout << "Commencing Producer-Consumer simulation "<< omp_get_num_threads() << std::endl;
			StartProducerConsumer();
			std::cout << "Commencing Producer-Consumer simulation using atomic operations"<< omp_get_num_threads() << std::endl;
			StartProducerConsumer(true);
		}
	};

}