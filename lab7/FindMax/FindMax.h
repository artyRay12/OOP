#pragma once
#include <vector>

template <typename T>
bool FindMax(std::vector<T> const& arr, T& maxValue)
{
	if (arr.empty())
	{
		return false;
	}

	const T *maxElem = &arr[0];

	for (const auto &elem: arr)
		if (*maxElem < elem)
			maxElem = &elem;

	maxValue = *maxElem;

	return true;
}

template <>
bool FindMax<const char*>(std::vector<const char*> const& arr, const char*& maxValue)
{
	if (arr.empty())
	{
		return false;
	}

	maxValue = arr[0];

	for (const auto &elem: arr)
		if (strcmp(elem, maxValue) > 0)
			maxValue = elem;

	return true;
}
