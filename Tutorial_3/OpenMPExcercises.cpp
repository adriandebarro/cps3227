// OpenMPExcercises.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "./Excercises/Excercise1.h"
#include "./Excercises/Excercise2.h"
#include "./Excercises/Execscise3.h"

void Pause()
{
	std::cout << "Press any key to continue..." << std::endl;
	std::getchar();
}


int main()
{
	OpenMPExcercises::Excercises::Example1 example1;
	example1.ExecuteExcercise();
	std::cout << "-------" << std::endl;
	OpenMPExcercises::Excercises::Example2 example2;
	example2.ExecuteExcercise();
	std::cout << "-------" << std::endl;
	OpenMPExcercises::Excercises::Example3 example3;
	example3.ExecuteExcercise();

	Pause();
    return 0;
}

