#pragma once

#include "Plant.h"
#include "Pea.h"
#include "Zombie.h"

class Peashooter : public Plant {
public:
    std::string directory;
    Peashooter(int row, int col);
    [[nodiscard]] bool zombiesInRow(const std::vector<Zombie> &zombies) const;
    virtual void fire(std::vector<std::unique_ptr<Pea>> &peas, const Map<Block> &map, std::vector<Zombie> &zombies);
};

