#pragma once

#include "rsdl.hpp"
#include "Player.h"

class Icons {
public:
    struct IconData {
        bool is_chosen;
        int price;
        std::string icon_directory_dim;
        std::string icon_directory_bright;
        int icon_y_position;
    };
    std::map<std::string, IconData> iconData;
    Icons();
    void updateIconSelection(int mouse_y);
    void displayIconBar(window &win, Player &player);
    void displayLayout(window &win, Player &player);
};

