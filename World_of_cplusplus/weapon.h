//
// Created by HP on 08.06.2018.
//

#ifndef EX4_WEAPON_H
#define EX4_WEAPON_H
#include <iostream>

enum Target {
    LEVEL,
    STRENGTH,
    LIFE
};

struct Weapon {
    char *name;
    Target target;
    int hitStrength;
    Weapon();
    Weapon(const char *name, Target target, int hit_strength);
    ~Weapon();
    Target getTarget() const;
    int getHitStrength() const;
    int getValue() const;
    bool operator==(const Weapon& weapon);
    bool operator!=(const Weapon& weapon);
    bool operator>(const Weapon& weapon);
    bool operator<(const Weapon& weapon);
    void operator<<(const Weapon& weapon);
};


#endif //EX4_WEAPON_H
