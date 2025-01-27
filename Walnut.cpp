#include "Walnut.h"
#include "Constants.h"

Walnut::Walnut(int row, int col)
        : Plant(row, col, UNTOUCHED_DIRECTORY){
    hp_limit = HP_LIMIT;
}

void Walnut::updateAppearance() {
    if (hp <= 4)
        directory = UNTOUCHED_DIRECTORY;
    else if (hp > 4 && hp <= 7)
        directory = CRACKED_1_DIRECTORY;
    else
        directory = CRACKED_2_DIRECTORY;
}

void Walnut::handleZombie(Zombie *zombie, const Map<Block> &map){
    if (isZombieNearby(zombie, map)) {
        hp++;
        updateAppearance();
        if (hp >= hp_limit) {
            is_destroyed = true;
            zombie->startMoving();
        }
    }
}
void Walnut::draw(window &win, const Map<Block> &map) const{
        auto [left_bound, right_bound] = map.getHorizontalLimits(row, col);
        auto [upper_bound, lower_bound] = map.getVerticalLimits(row, col);
        win.draw_png(directory, left_bound, upper_bound, ELEMENT_WIDTH, ELEMENT_HEIGHT);
}
