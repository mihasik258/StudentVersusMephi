#include "Zombie.h"

Zombie::Zombie(int initial_x_location, int initial_health, bool moving)
        : x_location(initial_x_location), health(initial_health), is_moving(moving), directory(STUDENT_HEALTHY_DIRECTORY), speed(STUDENT_DX) {
    row = rand() % 5;
    effects["fire"] = false;
    effects["ice"] = false;
}
void Zombie::addEffect(const std::string &effect) {
    effects[effect] = true;
}
void Zombie::removeEffect(const std::string &effect) {
    if (effects.find(effect) != effects.end()) {
        effects[effect] = false;
    }
}
void Zombie::move() {
    x_location -= speed;
}
void Zombie::updateAppearance() {
    if (effects["fire"]) {
        if (health > 7) directory = STUDENT_HEALTHY_FIRE_DIRECTORY;
        else if (health > 4) directory = STUDENT_MIDDLE_FIRE_DIRECTORY;
        else directory = STUDENT_INJURED_FIRE_DIRECTORY;
    } else if (effects["ice"]) {
        if (health > 7) directory = STUDENT_HEALTHY_FREEZE_DIRECTORY;
        else if (health > 4) directory = STUDENT_MIDDLE_FREEZE_DIRECTORY;
        else directory = STUDENT_INJURED_FREEZE_DIRECTORY;
    } else {
        if (health > 7) directory = STUDENT_HEALTHY_DIRECTORY;
        else if (health > 4) directory = STUDENT_MIDDLE_DIRECTORY;
        else directory = STUDENT_INJURED_DIRECTORY;
    }
}
[[nodiscard]] bool Zombie::hasEffect(const std::string& effect_name) const {
    auto it = effects.find(effect_name);
    return it != effects.end() && it->second;
}