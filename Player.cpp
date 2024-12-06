#include "Player.h"
#include "Constants.h"



Player::Player(int init_sun_count, bool first_click)
        : sun_count(init_sun_count), is_first_click_made(first_click) {}
void Player::pick_sun_if_clicked_on(Elements & elements, const Map<Block> &map, int mouse_x, int mouse_y, bool & sun_picked){
    for (int i = 0; i < elements.suns.size(); i++){
        int row = elements.suns[i].final_row; int col = elements.suns[i].final_col;
        auto [left_bound, right_bound] = map.getHorizontalLimits(row, col);
        int upper_bound = elements.suns[i].y_location;
        int lower_bound = elements.suns[i].y_location + ELEMENT_HEIGHT;
        if (mouse_x > left_bound && mouse_x < right_bound &&
            mouse_y > upper_bound && mouse_y < lower_bound){
            elements.suns.erase(elements.suns.begin() + i);
            sun_picked = true;
            sun_count += 50;
            return;
        }
        sun_picked = false;
    }
}
