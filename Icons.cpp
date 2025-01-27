#include "Icons.h"
#include "Constants.h"


Icons::Icons() {
    iconData["sunflower"] = {false, Sunflower::PRICE, Sunflower::ICON_DIM_DIRECTORY, Sunflower::ICON_BRIGHT_DIRECTORY, Sunflower::ICON_Y1};
    iconData["peashooter"] = {false, Peashooter::PRICE, Peashooter::ICON_DIM_DIRECTORY, Peashooter::ICON_BRIGHT_DIRECTORY, Peashooter::ICON_Y1};
    iconData["walnut"] = {false, Walnut::PRICE, Walnut::ICON_DIM_DIRECTORY, Walnut::ICON_BRIGHT_DIRECTORY, Walnut::ICON_Y1};
    iconData["iceshooter"] = {false, Iceshooter::PRICE, Iceshooter::ICON_DIM_DIRECTORY, Iceshooter::ICON_BRIGHT_DIRECTORY, Iceshooter::ICON_Y1};
    iconData["fireshooter"] = {false, Fireshooter::PRICE, Fireshooter::ICON_DIM_DIRECTORY, Fireshooter::ICON_BRIGHT_DIRECTORY, Fireshooter::ICON_Y1};
}
void Icons::updateIconSelection(int mouse_y) {
    for (auto &[type, data] : iconData) {
        data.is_chosen = false;
    }
    for (auto &[type, data] : iconData) {
        if (mouse_y > data.icon_y_position && mouse_y < data.icon_y_position + HEIGHT) {
            data.is_chosen = true;
            break;
        }
    }
}
void Icons::displayIconBar(window &win, Player &player) {
    for (auto &[type, data] : iconData) {
        const std::string &directory = (player.sun_count >= data.price) ? data.icon_directory_bright : data.icon_directory_dim;
        win.draw_png(directory, X1 + 3, data.icon_y_position, WIDTH, HEIGHT);
    }
}
void Icons::displayLayout(window &win, Player &player) {
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIRECTORY);
    win.draw_png(DIRECTORY, 20, 100, BAR_WIDTH, BAR_HEIGHT);
    win.draw_png(DIRECTORY, 20, 300, BAR_WIDTH, BAR_HEIGHT);
    win.draw_png(Sun::DIRECTORY, 5, 5, Sun::WIDTH, Sun::HEIGHT);
    displayIconBar(win, player);
}
