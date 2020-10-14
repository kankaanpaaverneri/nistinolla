#include "Grid.h"
#include "Util.h"

int Grid::kierros_laskuri = 0; //ALUSTETAAN STAATTINEN kierros_laskuri NOLLAAN

Grid::Grid()
    : vaikeus_aste {0} {
    //RAKENNETAAN MATRIISI
    int x {48}; //ASCII ARVO 48 ON 0
    int y {48}; //ASCII ARVO 48 ON 0
    for(int i {0}; i < MAX_GRID_SIZE; i++) {
        std::vector <char> temp;
        for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            if(i == MIN_GRID_SIZE) {
                temp.push_back(x);
                x++;
            } else if(j == MIN_GRID_SIZE) {
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
    //DESTRUCTOR Grid OLIOLLE
}

void Grid::display_grid() const { //TULOSTAA RUUDUKON PÄÄTTELLE
    for(int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
        std::cout << std::endl;
        for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            std::cout << grid.at(i).at(j);
            if(i != 0 && j != 0 && j != 3)
                std::cout << " | ";
            else
                std::cout << "   ";
        }
        if(i == 0 || i == 3) {
            std::cout << std::endl;
        } else {
            std::cout << std::endl;
            std::cout << "   ___ ___ ___";
            std::cout << std::endl;
        }
    }
}

bool Grid::update_grid(const int x, const int y, Pelaajat *pelaaja) {
    //TARKISTETAAN ONKKO KOORDINAATTIEN SIJAINTI SALLITTU.
    //JOS ON, PÄIVITETÄÄN MATRIISI PELAAJAN MERKILLÄ
    if(grid.at(y).at(x) != EMPTY_SPOT_ON_THE_GRID) {
        return false;
    } else {
        grid.at(y).at(x) = pelaaja->get_type();
        return true;
    }
}

bool Grid::computer_strategy(int &x, int &y, Pelaajat *tietokone) {
    //JOS tietokone NÄKEE ETTÄ pelaaja ON TEKEMÄSSÄ SUORAA, tietokone MENEE ESTÄMÄÄN SITÄ
    if((vaaka(x, y, tietokone) == true || pysty(x, y, tietokone) == true || risti(x, y, tietokone) == true) && get_vaikeus_aste() >= KESKITASO)
        return true;
    //JOS ei_uhkaa ON TOSI, PALAUTETAAN false ARVO JA tietokone VALITSEE KORDINAATIT SATUNNAISESTI siirto() FUNKTIOSSA
    if(ei_uhkaa(x, y, tietokone) == false && get_kierros_laskuri() != 0 && get_vaikeus_aste() == MAHDOTON)
        return true;
    return false;
}

bool Grid::vaaka(int &x, int &y, Pelaajat *tietokone) {
    /*TARKISTAA ONKO pelaaja TEKEMÄSSÄ SUORAA VAAKASUORASSA

    ENSIN TEHDÄÄN VAAKASUORA RIVI ARVIO.
    AINA KUN LUETAAN pelaaja MERKKI, KOROTETAAN counter YHDELLÄ
    JOS LUETAAN tietokone MERKKI VÄHENNETÄÄN counter YHDELLÄ
    KUN RIVI ON LUETTU TARKISTETAAN counter TULOS JA SEN JÄLKEEN counter NOLLATAAN
    */
    for(int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
        int counter {0};
        for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            if(grid.at(i).at(j) == tietokone->get_counter_type()) {
                counter++;
            } else if(grid.at(i).at(j) == tietokone->get_type()) {
                counter--;
            }
        }

        if(counter == -2) { //JOS counter SAA ARVON -2, TIETOKONE ON ITSE TEKEMÄSSÄ SUORAA
            for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
                    return true; //JOS LUETAAN -2 PALAUTETAAN true ARVO VÄLITTÖMÄSTI
                }
            }
        }

        if(counter == MELKEIN_SUORA) {  //JOS counter SAA ARVON 2, PELAAJA ON TEKEMÄSSÄ SUORAA
            for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
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
    /*TARKISTAA ONKO PELAAJA TEKEMÄSSÄ SUORAA PYSTYSUORASSA

    ENSIN TEHDÄÄN PYSTYRIVI ARVIO.
    AINA KUN LUETAAN pelaajan MERKKI, KOROTETAAN counter YHDELLÄ
    JOS LUETAAN tietokoneen MERKKI VÄHENNETÄÄN counter YHDELLÄ
    KUN RIVI ON LUETTU TARKISTETAAN counter TULOS JA SEN JÄLKEEN counter NOLLATAAN
    */
    for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
        int counter {0};
        for(int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
            if(grid.at(i).at(j) == tietokone->get_counter_type()) {
                counter++;
            } else if(grid.at(i).at(j) == tietokone->get_type()) {
                counter--;
            }
        }

        if(counter == -2) { //JOS counter SAA ARVON -2, tietokone ON ITSE TEKEMÄSSÄ SUORAA
            for(int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
                    return true; //JOS LUETAAN -2 PALAUTETAAN true ARVO VÄLITTÖMÄSTI
                }
            }
        }

        if(counter == MELKEIN_SUORA) { //JOS counter SAA ARVON 2, pelaaja ON TEKEMÄSSÄ SUORAA
            for(unsigned int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
                if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID) {
                    x = j;
                    y = i;
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
    //TARKISTETAAN ONKO pelaaja TEKEMÄSSÄ RISTIIN SUORAA
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
    //JOS pelaaja EI OLE TEKEMÄSSÄ SUORAA tietokone LAITTAA MERKKINSÄ REUNOILLE.
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
    //TARKISTAA VAAKASUORAAN, PYSTYSUORAAN JA RISTIIN ONKO JOMPIKUMPI VOITTANUT
    if(x_axis(pelaaja) == SUORA || y_axis(pelaaja) == SUORA || criss_cross(pelaaja) == SUORA || is_grid_full() == true)
        return true;
    else
        return false;
}

int Grid::x_axis(Pelaajat *pelaaja) {
    //TARKISTAA VAAKASUORAAN, ONKO VOITTAJAA LÖYTYNYT
    for(int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
        int counter {0};
        for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            if(grid.at(i).at(j) == pelaaja->get_type())
                counter++;
        }
        if(counter == SUORA) { //JOS VOITTAJA ON LÖYTYNYT SEN OLION VOITTOSTATUS SAA true ARVON
            pelaaja->set_voitto_status(true);
            return SUORA;
        }
    }
    return EI_SUORAA;
}

