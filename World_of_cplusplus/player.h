//
// Created by HP on 08.06.2018.
//

#ifndef EX4_PLAYER_H
#define EX4_PLAYER_H
#include <iostream>
#include "weapon.h"

using namespace std;

struct Player{
    char* name;
    int level;
    int life;
    int strength;
    Weapon weapon;
    int place;

    friend ostream& operator<<(ostream& os, const Player& player1);
    friend bool operator>(const Player& player1, const Player& player2);
    friend bool operator<(const Player& player1, const Player& player2);
    Player();
    Player(const char * name, const Weapon& weapon);
    ~Player();
    void nextLevel();
    bool isPlayer(const char * playerName)const;
    void makeStep();
    void addLife();
    void addStrength(int strengthToAdd);
    bool isAlive()const;
    bool weaponIsWeak(int weaponMinStrength)const;
    bool fight(Player& player);

};

#endif //EX4_PLAYER_H
