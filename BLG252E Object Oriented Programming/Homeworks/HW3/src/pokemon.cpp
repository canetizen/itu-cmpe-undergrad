/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#include "pokemon.h"

Pokemon::Pokemon(const std::string m_name, const int m_hp, const int m_damage,
                const int m_powerup_chance, const int m_recharge)
    :name{m_name}, damage{m_damage}, powerup_chance{m_powerup_chance}, recharge{m_recharge} //member initializer list to initialize cost members.
{
    hp = m_hp;
    is_fainted = false;
    is_powerup_state = false;
    is_own_terrain = false;
    recharge_counter = 0;
}

void Pokemon::set_recharge_counter(const int m_counter) { //getters and setters
    recharge_counter = m_counter;
}

void Pokemon::set_hp(const int m_hp) {
    hp = m_hp;
}

void Pokemon::set_is_fainted(const bool cond) {
    is_fainted = cond;
}

void Pokemon::set_is_powerup_state(const bool cond) {
    is_powerup_state = cond;
}

void Pokemon::set_is_own_terrain(const bool cond) {
    is_own_terrain = cond;
}

int Pokemon::get_recharge_counter() {
    return recharge_counter;
}

std::string Pokemon::get_name() {
    return name;
}

int Pokemon::get_hp() {
    return hp;
}

int Pokemon::get_damage() {
    return damage;
}

int Pokemon::get_powerup_chance() {
    return powerup_chance;
}

int Pokemon::get_recharge() {
    return recharge;
}

bool Pokemon::get_is_fainted() {
    return is_fainted;
}

bool Pokemon::get_is_powerup_state() {
    return is_powerup_state;
}

bool Pokemon::get_is_own_terrain() {
    return is_own_terrain;
}

void Pokemon::attack(Pokemon* const attacked, const int damage) {
    attacked->set_hp(attacked->get_hp() - damage);
}