#include "Zombie.h"

Zombie::Zombie()
    :
      x_location(INIT_X),
      health(10),
      is_moving(true),
      speed(DX),
      directory(HEALTHY_DIRECTORY){
      row = rand() % 5;
      effects["fire"] = false;
      effects["ice"] = false;
}
void Zombie::addEffect(const std::string &effect) {
    effects[effect] = true;
}
void Zombie::removeEffect(const std::string &effect) {
    auto it = effects.find(effect);
    if (it != effects.end()) {
        it->second = false; 
    }
}
void Zombie::move() {
    x_location -= speed;
}
void Zombie::updateAppearance() {
    if (effects["fire"]) {
        if (health > 7) directory = HEALTHY_FIRE_DIRECTORY;
        else if (health > 4) directory = MIDDLE_FIRE_DIRECTORY;
        else directory = INJURED_FIRE_DIRECTORY;
    } else if (effects["ice"]) {
        if (health > 7) directory = HEALTHY_FREEZE_DIRECTORY;
        else if (health > 4) directory = MIDDLE_FREEZE_DIRECTORY;
        else directory = INJURED_FREEZE_DIRECTORY;
    } else {
        if (health > 7) directory = HEALTHY_DIRECTORY;
        else if (health > 4) directory = MIDDLE_DIRECTORY;
        else directory = INJURED_DIRECTORY;
    }
}
[[nodiscard]] bool Zombie::hasEffect(const std::string& effect_name) const {
    auto it = effects.find(effect_name);
    return it != effects.end() && it->second;
}
void Zombie::draw(window &win, const Map<Block> &map) const {
    auto [upper_bound, lower_bound] = map.getVerticalLimits(row, 0);
    int y_location = upper_bound;
    win.draw_png(directory, x_location, y_location, ELEMENT_WIDTH, ELEMENT_HEIGHT);
}
void Zombie::startMoving() {
    is_moving = true;
}

void Zombie::stopMoving() {
    is_moving = false;
}

bool Zombie::isMoving() const {
    return is_moving;
}
std::vector<std::string> Zombie::getActiveEffects() const {
    std::vector<std::string> active_effects;
    for (const auto& [effect, is_active] : effects) {
        if (is_active) {
            active_effects.push_back(effect);
        }
    }
    return active_effects;
}
void Zombie::applyDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

bool Zombie::isDead() const {
    return health <= 0;
}

int Zombie::getHealth() const {
    return health;
}
int Zombie::getSpeed() const {
    return speed;
}

void Zombie::setSpeed(int new_speed) {
    if (new_speed > 0) {
        speed = new_speed;
    }
}
int Zombie::xLocation() const {
    return x_location;
}
int Zombie::getRow() const {
    return row;
}
void Zombie::setLocation(int l) {
    x_location = l;
}
void Zombie::setRow(int l) {
    row = l;
}
