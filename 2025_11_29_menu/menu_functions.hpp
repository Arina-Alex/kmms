#pragma once

#include "menu.hpp"

namespace mal {
    const MenuItem* show_menu(const MenuItem* current);
    const MenuItem* exit(const MenuItem* current);

    const MenuItem* read_pyshkin(const MenuItem* current);
    const MenuItem* read_lermontov(const MenuItem* current);
    const MenuItem* read_krylov(const MenuItem* current);
    const MenuItem* read_go_back(const MenuItem* current);

    const MenuItem* read_dybrovsky(const MenuItem* current);
    const MenuItem* read_onegin(const MenuItem* current);
    const MenuItem* read_zimny_vecher(const MenuItem* current);
    const MenuItem* read_go_back_writers(const MenuItem* current);
}