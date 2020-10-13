#ifndef _TIETOKONE_H_
#define _TIETOKONE_H_
#include "Pelaajat.h"
#include "Util.h"
#include "Grid.h"
#include <cstdlib>

class Tietokone : public Pelaajat {
    private:
        static constexpr const char tunniste = TIETOKONE_TUNNISTE;
    protected:
        char tyyppi, vasta_tyyppi;
        bool voitto_status;
        int x, y;
    public:
        Tietokone();
        virtual ~Tietokone() = default;
        virtual void alusta_pelaaja(const char tyyppi, const char vasta_tyyppi) override;
        virtual const char get_type() override {return tyyppi;}
        virtual const char get_counter_type() override {return vasta_tyyppi;}
        virtual const char get_tunniste() override {return tunniste;}
        virtual void set_voitto_status(const bool status) override {voitto_status = status;}
        virtual const bool get_voitto_status() override {return voitto_status;}
        virtual void set_computer_coordinates(const int x, const int y) override {this->x = x; this->y = y;}
        virtual const int get_computer_x_coordinate() {return x;}
        virtual const int get_computer_y_coordinate() {return y;}
};
#endif