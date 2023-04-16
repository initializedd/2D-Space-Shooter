#ifndef PAIR_H
#define PAIR_H

#include <concepts>

template <typename T>
concept Integer = std::is_integral_v<int>;

template <Integer T>
struct Pair
{
	T x;
	T y;
};

#endif // !PAIR_H