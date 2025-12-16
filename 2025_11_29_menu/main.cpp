#include <iostream>

#include "menu.hpp"
#include "menu_items.hpp"
#include "menu_functions.hpp"

int main () {
    const mal::MenuItem* current = &mal::MAIN;
	do {
	    current = current->func(current);
	} while (true);
    
	return 0;
}
