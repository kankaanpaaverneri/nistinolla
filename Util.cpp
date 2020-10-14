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
        delete [] buffer;
    }
}

void valitse_pelaaja_tyyppi(Pelaajat *pelaaja, Pelaajat *tietokone) {
    std::cout << "X vai 0?" << std::endl;

    //ALUSTETAAN MOLEMPIEN OLIOIDEN TYYPIT
    //ELI OVATKO X VAI O JA MYÖS MIKÄ HEIDÄN VASTUSTAJANSA ON
    while(true) {
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
    //TARKISTETAAN ONKO VÄLITETTY PELAAJA TIETOKONE VAI PELAAJA JA TOIMITAAN SEN MUKAISESTI
    while(true) {
        int x {0}, y {0};
        if(pelaaja->get_tunniste() == PELAAJA_TUNNISTE) { //TÄSSÄ SUORITETAAN PELAAJAN X, Y KOORDINAATTIEN SYÖTTÖ
            std::cout << std::endl;
            std::cout << "X arvo: ";
            x = input_cordinate();
            std::cout << "Y arvo: ";
            y = input_cordinate();
        } else if(pelaaja->get_tunniste() == TIETOKONE_TUNNISTE) { //TÄSSÄ SUORITETAAN TIETOKONEEN X, Y KORDINAATTIEN MÄÄRITTELY
            if(gr->computer_strategy(x, y, pelaaja) == false) { //TIETOKONE ARVIOI ONKO PELAAJA TEKEMÄSSÄ SUORAA JA MÄÄRITTELEE X, Y KOORDINAATIT SEN MUKAISESTI
                if(gr->get_kierros_laskuri() == 0 && gr->get_vaikeus_aste() == MAHDOTON) { //JOS ENSIMMÄINEN KIERROS, X, Y OVAT 2, 2
                    x = 2;
                    y = 2;
                } else { //MUUSSA TAPAUKSESSA TIETOKONE ARVIOI SATUNNAISESTI X, Y KOORDINAATIT
                    x = rand() % MAX_GRID_SIZE+MIN_GRID_SIZE;
                    y = rand() % MAX_GRID_SIZE+MIN_GRID_SIZE;
                }
            }
        }

        //PÄIVITETÄÄN RUUDUKKO X, Y KOORDINAATTIEN AVULLA
        if(gr->update_grid(x, y, pelaaja) == true)
            break;
        else {
            if(pelaaja->get_tunniste() == PELAAJA_TUNNISTE) {
                //JOS KOORDINAATIT EIVÄT TÄSMÄÄ JA SIIRRON TEKI PELAAJA, TULOSTETAAN VIRHEVIESTI
                virhe_viesti();
            }
        }
        gr->korota_kierros_laskuria();
    }
}

int input_cordinate() {
    //LUKEE KÄYTTÄJÄN SYÖTTEEN JA TARKISTAA ARVON
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

void tulokset(Pelaajat* pelaaja, Pelaajat *tietokone) {
    //PELIN PÄÄTYTTYÄ TULOSTETAAN TULOKSET
    std::cout << std::endl;
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
}