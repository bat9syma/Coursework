#include "DigitalCounter.h"

DigitalCounter::DigitalCounter() : minimum(10.0), maximum(15.0), value(minimum) 
{
    checkBounds();
}

DigitalCounter::DigitalCounter(double min, double max) : minimum(min), maximum(max), value(min)
{
    checkBounds();
}

DigitalCounter::DigitalCounter(const DigitalCounter& other) : minimum(other.minimum), maximum(other.maximum), value(other.value)
{
    checkBounds();
}

DigitalCounter::DigitalCounter(DigitalCounter&& other) : minimum(other.minimum), maximum(other.maximum), value(other.value) 
{
    other.minimum = 0;
    other.maximum = 0;
    other.value = 0;
    checkBounds();
}

DigitalCounter::~DigitalCounter() {}

void DigitalCounter::setMinimum(double min)
{
    minimum = min;
    checkBounds();
}

void DigitalCounter::setMaximum(double max)
{
    maximum = max;
    checkBounds();
}

void DigitalCounter::setValue(double value) 
{
    if (value <= maximum && value >= minimum)
    {
        this->value = value;
    }
    else if (value < minimum)
    {
        this->value = minimum;
    }
    else 
    {
        this->value = maximum;
    }
    checkBounds();
}

double DigitalCounter::getValue() const 
{
    return value;
}

double DigitalCounter::getMinimum() const 
{
    return minimum;
}

double DigitalCounter::getMaximum() const
{
    return maximum;
}

void DigitalCounter::checkBounds()
{
    if (value < minimum)
    {
        value = minimum;
    }
    if (value > maximum) 
    {
        value = maximum;
    }
}

DigitalCounter& DigitalCounter::operator=(const DigitalCounter& other)
{
    if (this != &other)
    {
        minimum = other.minimum;
        maximum = other.maximum;
        value = other.value;
    }
    return *this;
}

DigitalCounter& DigitalCounter::operator=(DigitalCounter&& other) 
{
    if (this != &other) 
    {
        minimum = other.minimum;
        maximum = other.maximum;
        value = other.value;
        other.minimum = 0;
        other.maximum = 0;
        other.value = 0;
    }
    return *this;
}

DigitalCounter& DigitalCounter::operator++() 
{
    ++value;
    return *this;
}

DigitalCounter DigitalCounter::operator++(int)
{
    DigitalCounter temp(*this);
    temp.value = value + 1;
    return temp;
}

DigitalCounter& DigitalCounter::operator--()
{
    --value;
    return *this;
}

DigitalCounter DigitalCounter::operator--(int) 
{
    DigitalCounter temp(*this);
    temp.value = value - 1;
    return temp;
}

DigitalCounter& DigitalCounter::operator+=(int increment)
{
    value += increment;
    return *this;
}

DigitalCounter& DigitalCounter::operator-=(int decrement)
{
    value -= decrement;
    return *this;
}

void DigitalCounter::display(std::ostream& os) const 
{
    os << " Current value: " << getValue() << std::endl;
}

void DigitalCounter::input(std::istream& is)
{
    double newValue;
    is >> newValue;
    if (newValue < minimum) 
    {
        newValue = minimum;
    }
    else if (newValue > maximum) 
    {
        newValue = maximum;
    }
    value = newValue;
}

std::ostream& operator<<(std::ostream& os, const DigitalCounter& counter)
{
    counter.display(os);
    return os;
}

std::istream& operator>>(std::istream& is, DigitalCounter& counter)
{
    counter.input(is);
    return is;
}