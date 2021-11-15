#include <iostream>
#include <cstring>

#include "player.h"
#include "weapon.h"


using namespace std;

Player::Player(const char * name, const Weapon& weapon){
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    this->weapon=weapon;
    level=1;
    strength=1;
    life=1;
    place=0;
}

Player::Player(){
    this->name = NULL;
    this->weapon=Weapon();
    level=1;
    strength=1;
    life=1;
    place=0;
}

Player::~Player(){
    delete[] name;
}

void Player::nextLevel(){
    level++;
}

bool Player::isPlayer(const char * playerName)const{
    if(strcmp(name, playerName)==0){
        return true;
    }
    return false;
}

void Player::makeStep(){
    place++;
}

void Player::addLife(){
    life++;
}

void Player::addStrength(int strengthToAdd){
    strength+=strengthToAdd;
}

bool Player::isAlive()const{
    if(this->level>0 && this->strength>0 && this->life>0){
        return true;
    }
    return false;
}

bool Player::weaponIsWeak(int weaponMinStrength)const{
    if(this->weapon.getValue()<weaponMinStrength){
        return true;
    }
    return false;
}

bool Player::fight(Player& player2){
    if(this->place==player2.place) {
        Player* attacker;
        Player* defender;
        if (this->weapon > player2.weapon) {
            attacker = this;
            defender = &player2;
        } else {
            if(this->weapon == player2.weapon){
                return false;
            }
            attacker = &player2;
            defender = this;
        }
        if (attacker->weapon.Weapon::getTarget() == 0) {
            defender->level -= attacker->weapon.getHitStrength();
            if(defender->level<0){
                defender->level=0;
            }
        }
        if (attacker->weapon.getTarget() == 1) {
            defender->strength -= attacker->weapon.getHitStrength();
            if(defender->strength<0){
                defender->strength=0;
            }
        }
        if (attacker->weapon.getTarget() == 2) {
            defender->life -= attacker->weapon.getHitStrength();
            if(defender->life<0){
                defender->life=0;
            }
        }
        return true;
    }else{
        return false;
    }
}

ostream& operator<<(ostream& os, const Player& player1){
    os<<"{player name: "<<player1.name<<", weapon: "<<player1.weapon.name;
    return os;
}

bool operator>(const Player& player1, const Player& player2){
    if(strcmp(player1.name, player2.name)>0){
        return true;
    }
    return false;
}

bool operator<(const Player& player1, const Player& player2){
    if(strcmp(player1.name, player2.name)<0){
        return true;
    }
    return false;
}
