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
std::size_t Vector<T>::get_size() const noexcept {
	return size;
}

template<typename T>
bool Vector<T>::has_item(const T& value) const noexcept {
	for (std::size_t i = 0; i < size; i++) {
		if (arr[i] == value) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Vector<T>::insert(const std::size_t position, const T& value) {
	if (position > size) {
		return false;
	}

	if (size == capacity) {
		std::size_t new_capacity = capacity * 2;
		T* new_arr = new T[new_capacity];

		for (std::size_t i = 0; i < size; i++) {
			new_arr[i] = arr[i];
		}
		delete[] arr;
		arr = new_arr;
		capacity = new_capacity;
	}

	for (std::size_t i = size; i > position; i--) {
		arr[i] = arr[i-1];
	}
	arr[position] = value;
	size++;

	return true;
}

template<typename T>
void Vector<T>::print() const noexcept {
	std::cout << "[";
	for (std::size_t i = 0; i < size; i++) {
		std::cout << arr[i];
		if (i < size - 1) {
            std::cout << ", ";
        }
	}
	std::cout << "]" << std::endl;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
	insert(size, value);
}

template<typename T>
bool Vector<T>::remove_first(const T& value) {
	for (std::size_t i = 0; i < size; i++) {
		if (arr[i] == value) {
			for (std::size_t j = i; j < size - 1; j++) {
				arr[j] = arr[j+1];
			}
			size--;
			return true;
		}
	}
	return false;
}
