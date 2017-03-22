#include <iostream>
#include <cstdio>

#include "./Exercises/ProducerConsumer.h"

using namespace Exercises;

void Pause()
{
	std::cout << "Press any key to continue" << std::endl;
	std::getchar();
}

int main(void)
{
	ProducerConsumer* prodCons = new ProducerConsumer();
	prodCons->ExecuteExample();
	Pause();
	return 0;
}