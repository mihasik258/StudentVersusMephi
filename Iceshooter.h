#pragma once


#include "Peashooter.h"
#include "Icepea.h"
#include "Zombie.h"

class Iceshooter : public Peashooter {
public:
    Iceshooter(int row, int col);
    void fire(std::vector<std::unique_ptr<Pea>> &peas, const Map<Block> &map, std::vector<Zombie> &zombies) override;
};
