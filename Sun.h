#pragma once


class Sun {
public:
    int final_row;
    int final_col;
    int y_location;
    int wait_seconds;
    explicit Sun(int row = 0, int col = 0, int y = 0, int wait = 0);
    void move(int lower_limit);
};

