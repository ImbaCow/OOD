#pragma once
#include "pch.h"

template <typename T, typename TItem1, typename TItem2>
void SetCompositeValue(const std::vector<std::shared_ptr<TItem1>>& styleArr, void (TItem2::*childFunc)(T), T value)
{
	for (auto& style : styleArr)
	{
		(*style.*childFunc)(value);
	}
}

template <typename T, typename TItem1, typename TItem2>
std::optional<T> GetCompositeValue(const std::vector<std::shared_ptr<TItem1>>& styleArr, std::optional<T> (TItem2::*childFunc)() const)
{
	if (!styleArr.size())
	{
		return std::nullopt;
	}

	std::optional<T> result = (*styleArr.front().*childFunc)();
	if (!result.has_value())
	{
		return std::nullopt;
	}

	if (std::all_of(styleArr.begin(), styleArr.end(), [&](const std::shared_ptr<TItem1>& style) {
			return (*style.*childFunc)() == result;
		}))
	{
		return result;
	}
	return std::nullopt;
}