/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#pragma once

#include "electricPokemon.h"
#include "psychicPokemon.h"

class Arena {
    public:
        Arena(); //Default constructor
        void addPokemon(const char, const std::string, const int, const int);
        void simulateBattle();
    private:
        void spawnTerrain();
        void restartTerrain();
        void printRoundStats(const int, const int);
        void printMatchResults();
        std::string terrain_type;
        int terrain_counter; //To measure terrain time.
        ElectricPokemon* elec_current; //Fighter pokemons will be represented by its pointers.
        PsychicPokemon* psyc_current;
};
