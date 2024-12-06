#include "Icons.h"
#include "Constants.h"


Icons::Icons() {
    iconData["sunflower"] = {false, SUNFLOWER_PRICE, SUNFLOWER_ICON_DIM_DIRECTORY, SUNFLOWER_ICON_BRIGHT_DIRECTORY, SUNFLOWER_ICON_Y1};
    iconData["peashooter"] = {false, PEASHOOTER_PRICE, PEASHOOTER_ICON_DIM_DIRECTORY, PEASHOOTER_ICON_BRIGHT_DIRECTORY, PEASHOOTER_ICON_Y1};
    iconData["walnut"] = {false, WALNUT_PRICE, WALNUT_ICON_DIM_DIRECTORY, WALNUT_ICON_BRIGHT_DIRECTORY, WALNUT_ICON_Y1};
    iconData["iceshooter"] = {false, ICESHOOTER_PRICE, ICESHOOTER_ICON_DIM_DIRECTORY, ICESHOOTER_ICON_BRIGHT_DIRECTORY, ICESHOOTER_ICON_Y1};
    iconData["fireshooter"] = {false, FIRESHOOTER_PRICE, FIRESHOOTER_ICON_DIM_DIRECTORY, FIRESHOOTER_ICON_BRIGHT_DIRECTORY, FIRESHOOTER_ICON_Y1};
}
void Icons::updateIconSelection(int mouse_y) {
    for (auto &[type, data] : iconData) {
        data.is_chosen = false;
    }
    for (auto &[type, data] : iconData) {
        if (mouse_y > data.icon_y_position && mouse_y < data.icon_y_position + ICON_HEIGHT) {
            data.is_chosen = true;
            break;
        }
    }
}
void Icons::displayIconBar(window &win, Player &player) {
    for (auto &[type, data] : iconData) {
        const std::string &directory = (player.sun_count >= data.price) ? data.icon_directory_bright : data.icon_directory_dim;
        win.draw_png(directory, ICON_BAR_X1 + 3, data.icon_y_position, ICON_WIDTH, ICON_HEIGHT);
    }
}
void Icons::displayLayout(window &win, Player &player) {
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIRECTORY);
    win.draw_png(ICON_BAR_DIRECTORY, 20, 100, ICON_BAR_WIDTH, ICON_BAR_HEIGHT);
    win.draw_png(ICON_BAR_DIRECTORY, 20, 300, ICON_BAR_WIDTH, ICON_BAR_HEIGHT);
    win.draw_png(SUN_DIRECTORY, 5, 5, SUN_WIDTH, SUN_HEIGHT);
    displayIconBar(win, player);
}