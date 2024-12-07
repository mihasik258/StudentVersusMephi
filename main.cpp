#include "Display.h"

int main(){
    bool quit = false;
    long int clk = 0;
    Level level;
    Elements game_characters;
    Icons icons;
    Player player;
    Map<Block> map(VERT_BLOCK_COUNT, HORIZ_BLOCK_COUNT);
    window win(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game(win, level, player, map);
    while(!quit){
    	bool gameOver = false;
        if (game_characters.hasZombiesPassedBoundary(X_UPPER_LEFT + 5))
            displayLosingMessage(win);
        else if (level.isWaveCompleted(game_characters))
            displayWinningMessage(win);
        else {
            icons.displayLayout(win, player);
            displayGameElements(win, game_characters, map);
            game_characters.updateAll(map, gameOver, clk);
            level.handleChanges(game_characters, map,clk);
        }
        HANDLE(
                QUIT(quit = true);
        KEY_PRESS(q, quit = true);
        LCLICK({
                       handleClick(player, icons, level, game_characters, map, mouse_x, mouse_y);
               });
        );
        clk++;
        win.update_screen();
        DELAY(CLK_LENGTH);
    }
    return 0;
}
