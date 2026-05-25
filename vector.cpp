#include "vector.hpp"

#include <iostream>

using mal::Vector;

template <typename T>
const std::size_t Vector<T>::START_CAPACITY = 4;

template<typename T>
Vector<T>::Vector() {
	arr = new T[START_CAPACITY];
	capacity = START_CAPACITY;
	size = 0;
}

template<typename T>
Vector<T>::~Vector() {
	delete[] arr;
	arr = nullptr;
	capacity = 0;
	size = 0;
}

template<typename T>
T& Vector<T>::operator[](std::size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
const T& Vector<T>::operator[](std::size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template<typename T>
void Vector<T>::resize() {
    std::size_t new_capacity = capacity * 2;
    T* new_arr = new T[new_capacity];
    
    for (std::size_t i = 0; i < size; ++i) {
        new_arr[i] = arr[i];
    }
    
    delete[] arr;
    arr = new_arr;
    capacity = new_capacity;
}

template<typename T>
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}


template<typename T>
void Vector<T>::push_back(const T& value) {
	if (size == capacity) {
		resize();
	}
	arr[size++] = value;
}

template<typename T>
void Vector<T>::remove(std::size_t index) {
	if (index >= size) return;
    
    for (std::size_t i = index; i < size - 1; ++i) {
        arr[i] = arr[i + 1];
    }
    --size;
}

template<typename T>
void Vector<T>::clear() {
    delete[] arr;
    capacity = START_CAPACITY;
    size = 0;
    arr = new T[capacity];
}

template class Vector<class Object>;
template class Vector<class Platform>;
template class Vector<class Enemy>;
template class Vector<class Coin>;
