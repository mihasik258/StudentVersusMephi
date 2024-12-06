#pragma once


#include "Plant.h"

class Sunflower : public Plant {
public:
    std::string directory;
    int last_sun_generated_time;
    Sunflower(int row, int col);
    [[nodiscard]] bool canGenerate(int current_time) const;
    void updateTime(int current_time);
};

