#include "Result.h"

void Result::addRes(const Stopwatch& result) 
{
	results.push_back(result);
}

Stopwatch Result::getMinTime() const
{
	if (results.empty())
	{
		throw std::runtime_error("There are no results, you need to fill in the race data!");
	}

	// Finding the element with the smallest value in the vector
	auto minRes = std::min_element(cbegin(results), cend(results),
		[](const Stopwatch& a,const Stopwatch& b)
		{
			return a.getValue() < b.getValue();
		});

	return (*minRes);
}

Stopwatch Result::getMaxTime() const
{
	if (results.empty())
	{
		throw std::runtime_error("There are no results, you need to fill in the race data!");
	}

	// Finding the element with the largest value in the vector
	auto maxRes = std::max_element(cbegin(results), cend(results),
		[](const Stopwatch& a, const Stopwatch& b)
		{
			return a.getValue() < b.getValue();
		});

	return (*maxRes);
}

double Result::getAvgTime() const
{
	if (results.empty())
	{
		throw std::runtime_error("There are no results, you need to fill in the race data!");
	}

	double sum = 0;
	// Summation of run time values ​​in a vector
	for (const auto& stopwatch : results)
	{
		sum += stopwatch.getValue();
	}

	return sum / results.size();
}

std::vector<Stopwatch> Result::getResults() const
{
	return results;
}

std::vector<Stopwatch> Result::getBestOf3()
{
	std::vector<Stopwatch> myTop;

	if (results.empty())
	{
		return myTop;
	}


	// Using a standard iterator for sorting
	std::sort(results.begin(), results.end(), [](const Stopwatch& a, const Stopwatch& b)
		{
			return a.getValue() < b.getValue();
		});

	// Save the third smallest result
	auto thirdMinIter = results.begin() + 2;

	ArrayIterator<Stopwatch> beginIter(results.begin());
	ArrayIterator<Stopwatch> endIter(results.end());

	// Add these values ​​to a new vector
	for (ArrayIterator<Stopwatch> iter = beginIter; iter != endIter; ++iter)
	{
		if (iter->getValue() <= thirdMinIter->getValue())
		{
			myTop.push_back(*iter);
		}
	}

	return myTop;
}

	