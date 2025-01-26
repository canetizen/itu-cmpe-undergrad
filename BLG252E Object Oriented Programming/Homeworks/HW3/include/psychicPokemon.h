/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#pragma once

#include "pokemon.h"
#include "electricPokemon.h"

class ElectricPokemon;

class PsychicPokemon : public Pokemon {
    public:
        PsychicPokemon(const std::string, const int, const int); //derived class constructor.
        void attack(ElectricPokemon* const); //pointer is constant, data may change.
};