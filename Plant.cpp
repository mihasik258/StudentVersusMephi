#include "Plant.h"
#include "Constants.h"

Plant::Plant(int row, int col, const std::string &initial_directory)
        : row(row), col(col), hp(0), hp_limit(1), is_destroyed(false), directory(initial_directory) {}

[[nodiscard]] bool Plant::isZombieNearby(const Zombie *zombie,const Map<Block> &map) const {
    auto [left_limit, right_limit] = map.getHorizontalLimits(row, col);
    right_limit -= 35;
    int zombie_new_location = zombie->xLocation() - Zombie::DX;
    return zombie->getRow() == row &&
           zombie_new_location < right_limit &&
           zombie_new_location > left_limit;
}

void Plant::handleZombie(Zombie *zombie,const Map<Block> &map) {
    if (isZombieNearby(zombie, map)) {
        hp++;
        if (hp >= hp_limit) {
            zombie->startMoving();
            is_destroyed = true;
        }
    }
}


