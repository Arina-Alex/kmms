#include "io.hpp"
#include "sort.hpp"

int main() {
    int arr[] = {3, 15, 6, 7, 1, 11};
	const int arr_size = sizeof(arr) / sizeof(arr[0]);
	
	biv::print("Массив перед сортировкой:", arr, arr_size);
    
    biv::sort::bubble_sort(arr, arr_size);

    biv::print("Массив после сортировки:", arr, arr_size);

    return 0;
}
