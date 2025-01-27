#pragma once


#include "Peashooter.h"
#include "Firepea.h"
#include "Zombie.h"

//------------------------------------------------------------------------------
// Класс Fireshooter
//------------------------------------------------------------------------------
/**
 * @brief Класс Fireshooter
 * 
 * Растение, стреляющее огненными снарядами.
 */
class Fireshooter : public Peashooter {
public:
    /**
     * @brief Конструктор Fireshooter.
     * @param row Ряд на игровом поле.
     * @param col Колонка на игровом поле.
     */
    Fireshooter(int row, int col);
    /**
     * @brief Стреляет огненными снарядами по зомби.
     * @param peas Коллекция снарядов.
     * @param map Карта игрового поля.
     * @param zombies Список зомби.
     */
    void fire(std::vector<std::unique_ptr<Pea>> &peas, const Map<Block> &map, std::vector<std::unique_ptr<Zombie>> &zombies) override;
    static constexpr int PRICE = 175;
    static constexpr int HP_LIMIT = 5;
    static constexpr int ICON_Y1 = 359;
    static constexpr const char* DIRECTORY = "./Image_Assets/Fireshooter.png";
    static constexpr const char* ICON_BRIGHT_DIRECTORY = "./Image_Assets/Firesh.png";
    static constexpr const char* ICON_DIM_DIRECTORY = "./Image_Assets/Firesh_b.png";
};
