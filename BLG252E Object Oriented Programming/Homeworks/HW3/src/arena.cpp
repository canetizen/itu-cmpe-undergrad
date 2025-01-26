/* @Author
* Student Name: Mustafa Can Caliskan
* Student ID : 150200097
*/
#include "arena.h"
#include <iostream>

Arena::Arena() {
    terrain_type = "uninitialized"; //The terrain type will be initialized as "uninitialized" at the beginning.
    terrain_counter = 0;
    elec_current = NULL; //Pointers will be initialized as NULL.
    psyc_current = NULL;
}

void Arena::addPokemon(const char type, const std::string name, const int hp, const int damage) {
    if (type == 'e') {
        std::cout << std::endl;
        elec_current = new ElectricPokemon(name, hp, damage); //Electric pokemon object will be created and pointed.
        std::cout << "Electric Pokemon "<< this->elec_current->get_name() << " has entered the arena." << std::endl;
        std::cout << "Class: Electric" << std::endl;
        std::cout << "\tName: " << this->elec_current->get_name() << std::endl;
        std::cout << "\tHP: " << this->elec_current->get_hp() << std::endl;
        std::cout << "\tDamage: " << this->elec_current->get_damage() << std::endl;
        std::cout << std::endl;
    } else if (type == 'p') {
        psyc_current = new PsychicPokemon(name, hp, damage); //Psychic pokemon object will be created and pointed.
        std::cout << "Psychic Pokemon "<< this->psyc_current->get_name() << " has entered the arena." << std::endl;
        std::cout << "Class: Psychic" << std::endl;
        std::cout << "\tName: " << this->psyc_current->get_name() << std::endl;
        std::cout << "\tHP: " << this->psyc_current->get_hp() << std::endl;
        std::cout << "\tDamage: " << this->psyc_current->get_damage() << std::endl;
        std::cout << std::endl;
    }
}

void Arena::simulateBattle() {
    Pokemon* first = NULL; //To keep track of the pokemon who will attack first.
    
    int round = 1;
    while (elec_current->get_is_fainted() == false && psyc_current->get_is_fainted() == false) { //The condition of the end of the battle is either of pokemons is fainted.
        elec_current->set_is_powerup_state(false); //to resetting at the beginning.
        psyc_current->set_is_powerup_state(false);
        if (elec_current->get_is_confused() == true) {
            if (elec_current->get_confused_timer() == 0)
                elec_current->set_is_confused(false);
        }

        if (terrain_counter == 0) //Spawn or respawn terrains according to the terrain counter.
            spawnTerrain();

        if (terrain_type == "electric" && elec_current->get_is_confused() == true) { //If the terrain is spawned as electric, and the electric pokemon is confused, the confusion effect will be eliminated.
            elec_current->set_is_confused(false);
            elec_current->set_confused_timer(0);
        }

        int random_first = rand() % 2; //To determine who will attack first.
        if (random_first == 0)
            first = elec_current;
        else
            first = psyc_current;

        int elec_powerup = rand() % 100; //To determine powerUp state of electric pokemon.
        if (0 <= elec_powerup && elec_powerup < elec_current->get_powerup_chance() && elec_current->get_recharge_counter() == 0) {
            elec_current->set_is_powerup_state(true);
            elec_current->set_recharge_counter(elec_current->get_recharge() + 1); //The time of recharge does not contain powerUp round.
        }

        int psyc_powerup = rand() % 100; //To determine powerUp state of psychic pokemon.
        if (0 <= psyc_powerup && psyc_powerup < psyc_current->get_powerup_chance() && psyc_current->get_recharge_counter() == 0) {
            psyc_current->set_is_powerup_state(true);
            psyc_current->set_recharge_counter(psyc_current->get_recharge() + 1);
        }

        if (first == elec_current) { //To manage attacks.
            elec_current->attack(psyc_current);
            if (psyc_current->get_is_fainted() == false) {
                psyc_current->attack(elec_current);
                if (psyc_current->get_is_powerup_state()) {
                    if (terrain_type == "none" || psyc_current->get_is_own_terrain() == true) {
                        elec_current->set_is_confused(true);
                        if (random_first == 0)
                            elec_current->set_confused_timer(4); //If the electric pokemon is confused AFTER its attack, the timer will start to count from 4.
                        else
                            elec_current->set_confused_timer(3);
                    }
                }
            }   
        } else {
            psyc_current->attack(elec_current);
            if (psyc_current->get_is_powerup_state()) {
                if (terrain_type == "none" || psyc_current->get_is_own_terrain() == true) {
                    elec_current->set_is_confused(true);
                    if (random_first == 0)
                        elec_current->set_confused_timer(4); //If the electric pokemon is confused AFTER its attack, the timer will start to count from 4.
                    else
                        elec_current->set_confused_timer(3);
                }
            }
            if (elec_current->get_is_fainted() == false)
                elec_current->attack(psyc_current);
        }

        printRoundStats(round, random_first);
        
        round++;
        terrain_counter--;
        if (elec_current->get_recharge_counter() != 0) //To adjust timers and counters for the next round.
            elec_current->set_recharge_counter(elec_current->get_recharge_counter() - 1);

        if (psyc_current->get_recharge_counter() != 0)
            psyc_current->set_recharge_counter(psyc_current->get_recharge_counter() - 1);
        
        if (elec_current->get_is_confused() == true) {
            if (elec_current->get_confused_timer() != 0)
                elec_current->set_confused_timer(elec_current->get_confused_timer() - 1);
        }
    }

    printMatchResults();
    restartTerrain();
}

