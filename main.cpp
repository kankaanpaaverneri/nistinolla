#include "Pelaajat.h"
#include "Pelaaja.h"
#include "Tietokone.h"
#include "Util.h"
#include "Grid.h"

#include <iostream>
#include <cstring>
#include <ctime>

int main() {
    srand((int)time(NULL));
    Pelaajat *pelaaja = new Pelaaja();
    Pelaajat *tietokone = new Tietokone();

    Grid gr;
    valikko(pelaaja, tietokone, gr);
    gr.display_grid();

    while(gr.check_winning_condition(tietokone) != true) {
        //PELAAJA TEKEE SIIRTONSA
        siirto(&gr, pelaaja);

        //TARKISTETAAN VOITTAJA
        if(gr.check_winning_condition(pelaaja) == true)
            break;

        //TIETOKONE TEKEE SIIRTONSA
        siirto(&gr, tietokone);
        gr.display_grid();
    }
    gr.display_grid();

    if(tietokone->get_voitto_status() == true && pelaaja->get_voitto_status() == true) {
        std::cout << "TASAPELI" << std::endl;
    } else if(tietokone->get_voitto_status() == true) {
        std::cout << "VOITTAJA OLI: " << tietokone->get_type() << std::endl;
        std::cout << "Tietokone" << std::endl;
    } else if(pelaaja->get_voitto_status() == true) {
        std::cout << "VOITTAJA OLI: " << pelaaja->get_type() << std::endl;
        std::cout << "Ihminen" << std::endl;
    } else if(tietokone->get_voitto_status() == false && pelaaja->get_voitto_status() == false) {
        std::cout << "KUMPIKAAN EI VOITTANUT" << std::endl;
    }

    delete pelaaja;
    delete tietokone;
    return 0;
}