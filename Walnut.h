#pragma once


#include "Plant.h"

class Walnut : public Plant {
public:
    std::string directory;

    Walnut(int row, int col);
    void updateAppearance();
    void handleZombie(Zombie &zombie, const Map<Block> &map) override;
};