int Grid::y_axis(Pelaajat *pelaaja) {
    //TARKISTAA PYSTYSUORAAN, ONKO VOITTAJAA LÖYTYNYT
    for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
        int counter {0};
        for(int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
            if(grid.at(i).at(j) == pelaaja->get_type())
                counter++;
        }
        if(counter == SUORA) {
            pelaaja->set_voitto_status(true); //JOS VOITTAJA ON LÖYTYNYT SEN OLION VOITTOSTATUS SAA true ARVON
            return SUORA;
        }
    }
    return EI_SUORAA;
}

int Grid::criss_cross(Pelaajat *pelaaja) {
    //TARKISTAA RISTIIN, ONKO VOITTAJAA LÖYTYNT
    //JOS VOITTAJA ON LÖYTYNYT SEN OLION VOITTOSTATUS SAA true ARVON
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
    //TARKISTAA ONKO MATRIISISSA TYHJIÄ PAIKKOJA JÄLJELLÄ
    for(int i {MIN_GRID_SIZE}; i < MAX_GRID_SIZE; i++) {
        for(int j {MIN_GRID_SIZE}; j < MAX_GRID_SIZE; j++) {
            if(grid.at(i).at(j) == EMPTY_SPOT_ON_THE_GRID)
                return false;
        }
    }
    return true;
}