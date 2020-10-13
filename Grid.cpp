#include "Grid.h"
#include "Util.h"

int Grid::kierros_laskuri = 0;

Grid::Grid()
    : vaikeus_aste {0} {
    unsigned int x {48};
    unsigned int y {48};
    for(unsigned int i {0}; i < MAX_GRID_SIZE; i++) {
        std::vector <char> temp;
        for(unsigned int j {0}; j < MAX_GRID_SIZE; j++) {
            if(i == 0) {
                temp.push_back(x);
                x++;
            } else if(j == 0) {
                temp.push_back(y);
            } else {
                temp.push_back(EMPTY_SPOT_ON_THE_GRID);
            }
        }
        grid.push_back(temp);
        y++;
    }
}

Grid::~Grid() {

}

void Grid::display_grid() const {
    for(unsigned int i {0}; i < MAX_GRID_SIZE; i++) {
        for(unsigned int j {0}; j < MAX_GRID_SIZE; j++) {
            std::cout << grid.at(i).at(j);
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

bool Grid::update_grid(const int x, const int y, Pelaajat *pelaaja) {
    //TARKISTETAAN ONKKO KORDINAATTIEN SIJAINTI SALLITTU.
    //JOS ON, PÄIVITETÄÄN MATRIISI
    if(grid.at(y).at(x) != EMPTY_SPOT_ON_THE_GRID) {
        return false;
    } else {
        grid.at(y).at(x) = pelaaja->get_type();
        return true;
    }
}

bool Grid::computer_strategy(int &x, int &y, Pelaajat *tietokone) {
    //JOS TIETOKONE NÄKEE ETTÄ OLET TEKEMÄSSÄ SUORAA NIIN SE MENEE ESTÄMÄÄN SITÄ
    if((vaaka(x, y, tietokone) == true || pysty(x, y, tietokone) == true || risti(x, y, tietokone) == true) && get_vaikeus_aste() >= KESKITASO)
        return true;
    //JOS SE EI NÄE UHKAA NIIN SE YRITTÄÄ TEHDÄ OMAA SUORAA
    if(ei_uhkaa(x, y, tietokone) == false && get_kierros_laskuri() != 0 && get_vaikeus_aste() == MAHDOTON)
        return true;
    return false;
}

bool Grid::vaaka(int &x, int &y, Pelaajat *tietokone) {
    for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
        int counter {0};
        for(unsigned int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            if(grid.at(i).at(j) == tietokone->get_counter_type()) {
                counter++;
            } else if(grid.at(i).at(j) == tietokone->get_type()) {
                counter--;
            }
        }

        if(counter == -2) {
            for(unsigned int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
                    return true;
                }
            }
        }

        if(counter == MELKEIN_SUORA) {
            for(unsigned int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
                    //return true;
                }
            }
        }
    }
    if(x == 0 && y == 0)
        return false;
    else
        return true;
}

bool Grid::pysty(int &x, int &y, Pelaajat *tietokone) {
    for(unsigned int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
        int counter {0};
        for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
            if(grid.at(i).at(j) == tietokone->get_counter_type()) {
                counter++;
            } else if(grid.at(i).at(j) == tietokone->get_type()) {
                counter--;
            }
        }

        if(counter == -2) {
            for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
                    return true;
                }
            }
        }

        if(counter == MELKEIN_SUORA) {
            for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
                    //return true;
                }
            }
        }
    }
    if(x == 0 && y == 0)
        return false;
    else
        return true;
}

