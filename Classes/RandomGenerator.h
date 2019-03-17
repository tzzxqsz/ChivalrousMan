#pragma once
#ifndef __RANDOM_GENERATOR_H__
#define __RANDOM_GENERATOR_H__
#include<algorithm>
#include<chrono>

class RandomGenerator
{
public:
	ptrdiff_t operator() (ptrdiff_t max)
	{
		double temp;
		srand(std::chrono::system_clock::now().time_since_epoch().count());
		temp = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
		return static_cast<ptrdiff_t>(temp * max);
	}
};

#endif // !

