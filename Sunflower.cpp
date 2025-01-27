#include "Sunflower.h"


Sunflower::Sunflower(int row, int col) : Plant(row, col, DIRECTORY), last_sun_generated_time(0) {
    hp_limit = HP_LIMIT;
}
[[nodiscard]] bool Sunflower::canGenerate(int current_time) const {
    return current_time - last_sun_generated_time >= Sun::SUNFLOWER_TIME;
}
void Sunflower::updateTime(int current_time) {
    last_sun_generated_time = current_time;
}
void Sunflower::draw(window &win, const Map<Block> &map) const{
    auto [left_bound, right_bound] = map.getHorizontalLimits(row, col);
    auto [upper_bound, lower_bound] = map.getVerticalLimits(row, col);
    win.draw_png(directory, left_bound, upper_bound, ELEMENT_WIDTH, ELEMENT_HEIGHT);
}