bool Grid::risti(int &x, int &y, Pelaajat *tietokone) {
    bool on_tosi {false};
    if(grid.at(1).at(1) == tietokone->get_counter_type() && grid.at(2).at(2) == tietokone->get_counter_type() && grid.at(3).at(3) == EMPTY_SPOT_ON_THE_GRID) {
        x = 3;
        y = 3;
        on_tosi = true;
    } else if(grid.at(3).at(3) == tietokone->get_counter_type() && grid.at(2).at(2) == tietokone->get_counter_type()  && grid.at(1).at(1) == EMPTY_SPOT_ON_THE_GRID) {
        x = 1;
        y = 1;
        on_tosi = true;
    } else if(grid.at(1).at(1) == tietokone->get_counter_type() && grid.at(3).at(3) == tietokone->get_counter_type() && grid.at(2).at(2) == EMPTY_SPOT_ON_THE_GRID) {
        x = 2;
        y = 2;
        on_tosi = true;
    } else if(grid.at(1).at(3) == tietokone->get_counter_type() && grid.at(2).at(2) == tietokone->get_counter_type() && grid.at(3).at(1) == EMPTY_SPOT_ON_THE_GRID) {
        x = 1;
        y = 3;
        on_tosi = true;
    } else if(grid.at(2).at(2) == tietokone->get_counter_type() && grid.at(3).at(1) == tietokone->get_counter_type() && grid.at(1).at(3) == EMPTY_SPOT_ON_THE_GRID) {
        x = 3;
        y = 1;
        on_tosi = true;
    } else if(grid.at(1).at(3) == tietokone->get_counter_type() && grid.at(3).at(1) == tietokone->get_counter_type() && grid.at(2).at(2) == EMPTY_SPOT_ON_THE_GRID) {
        x = 2;
        y = 2;
        on_tosi = true;
    }
    return on_tosi;
}

bool Grid::ei_uhkaa(int &x, int &y, Pelaajat *tietokone) {
    bool ei_uhkaa {true};
    if(grid.at(3).at(3) == EMPTY_SPOT_ON_THE_GRID) {
        x = 3;
        y = 3;
        ei_uhkaa = false;
    }
    if(grid.at(1).at(3) == EMPTY_SPOT_ON_THE_GRID) {
        x = 3;
        y = 1;
        ei_uhkaa = false;
    }
    if(grid.at(3).at(1) == EMPTY_SPOT_ON_THE_GRID) {
        x = 1;
        y = 3;
        ei_uhkaa = false;
    }
    if(grid.at(1).at(1) == EMPTY_SPOT_ON_THE_GRID) {
        x = 1;
        y = 1;
        ei_uhkaa = false;
    }
    return ei_uhkaa;
}

bool Grid::check_winning_condition(Pelaajat *pelaaja) {
    if(x_axis(pelaaja) == SUORA || y_axis(pelaaja) == SUORA || criss_cross(pelaaja) == SUORA || is_grid_full() == true)
        return true;
    else
        return false;
}

int Grid::x_axis(Pelaajat *pelaaja) {
    for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
        unsigned int counter {0};
        for(unsigned int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            if(grid.at(i).at(j) == pelaaja->get_type())
                counter++;
        }
        if(counter == SUORA) {
            pelaaja->set_voitto_status(true);
            return SUORA;
        }
    }
    return EI_SUORAA;
}

int Grid::y_axis(Pelaajat *pelaaja) {
    for(unsigned int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
        unsigned int counter {0};
        for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
            if(grid.at(i).at(j) == pelaaja->get_type())
                counter++;
        }
        if(counter == SUORA) {
            pelaaja->set_voitto_status(true);
            return SUORA;
        }
    }
    return EI_SUORAA;
}

int Grid::criss_cross(Pelaajat *pelaaja) {
    if(grid.at(1).at(1) == pelaaja->get_type() && grid.at(2).at(2) == pelaaja->get_type() && grid.at(3).at(3) == pelaaja->get_type()) {
        pelaaja->set_voitto_status(true);
        return SUORA;
    } else if(grid.at(3).at(1) == pelaaja->get_type() && grid.at(2).at(2) == pelaaja->get_type() && grid.at(1).at(3) == pelaaja->get_type()) {
        pelaaja->set_voitto_status(true);
        return SUORA;
    }
    return EI_SUORAA;
}

bool Grid::is_grid_full() {
    for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
        for(unsigned int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID)
                return false;
        }
    }
    return true;
}