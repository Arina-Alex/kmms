#include  "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const mal::MenuItem mal::READ_DUBROVSKY = {
	"1 - Хочу прочитать произведение Дубровский", mal::read_dybrovsky, &mal::READ_PUSHKIN
};
const mal::MenuItem mal::READ_ONEGIN = {
	"2 - Хочу прочитать произведение Евгений Онегин", mal::read_onegin, &mal::READ_PUSHKIN
};
const mal::MenuItem mal::READ_ZIMNY_VECHER = {
	"3 - Хочу прочитать произведение Зимний вечер", mal::read_zimny_vecher, &mal::READ_PUSHKIN
};
const mal::MenuItem mal::READ_GO_BACK_WRITERS = {
	"0 - Вернуться к выбору писателей", mal::read_go_back_writers, &mal::READ_PUSHKIN
};

namespace {
	const mal::MenuItem* const pyshkin_children[] = {
		&mal::READ_GO_BACK_WRITERS,
		&mal::READ_DUBROVSKY,
		&mal::READ_ONEGIN,
		&mal::READ_ZIMNY_VECHER
	};
	const int pyshkin_size = sizeof(pyshkin_children) / sizeof(pyshkin_children[0]);
}

const mal::MenuItem mal::READ_PUSHKIN = {
	"1 - Хочу читать произведения Пушкина ", mal::show_menu, &mal::READ, pyshkin_children, pyshkin_size
};
const mal::MenuItem mal::READ_LERMONTOV = {
	"2 - Хочу читать произведения Лермонтова", mal::show_menu, &mal::READ
};
const mal::MenuItem mal::READ_KRYLOV = {
	"3 - Хочу читать произведения Крылова", mal::show_menu, &mal::READ
};
const mal::MenuItem mal::READ_GO_BACK = {
	"0  - Выйти в главное меню", mal::read_go_back, &mal::MAIN
};

namespace {
	const mal::MenuItem* const read_children[] = {
		&mal::READ_GO_BACK,
		&mal::READ_PUSHKIN,
		&mal::READ_LERMONTOV,
        &mal::READ_KRYLOV
	};
	const int read_size = sizeof(read_children) / sizeof(read_children[0]);
}

const mal::MenuItem mal::READ = {
	"1 - Хочу читать произведения русских писателей", mal::show_menu, &mal::MAIN, read_children, read_size
};
const mal::MenuItem mal::EXIT = {
	"0 - Пойду спать", mal::exit, &mal::MAIN
};

namespace {
    const mal::MenuItem* const main_children[] = {
        &mal::EXIT,
		&mal::READ
        
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const mal::MenuItem mal::MAIN = {
	nullptr, mal::show_menu, nullptr, main_children, main_size
};