#pragma once

#include <cstddef>
#include <iostream>
		
namespace mal {
	template <typename T> 
	class Vector {
		private:
			static const std::size_t START_CAPACITY = 4;

			T* arr = nullptr;
			std::size_t capacity = START_CAPACITY;
			std::size_t size = 0;

			void resize() {
				std::size_t new_capacity = capacity * 2;
				T* new_arr = new T[new_capacity];
				
				for (std::size_t i = 0; i < size; ++i) {
					new_arr[i] = arr[i];
				}
				
				delete[] arr;
				arr = new_arr;
				capacity = new_capacity;
			}

		public:
			Vector(): capacity(START_CAPACITY), size(0) {
				arr = new T[capacity];
			}
			Vector(const Vector&) = delete;
			Vector& operator = (const Vector&) = delete;

			~Vector() {
				delete[] arr;
				arr = nullptr;
				capacity = 0;
				size = 0;
			}
			
			std::size_t get_size() const noexcept { 
				return size;
			}

			T& operator[](std::size_t index) {
				if (index >= size) {
					throw std::out_of_range("Index out of range");
				}
				return arr[index];
			}

			const T& operator[](std::size_t index) const {
				if (index >= size) {
					throw std::out_of_range("Index out of range");
				}
				return arr[index];
			}

			void push_back(const T& value) {
				if (size == capacity) {
					resize();
				}
				arr[size++] = value;
			}

			void remove(std::size_t index) {
				if (index >= size) return;
				for (std::size_t i = index; i < size - 1; ++i) {
					arr[i] = arr[i + 1];
				}
				--size;
			}

			void clear() {
				delete[] arr;
				capacity = START_CAPACITY;
				size = 0;
				arr = new T[capacity];
			}
	};
}

