#ifndef _PELAAJA_H_
#define _PELAAJA_H_
#include "Pelaajat.h"
#include "Util.h"
#include "Grid.h"
class Pelaaja : public Pelaajat { //CONCRETE CLASS
    private:
        static constexpr const char tunniste = PELAAJA_TUNNISTE;
    protected:
        char tyyppi, vasta_tyyppi;
        bool voitto_status;
    public:
        //CONSTRUCTORS JA DESTURCTOR
        Pelaaja();
        virtual ~Pelaaja() = default;

        //VIRTUALISET FUNKTIOT
        virtual void alusta_pelaaja(const char tyyppi, const char vasta_tyyppi) override;
        virtual const char get_type() override {return tyyppi;}
        virtual const char get_counter_type() override {return vasta_tyyppi;}
        virtual const char get_tunniste() override {return tunniste;}
        virtual void set_voitto_status(const bool status) override {voitto_status = status;}
        virtual const bool get_voitto_status() override {return voitto_status;}
        virtual void set_computer_coordinates(const int x, const int y);
        virtual const int get_computer_x_coordinate();
        virtual const int get_computer_y_coordinate();
};
#endif