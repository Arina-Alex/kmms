#include  "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const mal::MenuItem mal::STUDY_SUMM = {
	"1 - Хочу научиться складывать!", mal::study_summ, &mal::STUDY_ALGEBRA
};
const mal::MenuItem mal::STUDY_SUBSTRACT = {
	"2 - Хочу научиться вычитать!", mal::study_substract, &mal::STUDY_ALGEBRA
};
const mal::MenuItem mal::STUDY_MULTIPLY = {
	"3 - Хочу научиться умножать!", mal::study_multiply, &mal::STUDY_ALGEBRA
};
const mal::MenuItem mal::STUDY_DIVIDE = {
	"4 - Хочу научиться делить!", mal::study_divide, &mal::STUDY_ALGEBRA
};
const mal::MenuItem mal::STUDY_GO_BACK_SUBJECTS = {
	"0 - Вернуться к выбору предметов!", mal::study_go_back_subjects, &mal::STUDY_ALGEBRA
};

namespace {
	const mal::MenuItem* const algebra_children[] = {
		&mal::STUDY_GO_BACK_SUBJECTS,
		&mal::STUDY_SUMM,
		&mal::STUDY_SUBSTRACT,
		&mal::STUDY_MULTIPLY,
		&mal::STUDY_DIVIDE
	};
	const int algebra_size = sizeof(algebra_children) / sizeof(algebra_children[0]);
}

const mal::MenuItem mal::STUDY_DIFF = {
	"1 - Хочу изучить дифференциальное исчисление!", mal::study_diff, &mal::STUDY_ANALYSIS
};

const mal::MenuItem mal::STUDY_INTEGRAL = {
	"2 - Хочу изучить интегральное исчисление!", mal::study_integral, &mal::STUDY_ANALYSIS
};

namespace {
	const mal::MenuItem* const analysis_children[] = {
		&mal::STUDY_GO_BACK_SUBJECTS,
		&mal::STUDY_DIFF,
		&mal::STUDY_INTEGRAL,
	};
	const int analysis_size = sizeof(analysis_children) / sizeof(analysis_children[0]);
}

const mal::MenuItem mal::STUDY_ALGEBRA = {
	"1 - Хочу изучать алгебру!", mal::show_menu, &mal::STUDY, algebra_children, algebra_size
};

const mal::MenuItem mal::STUDY_ANALYSIS = {
	"2 - Хочу изучать математический анализ!", mal::show_menu, &mal::STUDY, analysis_children, analysis_size
};

const mal::MenuItem mal::STUDY_GO_BACK = {
	"0  - Выйти в главное меню!", mal::study_go_back, &mal::MAIN
};

namespace {
	const mal::MenuItem* const study_children[] = {
		&mal::STUDY_GO_BACK,
		&mal::STUDY_ALGEBRA,
		&mal::STUDY_ANALYSIS
	};
	const int study_size = sizeof(study_children) / sizeof(study_children[0]);
}




const mal::MenuItem mal::STUDY = {
	"1 - Хочу учиться математике!", mal::show_menu, &mal::MAIN, study_children, study_size
};
const mal::MenuItem mal::EXIT = {
	"0 - Я лучше пойду полежу...", mal::exit, &mal::MAIN
};

namespace {
	const mal::MenuItem* const main_children[] = {
		&mal::EXIT,
		&mal::STUDY
	};
	const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const mal::MenuItem mal::MAIN = {
	nullptr, mal::show_menu, nullptr, main_children, main_size
};