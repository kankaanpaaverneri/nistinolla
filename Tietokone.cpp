#include "Tietokone.h"

Tietokone::Tietokone()
    : tyyppi{'?'}, voitto_status{false} {
}

void Tietokone::alusta_pelaaja(const char tyyppi, const char vasta_tyyppi) {
    this->tyyppi = tyyppi;
    this->vasta_tyyppi = vasta_tyyppi;
}