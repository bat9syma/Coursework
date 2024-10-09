#pragma once
#include "DigitalCounter.h"

class Stopwatch : public DigitalCounter
{
private:
	bool isRunning; // Flag indicating whether the stopwatch is running
	std::string name;

public:

	// Default constructor
	Stopwatch();	
	// Constructor with parameters
	Stopwatch(std::string name, double min, double max);


	void start(); // Start the stopwatch
	void stop(double newValue); // Stop the stopwatch
	bool isStarted() const; // Check if the stopwatch is running
	void display(std::ostream& os) const override; // Display the stopwatch value

	// Methods for setting and getting the participant's name
	void setName(const std::string& newName);
	std::string getName() const;
};

