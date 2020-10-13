#ifndef _GRID_H_
#define _GRID_H_
#include "Pelaajat.h"
#include <iostream>
#include <vector>

#define MAX_GRID_SIZE 4
#define MIN_GRID_SIZE 0
#define EMPTY_SPOT_ON_THE_GRID '#'
#define SUORA 3
#define MELKEIN_SUORA 2
#define EI_SUORAA 0

class Grid {
    private:
        std::vector <std::vector<char>> grid;
        static int kierros_laskuri;
        int vaikeus_aste;
    public:
        Grid();
        ~Grid();
        static int get_kierros_laskuri() {return kierros_laskuri;}
        void korota_kierros_laskuria() {kierros_laskuri++;}
        void display_grid() const;
        bool update_grid(const int x, const int y, Pelaajat *pelaaja);

        void set_vaikeus_aste(const int vaikeus_aste) {this->vaikeus_aste = vaikeus_aste;}
        const int get_vaikeus_aste() const {return vaikeus_aste;}

        //TIETOKONEEN TEKOÄLY
        bool computer_strategy(int &x, int &y, Pelaajat *tietokone);
        bool vaaka(int &x, int &y, Pelaajat *tietokone);
        bool pysty(int &x, int &y, Pelaajat *tietokone);
        bool risti(int &x, int &y, Pelaajat *tietokone);
        bool ei_uhkaa(int &x, int &y, Pelaajat *tietokone);

        //VOITAMISEN TARKISTUS FUNKTIOT
        bool check_winning_condition(Pelaajat *pelaaja);
        int x_axis(Pelaajat *pelaaja);
        int y_axis(Pelaajat *pelaaja);
        int criss_cross(Pelaajat *pelaaja);
        bool is_grid_full();
};
#endif