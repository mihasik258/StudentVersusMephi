#include "Plant.h"
#include "Constants.h"

Plant::Plant(int row, int col)
        : row(row), col(col), hp(0), hp_limit(1), is_destroyed(false) {}

[[nodiscard]] bool Plant::isZombieNearby(const Zombie &zombie,const Map<Block> &map) const {
    auto [left_limit, right_limit] = map.getHorizontalLimits(row, col);
    right_limit -= 35;
    int zombie_new_location = zombie.x_location - STUDENT_DX;
    return zombie.row == row &&
           zombie_new_location < right_limit &&
           zombie_new_location > left_limit;
}

void Plant::handleZombie(Zombie &zombie,const Map<Block> &map) {
    if (isZombieNearby(zombie, map)) {
        hp++;
        if (hp >= hp_limit) {
            zombie.is_moving = true;
            is_destroyed = true;
        }
    }
}


