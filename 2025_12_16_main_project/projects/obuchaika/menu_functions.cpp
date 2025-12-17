#include "menu_functions.hpp"

#include <cstdlib>
#include <iostream>

const mal::MenuItem* mal::show_menu(const MenuItem* current) {
	std::cout << "Обучайка приветствует тебя!" << std::endl;
	for (int i = 1; i < current->children_count; i++) {
		std::cout << current->children[i]->title << std::endl;
	}
	std::cout << current->children[0]->title << std::endl;
	std::cout << "Обучайка > ";
	
	int user_input;
	std::cin >> user_input;
	std::cout << std::endl;
	
	return current->children[user_input];
}

const mal::MenuItem* mal::exit(const MenuItem* current) {
	std::exit(0);
}

//
const mal::MenuItem* mal::study_algebra(const MenuItem* current) {
	
	std::cout << "Переходим к изучению алгебры!" << std::endl << std::endl;
	return current->parent;
}

const mal::MenuItem* mal::study_analysis(const MenuItem* current) {
	
	std::cout << "Переходим к изучению математического анализа!" << std::endl << std::endl;
	return current->parent;
}

const mal::MenuItem* mal::study_go_back(const MenuItem* current) {
	return current->parent;
}

const mal::MenuItem* mal::study_summ(const MenuItem* current) {
	
	std::cout << "Изучаем сложение!" << std::endl << std::endl;
	return current->parent;
}

const mal::MenuItem* mal::study_substract(const MenuItem* current) {

	std::cout << "Изучаем вычитание!" << std::endl;
	return current->parent;
}

const mal::MenuItem* mal::study_multiply(const MenuItem* current) {

	std::cout << "Изучаем умножение!" << std::endl;
	return current->parent;
}

const mal::MenuItem* mal::study_divide(const MenuItem* current) {

	std::cout << "Изучаем деление!" << std::endl << std::endl;
	return current->parent;
}

const mal::MenuItem* mal::study_go_back_subjects(const MenuItem* current) {
	return current->parent->parent;
}

const mal::MenuItem* mal::study_diff(const MenuItem* current) {
	std::cout << "Изучаем дифференциальное исчисление!" << std::endl << std::endl;
	return current->parent;
}
	
const mal::MenuItem* mal::study_integral(const MenuItem* current) {
	std::cout << "Изучаем интегральное исчисление!" << std::endl << std::endl;
	return current->parent;
}
	
	