#pragma once


#include "Zombie.h"
#include "Map.h"

class Plant {
public:
    int row;
    int col;
    int hp;
    int hp_limit;
    bool is_destroyed;

    Plant(int row, int col);
    virtual ~Plant() = default;

    virtual void handleZombie(Zombie &zombie, const Map<Block> &map);
    [[nodiscard]] bool isZombieNearby(const Zombie &zombie, const Map<Block> &map) const;
};

