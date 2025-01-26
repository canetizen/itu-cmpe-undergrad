/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#include "electricPokemon.h"

ElectricPokemon::ElectricPokemon(const std::string m_name, const int m_hp, const int m_damage) 
    :Pokemon{m_name, m_hp, m_damage, 20, 3} //Base class constructor is used.
{
    is_confused = false;
    confused_timer = 0;
}

void ElectricPokemon::attack(PsychicPokemon* const psyc_current) {
    if (this->get_is_powerup_state() == false && this->is_confused == false) {
        Pokemon::attack(psyc_current, get_damage()); //Electric pokemon is attacking without powerUp. (Regular attack)
    } else if (this->get_is_powerup_state() == true && this->is_confused == false) {
        Pokemon::attack(psyc_current, get_damage() * 3); //Electric pokemon is attacking with powerUp.
    }
    if (psyc_current->get_hp() <= 0) { //check whether opponent is fainted.
        psyc_current->set_hp(0);
        psyc_current->set_is_fainted(true);
    }
}

void ElectricPokemon::set_confused_timer(const int timer) {
    confused_timer = timer;
}

void ElectricPokemon::set_is_confused(const bool cond) {
    is_confused = cond;
}

bool ElectricPokemon::get_is_confused() {
    return is_confused;
}

int ElectricPokemon::get_confused_timer() {
    return confused_timer;
}