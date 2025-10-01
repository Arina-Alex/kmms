#include <iostream>
#include <string>

int main() {
	std::cout << "Введите слово: ";
	std::string str;
	std::getline(std::cin, str);
	std::cout << str << std::endl;
}
