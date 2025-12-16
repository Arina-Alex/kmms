#include "menu_functions.hpp"

#include <cstdlib>

#include <iostream>

const mal::MenuItem* mal::show_menu(const MenuItem* current) {
    std::cout << "Читалка приветствует тебя" << std::endl;
    for (int i = 1; i < current->children_count; i++) {
        std::cout << current->children[i]->title << std::endl;
    }
    std::cout << current->children[0]->title << std::endl;
    std::cout << "Выбор >";

    int user_input;
    std::cin >> user_input;
	std::cout << std::endl;

    return current->children[user_input];
}

const mal::MenuItem* mal::exit(const MenuItem* current) {
    std::exit(0);
}

const mal::MenuItem* mal::read_pyshkin(const MenuItem* current) {
    std::cout << "Переходим к произведениям Пушкина" << std::endl;
    return current->parent;
}

const mal::MenuItem* mal::read_lermontov(const MenuItem* current) {
    std::cout << "Переходим к произведениям Лермонтова" << std::endl;
    return current->parent;
}

const mal::MenuItem* mal::read_krylov(const MenuItem* current) {
    std::cout << "Переходим к произведениям Крылова" << std::endl;
    return current->parent;
}

const mal::MenuItem* mal::read_go_back(const MenuItem* current) {
    return current->parent;
}

const mal::MenuItem* mal::read_dybrovsky(const MenuItem* current) {
    std::cout << "Приятного чтения!" << std::endl;
    return current->parent;
}

const mal::MenuItem* mal::read_onegin(const MenuItem* current) {
    std::cout << "Приятного чтения!" << std::endl;
    return current->parent;
}

const mal::MenuItem* mal::read_zimny_vecher(const MenuItem* current) {
    std::cout << "Приятного чтения!" << std::endl;
    return current->parent;
}

const mal::MenuItem* mal::read_go_back_writers(const MenuItem* current) {
    return current->parent->parent;
}