void Arena::spawnTerrain() { //To determine terrain type randomly.
    int random_terrain = rand() % 10;
    if (random_terrain >= 0 && random_terrain < 2) {
        elec_current->set_is_own_terrain(false);
        psyc_current->set_is_own_terrain(true);
        this->terrain_type = "psychic";
        terrain_counter = 5;
    } else if (random_terrain > 1 && random_terrain < 4) {
        psyc_current->set_is_own_terrain(false);
        elec_current->set_is_own_terrain(true);
        this->terrain_type = "electric";
        terrain_counter = 5;
    } else {
        psyc_current->set_is_own_terrain(false);
        elec_current->set_is_own_terrain(false);
        this->terrain_type = "none";
        terrain_counter = 1;
    }
}

void Arena::restartTerrain() { //To reset terrain for the new battle.
    delete elec_current; //The program does not need to keep them anymore.
    delete psyc_current;
    elec_current = NULL;
    psyc_current = NULL;
    terrain_type = "uninitialized";
    terrain_counter = 0;
}

void Arena::printRoundStats(const int round, const int heads) { //To print round stats.
    std::cout << std::endl;
    std::cout << "Round: " << round << std::endl;
    std::cout << "Current Terrain: " << this->terrain_type << std::endl;
    if(heads == 0)
        std::cout << this->elec_current->get_name() << " goes first." << std::endl;
    else
        std::cout << this->psyc_current->get_name() << " goes first." << std::endl;
    if (elec_current->get_is_powerup_state() == true)
        std::cout << this->elec_current->get_name() << " has initiated a power up." << std::endl;
    if (psyc_current->get_is_powerup_state() == true)
        std::cout << this->psyc_current->get_name() << " has initiated a power up." << std::endl;
    std::cout << this->elec_current->get_name() << " HP: " << this->elec_current->get_hp() << std::endl; 
    std::cout << this->psyc_current->get_name() << " HP: " << this->psyc_current->get_hp() << std::endl;
    if (this->elec_current->get_hp() > this->psyc_current->get_hp())
            std::cout << this->elec_current->get_name() << " is in the lead!" << std::endl;
    else if (this->elec_current->get_hp() < this->psyc_current->get_hp())
        std::cout << this->psyc_current->get_name() << " is in the lead!" << std::endl;
    else
        std::cout << "Pokemons have the same HP!" << std::endl; //The same hp condition.
    std::cout << std::endl;
}

void Arena::printMatchResults() {//At the end of the match.
    std::cout << std::endl;
    std::cout << "Match Results:" << std::endl;
    if (this->elec_current->get_is_fainted() == true) 
        std::cout << this->psyc_current->get_name() << " has won the match!" << std::endl;
    else if (this->psyc_current->get_is_fainted() == true)
        std::cout << this->elec_current->get_name() << " has won the match!" << std::endl;
    std::cout << std::endl;
}