#pragma once

#include <vector>
#include <stdexcept>

//------------------------------------------------------------------------------
// Класс Block
//------------------------------------------------------------------------------
/**
 * @brief Представляет отдельный блок на карте игры.
 */
class Block {
public:
    int x1, x2; ///< Границы блока по оси X.
    int y1, y2; ///< Границы блока по оси Y.

    /**
     * @brief Конструктор блока.
     * @param startX1 Левая граница.
     * @param startX2 Правая граница.
     * @param startY1 Верхняя граница.
     * @param startY2 Нижняя граница.
     */
    explicit Block(int startX1 = 0, int startX2 = 0, int startY1 = 0, int startY2 = 0);
    /**
     * @brief Проверяет, находится ли точка внутри блока.
     * @param mouseX Координата X точки.
     * @param mouseY Координата Y точки.
     * @return true, если точка внутри блока.
     */
    [[nodiscard]] bool contains(int mouseX, int mouseY) const;
};


