#pragma once

#include "Plant.h"
#include "Pea.h"
#include "Zombie.h"
//------------------------------------------------------------------------------
// Класс Peashooter
//------------------------------------------------------------------------------
/**
 * @brief Класс Peashooter
 * 
 * Базовое растение, стреляющее обычными снарядами.
 */
class Peashooter : public Plant {
public:
    /**
     * @brief Конструктор Peashooter.
     * @param row Ряд на игровом поле.
     * @param col Колонка на игровом поле.
     */
    Peashooter(int row, int col);
    /**
     * @brief Проверяет, находятся ли зомби в текущем ряду.
     * @param zombies Список зомби.
     * @return true, если в ряду есть зомби.
     */
    [[nodiscard]] bool zombiesInRow(const std::vector<std::unique_ptr<Zombie>> &zombies) const;
    /**
     * @brief Стреляет снарядами по зомби.
     * @param peas Коллекция снарядов.
     * @param map Карта игрового поля.
     * @param zombies Список зомби.
     */
    virtual void fire(std::vector<std::unique_ptr<Pea>> &peas, const Map<Block> &map, std::vector<std::unique_ptr<Zombie>> &zombies);
    void draw(window &win, const Map<Block> &map) const override;
    static constexpr int PRICE = 100;
    static constexpr int HP_LIMIT = 5;
    static constexpr int ICON_Y1 = 167;
    static constexpr const char* DIRECTORY = "./Image_Assets/PeashooterC.png";
    static constexpr const char* ICON_BRIGHT_DIRECTORY = "./Image_Assets/icon_peashooter_100.png";
    static constexpr const char* ICON_DIM_DIRECTORY = "./Image_Assets/icon_peashooter_100_dim.png";
};

