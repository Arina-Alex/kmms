#include "io.hpp"
#include <iostream>

void mal::print_arr(const char* comment, int* arr, const int size) {
    std::cout << comment << " ";

    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}