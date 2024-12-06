#include "Iceshooter.h"
#include "Constants.h"

Iceshooter::Iceshooter(int row, int col) : Peashooter(row, col) {
    directory = ICESHOOTER_DIRECTORY;
    hp_limit = PEASHOOTER_HP_LIMIT;
}

void Iceshooter::fire(std::vector<std::unique_ptr<Pea>> &peas,const Map<Block> &map, std::vector<Zombie> &zombies){
    if (zombiesInRow(zombies)) {
        auto new_icepea = std::make_unique<Icepea>();
        new_icepea->row = row;
        auto [left_limit, right_limit] = map.getHorizontalLimits(row, col);
        new_icepea->x_location = right_limit - 10;
        peas.push_back(std::move(new_icepea));
    }
}
