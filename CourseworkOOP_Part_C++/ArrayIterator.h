#pragma once
#include <vector>

template <typename T>

class ArrayIterator
{
private:
    // An iterator that points to the current element of the vector
    typename std::vector<T>::iterator iter;

public:
    // Default constructor
    ArrayIterator() = default;
    // Constructor that initializes the iterator with the specified value
    ArrayIterator(typename std::vector<T>::iterator iter) : iter(iter) {}

    // Overloaded dereference operator, returns a reference to the current element
    T& operator*()
    {
        return *iter;
    }

    // Overloaded prefix increment operator, moves the iterator to the next element
    ArrayIterator<T>& operator++()
    {
        ++iter;
        return *this;
    }

    // Overloaded arrow operator, returns a pointer to the current element
    T* operator->()
    {
        return &(*iter);
    }

    // Overloaded comparison operator for inequality, compares two iterators
    bool operator!=(const ArrayIterator<T>& other) const
    {
        return iter != other.iter;
    }
};
