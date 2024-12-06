#include "Walnut.h"
#include "Constants.h"

Walnut::Walnut(int row, int col)
        : Plant(row, col), directory(WALNUT_UNTOUCHED_DIRECTORY) {
    hp_limit = WALNUT_HP_LIMIT;
}

void Walnut::updateAppearance() {
    if (hp <= 4)
        directory = WALNUT_UNTOUCHED_DIRECTORY;
    else if (hp > 4 && hp <= 7)
        directory = WALNUT_CRACKED_1_DIRECTORY;
    else
        directory = WALNUT_CRACKED_2_DIRECTORY;
}

void Walnut::handleZombie(Zombie &zombie, const Map<Block> &map){
    if (isZombieNearby(zombie, map)) {
        hp++;
        updateAppearance();
        if (hp >= hp_limit) {
            is_destroyed = true;
            zombie.is_moving = true;
        }
    }
}
