#include "Sunflower.h"


Sunflower::Sunflower(int row, int col) : Plant(row, col), directory(SUNFLOWER_DIRECTORY), last_sun_generated_time(0) {
    hp_limit = SUNFLOWER_HP_LIMIT;
}
[[nodiscard]] bool Sunflower::canGenerate(int current_time) const {
    return current_time - last_sun_generated_time >= SUNFLOWER_SUN_TIME;
}
void Sunflower::updateTime(int current_time) {
    last_sun_generated_time = current_time;
}