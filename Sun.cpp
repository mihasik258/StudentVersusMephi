#include "Sun.h"
#include "Constants.h"

void Sun::move(int lower_limit) {
    if (y_location + DY < lower_limit) {
        y_location += DY;
    } else {
        wait_seconds++;
    }
}
Sun::Sun()
    : final_row(0), final_col(0), y_location(0), wait_seconds(0) {}

void Sun::setFinalRow(int row) {
    final_row = row;
}

void Sun::setFinalCol(int col) {
    final_col = col;
}

void Sun::setYLocation(int y) {
    y_location = y;
}

void Sun::resetWaitSeconds() {
    wait_seconds = 0;
}

