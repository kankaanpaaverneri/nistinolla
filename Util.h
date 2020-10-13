#ifndef _UTIL_H_
#define _UTIL_H_
#include "Pelaajat.h"
#include "Grid.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

#define BUFFER_LIMIT 128
#define UPPER_X 'X'
#define UPPER_O 'O'
#define LOWER_X 'x'
#define LOWER_O 'o'
#define PELAAJA_TUNNISTE 'P'
#define TIETOKONE_TUNNISTE 'T'
#define TUNARI 1
#define KESKITASO 2
#define MAHDOTON 3

void valikko(Pelaajat *pelaaja, Pelaajat *tietokone, Grid &ref);
void valitse_vaikeustaso(Grid &ref);
void valitse_pelaaja_tyyppi(Pelaajat *pelaaja, Pelaajat *tietokone);
void virhe_viesti();
void siirto(Grid *gr, Pelaajat *pelaaja);
int input_cordinate();

#endif