#include "Block.h"
#include "Constants.h"

Block::Block(int startX1, int startX2, int startY1, int startY2)
        : x1(startX1), x2(startX2), y1(startY1), y2(startY2) {}
[[nodiscard]] bool Block::contains(int mouseX, int mouseY) const {
    return mouseX > x1 && mouseX < x2 && mouseY > y1 && mouseY < y2;
}
