#include "ArrayIterator.h"

template <typename T>
ArrayIterator<T>::ArrayIterator(const std::vector<T>& items) : counter(items.cbegin()), index(0) {}


template <typename T>
const T& ArrayIterator<T>::getNext()
{
    return *counter++;
}

template<typename T>
const T& ArrayIterator<T>::operator*() const
{
    return *counter;
}

template <typename T>
ArrayIterator<T>& ArrayIterator<T>::operator++()
{
    ++index;
    return *this;
}

template <typename T>
bool ArrayIterator<T>::operator!=(const ArrayIterator<T>& other) const
{
    return counter != other.counter;
}