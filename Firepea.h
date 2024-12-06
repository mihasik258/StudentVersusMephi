#pragma once


#include "Zombie.h"
#include "Pea.h"

class Firepea : public Pea {
public:
    Firepea();
    void applyEffect(Zombie &zombie) override;
};
