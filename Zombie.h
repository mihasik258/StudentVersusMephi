#pragma once


#include <string>
#include <unordered_map>
#include "Constants.h"

class Zombie {
public:
    int row;
    int x_location;
    int health;
    bool is_moving;
    int speed;
    std::string directory;
    std::unordered_map<std::string, bool> effects;

    explicit Zombie(int initial_x_location = STUDENT_INIT_X, int initial_health = 10, bool moving = true);
    void addEffect(const std::string &effect);
    void removeEffect(const std::string &effect);
    void move();
    void updateAppearance();
    [[nodiscard]] bool hasEffect(const std::string& effect_name) const;
};
