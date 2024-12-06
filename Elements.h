#pragma once


#include <vector>
#include <memory>
#include "Zombie.h"
#include "Plant.h"
#include "Pea.h"
#include "Sun.h"
#include "Sunflower.h"
#include "Walnut.h"
#include "Icepea.h"
#include "Firepea.h"
#include "Fireshooter.h"
#include "Iceshooter.h"
#include "Map.h"

class Elements {
public:
    std::vector<Zombie> zombies;
    std::vector<std::unique_ptr<Plant>> plants;
    std::vector<std::unique_ptr<Pea>> peas;
    std::vector<Sun> suns;
    Elements();
    void genSkySun();
    void removeSuns();
    void genPlantSun(Plant* plant, const Map<Block> &map);
    void setAllZombiesMoving();
    void addZombie(const Zombie &zombie);
    bool hasZombieReachedAnyElement(Zombie &zombie, const Map<Block> &map);
    bool canMove(Zombie & zombie, const Map<Block> &map);
    void moveZombies(const Map<Block> &map);
    bool canPeaMove(Pea & pea, const Map<Block> &map);
    void movePeas(const Map<Block> &map);
    void moveSuns(const Map<Block> &map);
    [[nodiscard]] bool hasZombiesPassedBoundary(int boundary_x) const;
    void handlePlant(const Map<Block> &map);
    void firePeas(const Map<Block> &map);
    void applyHitting(int p_ind, int z_ind);
    void handlePea(const Map<Block> &map);
    void handleMovements(const Map<Block> &map, int clk);
};

