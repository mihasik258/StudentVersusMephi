#pragma once

#include "Zombie.h"
#include "Pea.h"

class Icepea : public Pea {
public:
    Icepea();
    void applyEffect(Zombie &zombie) override;
};

