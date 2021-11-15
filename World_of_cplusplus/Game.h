//
// Created by HP on 09.06.2018.
//

#ifndef EX4_GAME_H
#define EX4_GAME_H
#include <iostream>
#include "weapon.h"
#include "player.h"

using namespace std;

enum GameStatus {
    INVALID_PARAM,
    NAME_ALREADY_EXISTS,
    GAME_FULL,
    NAME_DOES_NOT_EXISTS,
    FIGHT_FAILED,
    SUCCESS
};

struct Game{
    int maxPlayers;
    Player** playersArray;

    Game(int maxPlayer);
    ~Game();
    friend ostream& operator<<(ostream& os, const Game& game);
    GameStatus addPlayer(const char * playerName, const char * weaponName, Target target, int hit_strength);
    GameStatus nextLevel(const char * playerName);
    GameStatus makeStep(const char * playerName);
    GameStatus addLife(const char * playerName);
    GameStatus addStrength (const char * playerName, int strengthToAdd);
    bool removeAllPlayersWithWeakWeapon(int weaponStrength);
    GameStatus fight(const char * playerName1, const char * playerName2);

};



#endif //EX4_GAME_H
