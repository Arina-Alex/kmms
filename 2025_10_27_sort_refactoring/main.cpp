#include "io.hpp"
#include "sort.hpp"

int main () {
    int arr[] = {3, 11, 25, 20, 7, 9, 1};
    const int arr_size = sizeof(arr)/sizeof(arr[0]);

    mal::print_arr("Массив до сортировки:", arr, arr_size);

    mal::sort::shell_sort(arr, arr_size);

    mal::print_arr("Массив после сортировки:", arr, arr_size);

    return 0;
}
