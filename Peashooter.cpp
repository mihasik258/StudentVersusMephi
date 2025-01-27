#include "Peashooter.h"


Peashooter::Peashooter(int row, int col) : Plant(row, col, DIRECTORY){
    hp_limit = HP_LIMIT;
}
[[nodiscard]] bool Peashooter::zombiesInRow(const std::vector<std::unique_ptr<Zombie>> &zombies) const {
	return std::any_of(zombies.begin(), zombies.end(),
	                   [&](const std::unique_ptr<Zombie> &zombie) {
	                       return zombie->getRow() == row;
	                   });
}
void Peashooter::fire(std::vector<std::unique_ptr<Pea>> &peas,const Map<Block> &map, std::vector<std::unique_ptr<Zombie>> &zombies) {
    if (zombiesInRow(zombies)) {
        auto new_pea = std::make_unique<Pea>();
        new_pea->row = row;
        auto [left_limit, right_limit] = map.getHorizontalLimits(row, col);
        new_pea->x_location = right_limit - 10;
        peas.push_back(std::move(new_pea));
    }
}
void Peashooter::draw(window &win, const Map<Block> &map) const{
    auto [left_bound, right_bound] = map.getHorizontalLimits(row, col);
    auto [upper_bound, lower_bound] = map.getVerticalLimits(row, col);
    win.draw_png(directory, left_bound + 9, upper_bound + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
}
