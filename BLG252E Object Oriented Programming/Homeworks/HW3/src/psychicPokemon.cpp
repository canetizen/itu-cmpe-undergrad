/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#include "psychicPokemon.h"

PsychicPokemon::PsychicPokemon(const std::string m_name, const int m_hp, const int m_damage) 
    :Pokemon{m_name, m_hp, m_damage, 30, 5} //Base class constructor is used.
{}

void PsychicPokemon::attack(ElectricPokemon* const elec_current) {
    if (this->get_is_own_terrain() == true) {
        Pokemon::attack(elec_current, get_damage() * 2); //Psychic pokemon causes damage because of the powerUp, and the terrain is psychic.
    } else {
        Pokemon::attack(elec_current, get_damage()); //Regular attack.
    }
    if (elec_current->get_hp() <= 0) { //check whether opponent is fainted.
        elec_current->set_hp(0);
        elec_current->set_is_fainted(true);
    }
}