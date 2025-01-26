/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#pragma once

#include "pokemon.h"
#include "psychicPokemon.h"
class PsychicPokemon;

class ElectricPokemon : public Pokemon {
    public:
        ElectricPokemon(const std::string, const int, const int); //derived class constructor
        void attack(PsychicPokemon* const); //pointer is constant, data may change.
        void set_confused_timer(const int);
        void set_is_confused(const bool);
        bool get_is_confused();
        int get_confused_timer();
    private:
        bool is_confused; //to determine whether confused or not.
        int confused_timer; //to measure confused time.
};