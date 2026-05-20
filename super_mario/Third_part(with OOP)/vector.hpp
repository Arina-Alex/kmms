#pragma once

#include <cstddef>
		
namespace mal {
	template <typename T> 
	class Vector {
		private:
			static const std::size_t START_CAPACITY;

			T* arr = nullptr;
			std::size_t capacity = START_CAPACITY;
			std::size_t size = 0;

			void resize();

		public:
			Vector();
			Vector(const Vector&) = delete;
			Vector& operator = (const Vector&) = delete;
			~Vector();
			
			std::size_t get_size() const noexcept;
			T& operator[](std::size_t index);
			const T& operator[](std::size_t index) const;
			void push_back(const T& value);
			void remove(std::size_t index);
			void clear();

	};
}


