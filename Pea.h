#pragma once


#include "Zombie.h"

class Pea {
public:
    int row;
    int x_location;
    std::string directory;

    Pea();
    virtual ~Pea() = default;

    virtual void applyEffect(Zombie &zombie);
    [[nodiscard]] bool reachedZombie(const Zombie &zombie) const;
    void move();
};


