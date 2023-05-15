#ifndef PAIR_H
#define PAIR_H

#include <concepts>

template <typename T>
concept Number = std::is_integral_v<int> || std::is_floating_point_v<double>;

template <Number T>
struct Pair
{
	T x;
	T y;
};

#endif // !PAIR_H