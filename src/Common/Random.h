#ifndef RANDOM_H
#define RANDOM_H

#include <chrono>
#include <random>

inline int getRandomNumber(int min, int max)
{
	std::random_device rd{};
	std::seed_seq ss
	{
		static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
		rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()
	};

	std::mt19937 mt{ ss };

	std::uniform_int_distribution dist{ min, max };

	return dist(mt);
}

#endif // !RANDOM_H