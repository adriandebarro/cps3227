#pragma once 

#include <omp.h>
#include <random>

#include "../Common/Common.h"
#include "./Excercise.h"

namespace OpenMPExcercises
{
	namespace Excercises
	{
		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// <summary>	Exericse 3, Matrix multiplication comparision </summary>
		///
		/// <remarks>	Adrian, 12/03/2017. </remarks>
		////////////////////////////////////////////////////////////////////////////////////////////////////

		#define MATRIX_SIDE_SIZE 1000

		class Example3 : public Excercise
		{
		private:
	
		public:

			double** CreateMatrix(int p_size)
			{
				double **matrix = new double*[p_size];

				for (int index = 0; index < p_size; index++)
				{
					matrix[index] = new double[p_size];
				}

				for(int y = 0; y < p_size; y++)
				{
					for(int x = 0; x < p_size; x ++)
					{
						matrix[x][y] = 0;
					}
				}

				return matrix;
			}

			void CreateDummyData(double **p_matrixA, double **p_matrixB, double p_size)
			{
				for (int x = 0; x < p_size; x ++)
				{
					for (int y = 0; y < p_size; y++)
					{
						p_matrixA[x][y] = std::rand() % 100;
					}
				}

				for (int x = 0; x < p_size; x++)
				{
					for (int y = 0; y < p_size; y++)
					{
						p_matrixB[x][y] = std::rand() % 100;
					}
				}
			}


			void SerialMatrixMultiplication(double **p_matrix1, double **p_matrix2, double **p_resultMatrix, int p_sideSize)
			{
				for (int x = 0; x < p_sideSize; x++)
				{
					for (int y = 0; y < p_sideSize; y++)
					{
						for (int i = 0; i < p_sideSize; i++)
						{
							int currentRowElement = p_matrix1[x][i];
							int currentColElement = p_matrix2[i][y];

							p_resultMatrix[x][y] = p_resultMatrix[x][y] + p_matrix1[x][i] * p_matrix2[i][y];
						}
					}
				}
			}


			void ParallelMatrixMultiplication(double **p_matrix1, double **p_matrix2, double **p_resultMatrix, int p_sideSize)
			{
				int total = p_sideSize * p_sideSize;
				#pragma omp parallel for 
				for (int xy = 0; xy < total; xy++)
				{
					int x = xy / p_sideSize;
					int y = xy % p_sideSize;
					for (int i = 0; i < p_sideSize; i++)
					{
						p_resultMatrix[x][y] = p_resultMatrix[x][y] + p_matrix1[x][i] * p_matrix2[i][y];
					}
				}
			}


			virtual void ExecuteExcercise()
			{
				double **matrixA = nullptr;
				double **matrixB = nullptr;
				double **matrixCNaive = nullptr;
				double **matrixCParallel = nullptr;

				omp_set_num_threads(10);
				double startingClock, endingClock;

				matrixA = CreateMatrix(MATRIX_SIDE_SIZE);
				matrixB = CreateMatrix(MATRIX_SIDE_SIZE);
				matrixCNaive = CreateMatrix(MATRIX_SIDE_SIZE);
				matrixCParallel = CreateMatrix(MATRIX_SIDE_SIZE);

				CreateDummyData(matrixA, matrixB, MATRIX_SIDE_SIZE);

				Common::TakeCurrentTime(startingClock);
				SerialMatrixMultiplication(matrixA,matrixB, matrixCParallel, MATRIX_SIDE_SIZE);
				Common::TakeCurrentTime(endingClock);

				double naiveTimeTaken = Common::ComputeTime(startingClock, endingClock);
				std::cout << "Time taken for sequential matrix multiplication " << naiveTimeTaken << std::endl;

				Common::TakeCurrentTime(startingClock);
				ParallelMatrixMultiplication(matrixA, matrixB, matrixCParallel, MATRIX_SIDE_SIZE);
				Common::TakeCurrentTime(endingClock);

				double parallelTimeTaken = Common::ComputeTime(startingClock, endingClock);
				std::cout << "Time taken for Parallel matrix multiplication " << parallelTimeTaken << std::endl;
			}
		};
	}
}
