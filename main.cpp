#include "Display.h"


int main() {
    bool quit = false;
    long int clk = 0;
    bool mouse_click = false;
    int mouse_x = 0, mouse_y = 0;
    Level level;
    Elements game_characters;
    Icons icons;
    Player player;
    Map<Block> map(VERT_BLOCK_COUNT, HORIZ_BLOCK_COUNT);
    window win(window::WIDTH, window::HEIGHT);
    init_game(win, level, player, map);

    while (!quit) {
        bool gameOver = false;
        if (game_characters.hasZombiesPassedBoundary(X_UPPER_LEFT + 5)) {
            displayLosingMessage(win);
        } else if (level.isWaveCompleted(game_characters)) {
            displayWinningMessage(win);
        } else {
            icons.displayLayout(win, player);
            displayGameElements(win, game_characters, map);
            game_characters.updateAll(map, gameOver, clk);
            level.handleChanges(game_characters, map, clk);
        }
        processEvents(quit, gameOver, mouse_click, mouse_x, mouse_y);

        if (mouse_click) {
            handleClick(player, icons, level, game_characters, map, mouse_x, mouse_y);
            mouse_click = false; 
        }
        clk++;
        win.update_screen();
        SDL_Delay(CLK_LENGTH); 
    }
    return 0;
}
