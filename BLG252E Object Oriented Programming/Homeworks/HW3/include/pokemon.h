/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#pragma once

#include <string>

class Pokemon {
    public:
        Pokemon(const std::string, const int, const int, const int, const int); //base class constructor
        void set_recharge_counter(const int); //getters and setters
        void set_hp(const int); 
        void set_is_fainted(const bool);
        void set_is_powerup_state(const bool);
        void set_is_own_terrain(const bool);
        std::string get_name();
        int get_recharge_counter();
        int get_hp();
        int get_damage();
        int get_powerup_chance();
        int get_recharge();
        bool get_is_fainted();
        bool get_is_powerup_state();
        bool get_is_own_terrain();
    protected:
        void attack(Pokemon* const, const int); //pointer is constant, data may change.
    private:
        const std::string name;
        int hp;
        const int damage;
        const int powerup_chance;
        const int recharge;
        bool is_fainted;
        bool is_powerup_state;
        bool is_own_terrain;
        int recharge_counter;
};
