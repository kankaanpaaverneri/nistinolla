#ifndef _PELAAJAT_H_
#define _PELAAJAT_H_

class Pelaajat {
    public:
        virtual ~Pelaajat() = default;
        virtual void alusta_pelaaja(const char tyyppi, const char vasta_tyyppi) = 0;
        virtual const char get_type() = 0;
        virtual const char get_counter_type() = 0;
        virtual const char get_tunniste() = 0;
        virtual void set_voitto_status(const bool status) = 0;
        virtual const bool get_voitto_status() = 0;
        virtual void set_computer_coordinates(const int x, const int y) = 0;
        virtual const int get_computer_x_coordinate() = 0;
        virtual const int get_computer_y_coordinate() = 0;
};
#endif