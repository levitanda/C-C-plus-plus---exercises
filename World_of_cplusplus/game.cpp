#include <iostream>
#include <cstring>
#include <cstddef>
#include "Game.h"
#include "player.h"

using namespace std;

Game::Game(int maxPlayer){
    this->playersArray = new Player*[maxPlayer];
    for(int i=0; i<maxPlayer; i++) {
        playersArray[i] = NULL;
    }
    this->maxPlayers=maxPlayer;
}

Game::~Game(){
    for(int i=0; i<maxPlayers; i++) {
       delete playersArray[i];
    }
    delete[] playersArray;
}

GameStatus Game::addPlayer(const char * playerName, const char * weaponName, Target target, int hit_strength){
    for(int i=0; i<(this->maxPlayers); i++) {
        if (playersArray[i] == NULL) {
            continue;
        }
        if (playersArray[i]->isPlayer(playerName)) {
            return NAME_ALREADY_EXISTS;
        }
    }
    for(int i=0; i<maxPlayers; i++) {
        if(playersArray[i]==NULL){
            Weapon *tmp_weapon=new Weapon(weaponName, target, hit_strength);
            Player *tmp_player=new Player(playerName, *tmp_weapon);
            playersArray[i]=tmp_player;
            return SUCCESS;
        }
    }
    return GAME_FULL;
}

GameStatus Game::nextLevel(const char * playerName){
    for(int i=0; i<maxPlayers; i++){
        if(playersArray[i]==NULL){
            continue;
        }
        if(playersArray[i]->isPlayer(playerName)){
            playersArray[i]->nextLevel();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXISTS;
}

GameStatus Game::makeStep(const char * playerName){
    for(int i=0; i<maxPlayers; i++){
        if(playersArray[i]==NULL){
            continue;
        }
        if(playersArray[i]->isPlayer(playerName)){
            playersArray[i]->makeStep();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXISTS;
}

GameStatus Game::addLife(const char * playerName){
    for(int i=0; i<maxPlayers; i++){
        if(playersArray[i]==NULL){
            continue;
        }
        if(playersArray[i]->isPlayer(playerName)){
            playersArray[i]->addLife();
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXISTS;
}

GameStatus Game::addStrength (const char * playerName, int strengthToAdd){
    if(strengthToAdd<0){
        return INVALID_PARAM;
    }
    for(int i=0; i<maxPlayers; i++){
        if(playersArray[i]==NULL){
            continue;
        }
        if(playersArray[i]->isPlayer(playerName)){
            playersArray[i]->addStrength(strengthToAdd);
            return SUCCESS;
        }
    }
    return NAME_DOES_NOT_EXISTS;
}

bool Game::removeAllPlayersWithWeakWeapon(int weaponStrength){
    bool flag=false;
    for(int i=0; i<maxPlayers; i++){
        if(playersArray[i]==NULL){
            continue;
        }
        if(playersArray[i]->weaponIsWeak(weaponStrength)){
            flag=true;
            playersArray[i]=NULL;
        }
    }
    return flag;
}

GameStatus Game::fight(const char * playerName1, const char * playerName2){
    int firstPlayer=-1;
    int secondPlayer=-1;
    for(int i=0; i<maxPlayers; i++){
        if(playersArray[i]==NULL){
            continue;
        }
        if(playersArray[i]->isPlayer(playerName1)){
            firstPlayer=i;
        }
        if(playersArray[i]->isPlayer(playerName2)){
            secondPlayer=i;
        }
    }
    if(firstPlayer==-1 || secondPlayer==-1){
        return NAME_DOES_NOT_EXISTS;
    }
    if(playersArray[firstPlayer]->fight(*playersArray[secondPlayer])){
        if(!playersArray[firstPlayer]->isAlive()){
            playersArray[firstPlayer]=NULL;
        }
        if(!playersArray[secondPlayer]->isAlive()){
            playersArray[secondPlayer]=NULL;
        }
        return SUCCESS;
    }
    return FIGHT_FAILED;
}

static void bubbleSort(Player** playersArray, int arraySize){
    for (int i = 0; i < arraySize; i++) {
        for (int j = i + 1; j < arraySize; j++) {
            if(playersArray[i]==NULL){
                if(playersArray[j]==NULL){
                    continue;
                }
                Player* bub;
                bub = playersArray[i];
                playersArray[i] = playersArray[j];
                playersArray[j] = bub;
                continue;
            }
            if(playersArray[j]==NULL){
                continue;
            }
            if (*playersArray[j] < *playersArray[i]) {
                Player* bub;
                bub = playersArray[i];
                playersArray[i] = playersArray[j];
                playersArray[j] = bub;
            }
        }
    }
}

ostream& operator<<(ostream& os, const Game& game){
    bubbleSort(game.playersArray, game.maxPlayers);
    for (int i = 0; i < game.maxPlayers; i++) {
        if(game.playersArray[i] == NULL){
            continue;
        }
        os<<"player "<<i<<": "<<game.playersArray[i]->name<<","<<endl;
    }
    return os;
}