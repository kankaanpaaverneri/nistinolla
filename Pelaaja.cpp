#include "Pelaaja.h"

Pelaaja::Pelaaja()
    : tyyppi{'?'}, voitto_status{false} {
}

void Pelaaja::alusta_pelaaja(const char tyyppi, const char vasta_tyyppi) {
    this->tyyppi = tyyppi;
    this->vasta_tyyppi = vasta_tyyppi;
}

void Pelaaja::set_computer_coordinates(const int x, const int y) {
    //EI TEHDÄ TÄÄLLÄ MITÄÄN
    return;
}

const int Pelaaja::get_computer_x_coordinate() {
    //EI TEHDÄ TÄÄLLÄ MITÄÄN
    return 0;
}

const int Pelaaja::get_computer_y_coordinate() {
    //EI TEHDÄ TÄÄLLÄ MITÄÄN
    return 0;
}
