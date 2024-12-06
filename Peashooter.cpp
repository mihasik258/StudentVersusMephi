#include "Peashooter.h"


Peashooter::Peashooter(int row, int col) : Plant(row, col), directory(PEASHOOTER_DIRECTORY) {
    hp_limit = PEASHOOTER_HP_LIMIT;
}
[[nodiscard]] bool Peashooter::zombiesInRow(const std::vector<Zombie> &zombies) const {
    return std::any_of(zombies.begin(), zombies.end(), [&](const Zombie &zombie) {
        return zombie.row == row;
    });
}
void Peashooter::fire(std::vector<std::unique_ptr<Pea>> &peas,const Map<Block> &map, std::vector<Zombie> &zombies) {
    if (zombiesInRow(zombies)) {
        auto new_pea = std::make_unique<Pea>();
        new_pea->row = row;
        auto [left_limit, right_limit] = map.getHorizontalLimits(row, col);
        new_pea->x_location = right_limit - 10;
        peas.push_back(std::move(new_pea));
    }
}