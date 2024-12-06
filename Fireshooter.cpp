#include "Fireshooter.h"
#include "Constants.h"

Fireshooter::Fireshooter(int row, int col) : Peashooter(row, col) {
    directory = FIRESHOOTER_DIRECTORY;
    hp_limit = PEASHOOTER_HP_LIMIT;
}

void Fireshooter::fire(std::vector<std::unique_ptr<Pea>> &peas, const Map<Block> &map, std::vector<Zombie> &zombies) {
    if (zombiesInRow(zombies)) {
        auto new_firepea = std::make_unique<Firepea>();
        new_firepea->row = row;
        auto [left_limit, right_limit] = map.getHorizontalLimits(row, col);
        new_firepea->x_location = right_limit - 10;
        peas.push_back(std::move(new_firepea));
    }
}