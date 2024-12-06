#pragma once

#include "rsdl.hpp"
#include "Constants.h"
#include "Level.h"

void displayZombies(window & win, std::vector<Zombie> & zombies, const Map<Block> &map){
    for (auto & zombie : zombies){
        int row = zombie.row;
        auto [upper_bound, lower_bound] = map.getVerticalLimits(row, 0);
        int y_location = upper_bound;
        win.draw_png(zombie.directory, zombie.x_location, y_location, ELEMENT_WIDTH, ELEMENT_HEIGHT);
    }
}
void displayPeas(window & win, std::vector<Pea*> & peas, const Map<Block> &map){
    for (auto & pea : peas){
        int row = pea->row;
        auto [left_bound, right_bound] = map.getHorizontalLimits(0, 8);
        auto [upper_bound, lower_bound] = map.getVerticalLimits(row, 0);
        int y_location = upper_bound + 20;
        if (pea->x_location < (right_bound - 35))
            win.draw_png(pea->directory, pea->x_location, y_location, PEA_WIDTH, PEA_HEIGHT);
    }
}
void displayPlants(window &win, const std::vector<std::unique_ptr<Plant>> &plants, const Map<Block> &map) {
    for (const auto &plant : plants) {
        int col = plant->col;
        int row = plant->row;
        auto [left_bound, right_bound] = map.getHorizontalLimits(row, col);
        auto [upper_bound, lower_bound] = map.getVerticalLimits(row, col);
        if (auto walnut = dynamic_cast<Walnut*>(plant.get())) {
            win.draw_png(walnut->directory, left_bound + 9, upper_bound + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
        else if (auto peashooter = dynamic_cast<Peashooter*>(plant.get())) {
            win.draw_png(peashooter->directory, left_bound + 9, upper_bound + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
        else if (auto iceshooter = dynamic_cast<Iceshooter*>(plant.get())) {
            win.draw_png(iceshooter->directory, left_bound + 9, upper_bound + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
        else if (auto sunflower = dynamic_cast<Sunflower*>(plant.get())) {
            win.draw_png(sunflower->directory, left_bound + 9, upper_bound + 9, ELEMENT_WIDTH, ELEMENT_HEIGHT);
        }
    }
}

void displaySuns(window & win, std::vector<Sun> suns, const Map<Block> &map){
    for (auto & sun : suns){
        int col = sun.final_col;
        auto [left_bound, right_bound] = map.getHorizontalLimits(0, col);
        int x_location = left_bound;
        win.draw_png(SUN_DIRECTORY, x_location, sun.y_location, ELEMENT_WIDTH, ELEMENT_HEIGHT);
    }
}
void displayGameElements(window &win, Elements &elements, const Map<Block> &map) {
    displayZombies(win, elements.zombies, map);
    displayPlants(win, elements.plants, map);
    std::vector<Pea*> pea_ptrs;
    for (const auto &pea : elements.peas) {
        pea_ptrs.push_back(pea.get());
    }
    displayPeas(win, pea_ptrs, map);
    displaySuns(win, elements.suns, map);
}

void displayLosingMessage(window & win){
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIM_DIRECTORY);
    win.draw_png(LOSING_MESSAGE_DIRECTORY, WINDOW_WIDTH/4, WINDOW_HEIGHT/8 - 40, 500, 500);
}

void displayWinningMessage(window & win){
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIM_DIRECTORY);
    win.draw_png(WINNING_MESSAGE_DIRECTORY, WINDOW_WIDTH/3, WINDOW_HEIGHT/8 - 60, 300, 550);
}

bool is_an_icon_chosen(int mouse_x, int mouse_y){
    if (mouse_x > ICON_BAR_X1 && mouse_x < ICON_BAR_X2 &&
        mouse_y > ICON_BAR_Y1 && mouse_y < ICON_BAR_Y2)
        return true;
    return false;
}

void handleClick(Player & player, Icons & icons, Level & level, Elements & elements, Map<Block> &map, int mouse_x, int mouse_y){
    bool sun_picked = false;
    if (!player.is_first_click_made){
        if (is_an_icon_chosen(mouse_x, mouse_y)){
            icons.updateIconSelection(mouse_y);
            player.is_first_click_made = true;
        }
        player.pick_sun_if_clicked_on(elements, map, mouse_x, mouse_y, sun_picked);
        /*
        if (!sun_picked && Block::isClickInFrontyard(map, mouse_x, mouse_y))
            elements.removeClicked(map, mouse_x, mouse_y);*/
    } else if (map.isClickInFrontyard(mouse_x, mouse_y)) {
        if (icons.iconData["walnut"].is_chosen) {
            level.createPlant<Walnut>(player, map, elements, icons, mouse_x, mouse_y, "walnut");
        } else if (icons.iconData["peashooter"].is_chosen) {
            level.createPlant<Peashooter>(player, map, elements, icons, mouse_x, mouse_y, "peashooter");
        } else if (icons.iconData["iceshooter"].is_chosen) {
            level.createPlant<Iceshooter>(player, map, elements, icons, mouse_x, mouse_y, "iceshooter");
        } else if (icons.iconData["fireshooter"].is_chosen) {
            level.createPlant<Fireshooter>(player, map, elements, icons, mouse_x, mouse_y, "fireshooter");
        } else if (icons.iconData["sunflower"].is_chosen) {
            level.createPlant<Sunflower>(player, map, elements, icons, mouse_x, mouse_y, "sunflower");
        }
        player.is_first_click_made = false;
    }
}

void readSavedata(Player & player, Level & level){
    std::string line;
    std::ifstream myfile ("savedata.txt");
    if (myfile.is_open()){
        getline (myfile,line);
        //player.name = line;
        getline (myfile, line);
        level.level_num = stoi(line);
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

bool clickedStart(int mouse_x, int mouse_y){
    if (mouse_x > TAP_TO_START_X1 && mouse_y < TAP_TO_START_X2 &&
        mouse_y > TAP_TO_START_Y1 && mouse_y < TAP_TO_START_Y2)
        return true;
    return false;
}

void displayStarting(window & win){
    bool game_started = false;
    bool quit = false;
    while (quit || !game_started){
        win.draw_png(STARTING_SCREEN_DIRECTORY, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
        HANDLE(
                QUIT(quit = true);
        KEY_PRESS(q, quit = true);
        LCLICK({
                       if (clickedStart(mouse_x, mouse_y))
                       game_started = true;
               });
        );

        win.update_screen();
        DELAY(10);
    }
}
void init_game(window & win, Level & level, Player & player, Map<Block> &map){
    displayStarting(win);
    win.play_music("joke.mp3", -1);
    readSavedata(player, level);
    level.readLevelData();
    level.decideZombieCountForEachSec();
    map.initializeBlocks(X_UPPER_LEFT, Y_UPPER_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT);
    player.sun_count = INIT_SUN_COUNT;
    player.is_first_click_made = false;
}
