#pragma once


#include "Peashooter.h"
#include "Firepea.h"
#include "Zombie.h"

class Fireshooter : public Peashooter {
public:
    Fireshooter(int row, int col);
    void fire(std::vector<std::unique_ptr<Pea>> &peas, const Map<Block> &map, std::vector<Zombie> &zombies) override;
};
