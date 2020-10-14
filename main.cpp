#include <iostream>
#include <cstring>
#include <ctime>

#include "Pelaajat.h"
#include "Pelaaja.h"
#include "Tietokone.h"
#include "Util.h"
#include "Grid.h"

int main() {
    srand((int)time(NULL));

    Pelaajat *pelaaja = new Pelaaja();
    Pelaajat *tietokone = new Tietokone();

    Grid gr;
    valikko(pelaaja, tietokone, gr); //Util.h
    gr.display_grid();

    while(gr.check_winning_condition(tietokone) != true) {
        //pelaaja TEKEE SIIRTONSA
        siirto(&gr, pelaaja); //Util.h

        //TARKISTETAAN VOITTAJA
        if(gr.check_winning_condition(pelaaja) == true)
            break;

        //tietokone TEKEE SIIRTONSA
        siirto(&gr, tietokone); //Util.h
        gr.display_grid();
    }
    gr.display_grid();
    tulokset(pelaaja, tietokone); //Util.h

    delete pelaaja;
    delete tietokone;
    return 0;
}