#pragma once

#include <iostream>

class DigitalCounter 
{
private:
    // Possible counter values
    double value; 
    double minimum; 
    double maximum; 

public:
    // The default constructor
    DigitalCounter();
    // Constructor specifying the minimum and maximum values
    DigitalCounter(double min, double max);
    // Copy constructor
    DigitalCounter(const DigitalCounter& other);
    // Move constructor
    DigitalCounter(DigitalCounter&& other);
    // Destructor
    virtual ~DigitalCounter();

    // Setting values
    void setMinimum(double min);
    void setMaximum(double max);
    void setValue(double value);
    
    // Check for a range
    void checkBounds();

    // Getting the values
    double getValue() const;
    double getMinimum() const;
    double getMaximum() const;  

    // Operator () to set data field values
    void operator()(double newValue, double newMinimum, double newMaximum) 
    {
        value = newValue;
        minimum = newMinimum;
        maximum = newMaximum;
        checkBounds();
    }

    // Operators overloading
    DigitalCounter& operator= (const DigitalCounter& other);
    DigitalCounter& operator= (DigitalCounter&& other);
    DigitalCounter& operator++();
    DigitalCounter operator++(int);
    DigitalCounter& operator--();
    DigitalCounter operator--(int);
    DigitalCounter& operator+=(int increment);
    DigitalCounter& operator-=(int decrement);

    // Virtual method for outputting and inputting the counter value
    virtual void display(std::ostream& os) const;
    virtual void input(std::istream& is);

    // Friendly functions for outputting and inputting the counter value to the stream
    friend std::ostream& operator << (std::ostream& os, const DigitalCounter& counter);
    friend std::istream& operator >> (std::istream& is, DigitalCounter& counter);
};
