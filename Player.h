#pragma once


#include "Elements.h"

class Player {
public:
    int sun_count;
    bool is_first_click_made;
    std::string directory;
    explicit Player(int init_sun_count = INIT_SUN_COUNT, bool first_click = false);
    void pick_sun_if_clicked_on(Elements & elements, const Map<Block> &map, int mouse_x, int mouse_y, bool & sun_picked);
};
