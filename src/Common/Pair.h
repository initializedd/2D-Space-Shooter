#ifndef PAIR_H
#define PAIR_H

#include <concepts>

template <typename T>
concept Number = std::is_integral_v<int> || std::is_floating_point_v<float>;

template <Number T>
struct Pair
{
	T x;
	T y;
};

template <Number T>
using Vector2 = Pair<T>;

#endif // !PAIR_H
