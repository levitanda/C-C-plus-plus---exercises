#include <iostream>
#include <cstring>
#include "weapon.h"

using namespace std;

Weapon::Weapon(const char *name, Target target, int hit_strength){
    this->name = new char[strlen(name)+1];
    strcpy(this->name, name);
    this->target=target;
    this->hitStrength=hit_strength;
}

Weapon::Weapon(){
    this->name = NULL;
    this->target=LEVEL;
    this->hitStrength=0;
}

Weapon::~Weapon(){
    delete[] name;
}

Target Weapon::getTarget() const{
    return target;
}
int Weapon::getHitStrength() const{
    return hitStrength;
}
int Weapon::getValue() const{
    if(target==0){
        return hitStrength;
    }
    if(target==1){
        return 2*hitStrength;
    }
    if(target==2){
        return 3*hitStrength;
    }
    return hitStrength;
}

bool Weapon::operator==(const Weapon& weapon){
    if(this->getValue()==weapon.getValue()){
        return true;
    }
    return false;
}

bool Weapon::operator!=(const Weapon& weapon){
    if(this->getValue()!=weapon.getValue()){
        return true;
    }
    return false;
}
bool Weapon::operator>(const Weapon& weapon){
    if(this->getValue()>weapon.getValue()){
        return true;
    }
    return false;
}

bool Weapon::operator<(const Weapon& weapon){
    if(this->getValue()<weapon.getValue()){
        return true;
    }
    return false;
}
void Weapon::operator<<(const Weapon& weapon){
    cout<<"{weapon name: "<<weapon.name<<", weapon value: "<<weapon.getValue()<<"}";
}
