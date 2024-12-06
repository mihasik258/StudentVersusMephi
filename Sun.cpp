#include "Sun.h"
#include "Constants.h"


Sun::Sun(int row, int col, int y, int wait)
        : final_row(row), final_col(col), y_location(y), wait_seconds(wait) {}
void Sun::move(int lower_limit) {
    if (y_location + SUN_DY < lower_limit) {
        y_location += SUN_DY;
    } else {
        wait_seconds++;
    }
}