#include <iostream>

#include "bubble_sort.hpp"

int main() {
	std::vector<int> arr = {1, 0, 2, 5, 3, 11}; 
	std::cout << "Maccив до сортировки:";
	for (int i = 0; i < arr.size(); i++) {
		std::cout << ' ' << arr[i];
	}
	std::cout << std::endl;
	
	mal::bubble_sort(arr);

	std::cout << "Maccив после сортировки:";
	for (int i = 0; i < arr.size(); i++){
		std::cout << ' ' << arr[i];
	}
	
	std::cout << std::endl;
	
	std::system("PAUSE"); 
	return 0;
}