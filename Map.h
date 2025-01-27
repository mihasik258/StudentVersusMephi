#pragma once

#include "Block.h"

//------------------------------------------------------------------------------
// Шаблонный класс Map
//------------------------------------------------------------------------------
/**
 * @brief Представляет карту игры как сетку блоков.
 * 
 * @tparam T Тип блоков, используемых в сетке.
 */
template <typename T>
class Map {
public:
    std::vector<std::vector<T>> grid; ///< Сетка блоков.

    /**
     * @brief Конструктор карты.
     * @param rows Количество строк.
     * @param cols Количество столбцов.
     */
    Map(int rows, int cols) : grid(rows, std::vector<T>(cols)) {}
    /**
     * @brief Инициализирует блоки в сетке с заданными параметрами.
     * @param startX Начальная координата X.
     * @param startY Начальная координата Y.
     * @param blockWidth Ширина блока.
     * @param blockHeight Высота блока.
     */
    void initializeBlocks(int startX, int startY, int blockWidth, int blockHeight) {
        for (int y = 0; y < grid.size(); y++) {
            for (int x = 0; x < grid[y].size(); x++) {
                grid[y][x] = T(
                        startX + x * blockWidth,
                        startX + (x + 1) * blockWidth,
                        startY + y * blockHeight,
                        startY + (y + 1) * blockHeight
                );
            }
        }
    }
    /**
     * @brief Возвращает горизонтальные границы блока.
     * @param row Строка блока.
     * @param col Столбец блока.
     * @return Пара границ по оси X.
     * @throws std::out_of_range Если индекс блока некорректен.
     */
    [[nodiscard]] std::pair<int, int> getHorizontalLimits(int row, int col) const {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[row].size()) {
            throw std::out_of_range("Invalid row or column index.");
        }
        const T& block = grid[row][col];
        return {block.x1, block.x2};
    }
    /**
     * @brief Возвращает вертикальные  границы блока.
     * @param row Строка блока.
     * @param col Столбец блока.
     * @return Пара границ по оси Y.
     * @throws std::out_of_range Если индекс блока некорректен.
     */
    [[nodiscard]] std::pair<int, int> getVerticalLimits(int row, int col) const {
        if (row < 0 || row >= grid.size() || col < 0 || col >= grid[row].size()) {
            throw std::out_of_range("Invalid row or column index.");
        }
        const T& block = grid[row][col];
        return {block.y1, block.y2};
    }
    /**
     * @brief Проверяет, находится ли точка внутри переднего двора карты.
     * @param mouseX Координата X точки.
     * @param mouseY Координата Y точки.
     * @return true, если точка находится в пределах карты.
     */
    [[nodiscard]] bool isClickInFrontyard(int mouseX, int mouseY) const {
        int rightBound = grid[0].back().x2;
        int leftBound = grid[0].front().x1;
        int upperBound = grid.front().front().y1;
        int lowerBound = grid.back().front().y2;
        return (mouseX > leftBound && mouseX < rightBound && mouseY > upperBound && mouseY < lowerBound);
    }
    /**
     * @brief Определяет, в каком блоке произошёл клик.
     * @param mouseX Координата X клика.
     * @param mouseY Координата Y клика.
     * @param row Выходной параметр: строка блока.
     * @param col Выходной параметр: столбец блока.
     * @return true, если клик произошёл в пределах карты.
     */
    bool determineClickBlock(int mouseX, int mouseY, int &row, int &col) const {
        auto it = std::find_if(grid.begin(), grid.end(), [&](const std::vector<T>& rowBlocks) {
            return std::any_of(rowBlocks.begin(), rowBlocks.end(), [&](const T& block) {
                return block.contains(mouseX, mouseY);
            });
        });
        if (it != grid.end()) {
            row = std::distance(grid.begin(), it);
            auto blockIt = std::find_if(it->begin(), it->end(), [&](const T& block) {
                return block.contains(mouseX, mouseY);
            });
            col = std::distance(it->begin(), blockIt);
            return true;
        }
        return false;
    }
    /**
     * @brief Проверяет, находится ли клик внутри указанного блока.
     * @param row Строка блока.
     * @param col Столбец блока.
     * @param mouseX Координата X клика.
     * @param mouseY Координата Y клика.
     * @return true, если точка находится внутри блока.
     */
    [[nodiscard]] bool isClickWithinBlock(int row, int col, int mouseX, int mouseY) const {
        if (row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size()) {
            return grid[row][col].contains(mouseX, mouseY);
        }
        return false;
    }
};
