#include "Util.h"

void virhe_viesti() {
    std::cout << "VIRHEELLINEN SYÖTE..." << std::endl;
}

void valikko(Pelaajat *pelaaja, Pelaajat *tietokone, Grid &ref) {
    std::cout << "=== NISTINOLLA ===" << std::endl << std::endl;

    //VALITAAN VAIKEUSTASO
    valitse_vaikeustaso(ref);

    //ALUSTETAAN PELAAJIEN TYYPIT
    valitse_pelaaja_tyyppi(pelaaja, tietokone);
}

void valitse_vaikeustaso(Grid &ref) {
    std::cout << "VAIKEUSASTEET: " << std::endl << std::endl;
    std::cout << "1) Tunari" << std::endl;
    std::cout << "2) Keskitaso" << std::endl;
    std::cout << "3) Mahdoton" << std::endl;
    while(ref.get_vaikeus_aste() == 0) {
        char *buffer = new char[BUFFER_LIMIT+1];
        fgets(buffer, BUFFER_LIMIT, stdin);
        int vaikeus_aste {0};
        if(sscanf(buffer, "%d", &vaikeus_aste) != 1) {
            virhe_viesti();
            delete [] buffer;
            continue;
        }
        if(vaikeus_aste < TUNARI || vaikeus_aste > MAHDOTON) {
            std::cout << "Arvo ei 1 ja 3 väliltä!" << std::endl << std::endl;
            continue;
        }
        ref.set_vaikeus_aste(vaikeus_aste);
    }
}

void valitse_pelaaja_tyyppi(Pelaajat *pelaaja, Pelaajat *tietokone) {
    std::cout << "X vai O?" << std::endl;

    while(1) {
        char *buffer = new char[BUFFER_LIMIT+1];
        fgets(buffer, BUFFER_LIMIT, stdin);
        if(*buffer == UPPER_X || *buffer == LOWER_X) {
            pelaaja->alusta_pelaaja(UPPER_X, UPPER_O);
            tietokone->alusta_pelaaja(UPPER_O, UPPER_X);
        } else if(*buffer == UPPER_O || *buffer == LOWER_O) {
            pelaaja->alusta_pelaaja(UPPER_O, UPPER_X);
            tietokone->alusta_pelaaja(UPPER_X, UPPER_O);
        } else {
            virhe_viesti();
            delete [] buffer;
            continue;
        }
        delete [] buffer;
        break;
    }
}

void siirto(Grid *gr, Pelaajat *pelaaja) {
    while(1) {
        int x {0}, y {0};
        if(pelaaja->get_tunniste() == PELAAJA_TUNNISTE) {
            std::cout << "X arvo: ";
            x = input_cordinate();
            std::cout << "Y arvo: ";
            y = input_cordinate();
        } else if(pelaaja->get_tunniste() == TIETOKONE_TUNNISTE) {
            if(gr->computer_strategy(x, y, pelaaja) == false) {
                if(gr->get_kierros_laskuri() == 0 && gr->get_vaikeus_aste() == MAHDOTON) {
                    x = 2;
                    y = 2;
                } else {
                    x = rand() % MAX_GRID_SIZE+MIN_GRID_SIZE;
                    y = rand() % MAX_GRID_SIZE+MIN_GRID_SIZE;
                }
            }
        }

        //PÄIVITETÄÄN GRID
        if(gr->update_grid(x, y, pelaaja) == true)
            break;
        else {
            if(pelaaja->get_tunniste() == PELAAJA_TUNNISTE) {
                virhe_viesti();
            }
        }
        gr->korota_kierros_laskuria();
    }
}

int input_cordinate() {
    int kordinaatti_arvo {0};
    while(1) {
        char *buffer = new char[BUFFER_LIMIT+1];
        fgets(buffer, BUFFER_LIMIT, stdin);
        if(sscanf(buffer, "%d", &kordinaatti_arvo) != 1) {
            virhe_viesti();
            delete [] buffer;
            continue;
        }
        if(kordinaatti_arvo >= MAX_GRID_SIZE || kordinaatti_arvo <= MIN_GRID_SIZE) {
            virhe_viesti();
            std::cout << "Syötä arvo uudelleen: " << std::endl;
            delete [] buffer;
            continue;
        }
        delete [] buffer;
        break;
    }
    return kordinaatti_arvo;
}