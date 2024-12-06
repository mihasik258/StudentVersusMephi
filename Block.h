#pragma once

#include <vector>
#include <stdexcept>

class Block {
public:
    int x1, x2;
    int y1, y2;
    explicit Block(int startX1 = 0, int startX2 = 0, int startY1 = 0, int startY2 = 0);
    [[nodiscard]] bool contains(int mouseX, int mouseY) const;
};


