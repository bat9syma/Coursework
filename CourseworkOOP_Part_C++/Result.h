#pragma once
#include "Stopwatch.h"
#include "ArrayIterator.h"
#include <algorithm>

class Result 
{
private:
	// Vector to store race results
	std::vector<Stopwatch> results;
public:
	// Events with the result of the race
	void addRes(const Stopwatch& result);
	Stopwatch getMinTime() const;
	Stopwatch getMaxTime() const;
	double getAvgTime() const; 

	// Vector to get all race results and three winners
	std::vector<Stopwatch> getResults() const;
	std::vector<Stopwatch> getBestOf3();
};

