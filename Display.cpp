#include "Display.h"

void displayPlants(window &win, const std::vector<std::unique_ptr<Plant>> &plants, const Map<Block> &map) {
    for (const auto &plant : plants) {
        plant->draw(win, map); 
    }
}
void displayPeas(window & win, std::vector<std::unique_ptr<Pea>> & peas, const Map<Block> &map){
    for (const auto &pea : peas) {
        pea->draw(win, map); 
    }
}
void displayZombies(window & win, std::vector<std::unique_ptr<Zombie>> & zombies, const Map<Block> &map){
    for (const auto & zombie : zombies){
        zombie->draw(win, map); 
    }
}
void displaySuns(window & win, std::vector<Sun> suns, const Map<Block> &map){
    for (auto & sun : suns){
        int col = sun.getFinalCol();
        auto [left_bound, right_bound] = map.getHorizontalLimits(0, col);
        int x_location = left_bound;
        win.draw_png(Sun::DIRECTORY, x_location, sun.getYLocation(), ELEMENT_WIDTH, ELEMENT_HEIGHT);
    }
}
void displayGameElements(window &win, Elements &elements, const Map<Block> &map) {
    displayZombies(win, elements.zombies, map);
    displayPlants(win, elements.plants, map);
    displayPeas(win, elements.peas, map);
    displaySuns(win, elements.suns, map);
}

void displayLosingMessage(window & win){
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIM_DIRECTORY);
    win.draw_png(LOSING_MESSAGE_DIRECTORY, window::WIDTH/4, window::HEIGHT/8 - 40, 500, 500);
}

void displayWinningMessage(window & win){
    win.draw_bg(BLACK_SCREEN_DIRECTORY);
    win.draw_bg(BACKGROUND_DIM_DIRECTORY);
    win.draw_png(WINNING_MESSAGE_DIRECTORY, window::WIDTH/3, window::HEIGHT/8 - 60, 300, 550);
}

bool is_an_icon_chosen(int mouse_x, int mouse_y){
    if (mouse_x > Icons::X1 && mouse_x < Icons::X2 &&
        mouse_y > Icons::Y1 && mouse_y < Icons::Y2)
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
        getline (myfile, line);
        level.level_num = stoi(line);
        myfile.close();
    }
    else std::cout << "Unable to open file";
}

bool clickedStart(int mouse_x, int mouse_y){
    if (mouse_x > window::TAP_TO_START_X1 && mouse_y < window::TAP_TO_START_X2 &&
        mouse_y > window::TAP_TO_START_Y1 && mouse_y < window::TAP_TO_START_Y2)
        return true;
    return false;
}
void processEvents(bool &quit, bool &game_started, bool &mouse_click, int &mouse_x, int &mouse_y) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_q) {
                quit = true;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                mouse_click = true;
                mouse_x = event.button.x;
                mouse_y = event.button.y;
            }
            break;
        }
    }
}
void displayStarting(window &win) {
    bool game_started = false;
    bool quit = false;
    bool mouse_click = false;
    int mouse_x = 0, mouse_y = 0;

    while (!game_started && !quit) {
        win.draw_png(STARTING_SCREEN_DIRECTORY, 0, 0, window::WIDTH, window::HEIGHT);

        processEvents(quit, game_started, mouse_click, mouse_x, mouse_y);

        if (mouse_click) {
            if (clickedStart(mouse_x, mouse_y)) {
                game_started = true;
            }
            mouse_click = false;
        }

        win.update_screen();
        SDL_Delay(10); 
    }
}
void init_game(window & win, Level & level, Player & player, Map<Block> &map){
    displayStarting(win);
    win.play_music("joke.mp3", -1);
    readSavedata(player, level);
    level.readLevelData();
    level.decideZombieCountForEachSec();
    map.initializeBlocks(X_UPPER_LEFT, Y_UPPER_LEFT, BLOCK_WIDTH, BLOCK_HEIGHT);
    player.sun_count = Sun::INIT_COUNT;
    player.is_first_click_made = false;
}
