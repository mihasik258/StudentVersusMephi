#pragma once


#include "Zombie.h"
#include "Map.h"

//------------------------------------------------------------------------------
// Класс Plant
//------------------------------------------------------------------------------
/**
 * @brief Базовый класс для всех растений, которые игрок может размещать на поле.
 */
class Plant {
public:
    std::string directory;
    /**
     * @brief Конструктор растения.
     * @param row Ряд.
     * @param col Колонка.
     */
    Plant(int row, int col, const std::string &initial_directory);
    virtual ~Plant() = default;
    /**
     * @brief Проверяет, цело ли растение чтобы запустить зомби дальше.
     * @param zombie Зомби для проверки.
     */
    virtual void handleZombie(Zombie *zombie, const Map<Block> &map);
    /**
     * @brief Проверяет, находится ли зомби рядом с растением.
     * @param zombie Зомби для проверки.
     * @return true, если зомби находится в пределах поражения.
     */
    [[nodiscard]] bool isZombieNearby(const Zombie *zombie, const Map<Block> &map) const;
    virtual void draw(window &win, const Map<Block> &map) const = 0;
    [[nodiscard]] int getRow() const { return row; }
    [[nodiscard]] int getCol() const { return col; }
    [[nodiscard]] bool isDestroyed() const { return is_destroyed; }
protected:
    int row; ///< Ряд, где размещено растение.
    int col; ///< Колонка, где размещено растение.
    int hp; ///< Текущее здоровье растения.
    int hp_limit; ///< Максимальное здоровье растения.
    bool is_destroyed; ///< Флаг, указывающий на разрушение растения.
};

