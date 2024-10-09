#include "Stopwatch.h"

Stopwatch::Stopwatch() : DigitalCounter(), isRunning(false) {}

Stopwatch::Stopwatch(std::string name, double min, double max) : DigitalCounter(min, max), isRunning(false), name(name) {}

void Stopwatch::start() 
{
    isRunning = true;
}

void Stopwatch::stop(double newValue) 
{
    if (isRunning) 
    {
        isRunning = false;
        setValue(newValue);
    }
}

bool Stopwatch::isStarted() const 
{

    return isRunning;
}

void Stopwatch::display(std::ostream& os) const 
{
    if (isRunning)
    {
        os << "Running";
    }
    else 
    {
        DigitalCounter::display(os);
    }
}

void Stopwatch::setName(const std::string& newName)
{
    name = newName;
}

std::string Stopwatch::getName() const
{
    return name;
}


