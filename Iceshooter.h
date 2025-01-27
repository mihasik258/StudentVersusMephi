#pragma once


#include "Peashooter.h"
#include "Icepea.h"
#include "Zombie.h"

//------------------------------------------------------------------------------
// Класс Iceshooter
//------------------------------------------------------------------------------
/**
 * @brief Класс Iceshooter
 * 
 * Растение, стреляющее замораживающими снарядами.
 */
class Iceshooter : public Peashooter {
public:
    /**
     * @brief Конструктор Iceshooter.
     * @param row Ряд на игровом поле.
     * @param col Колонка на игровом поле.
     */
    Iceshooter(int row, int col);
    /**
     * @brief Стреляет замораживающими снарядами по зомби.
     * @param peas Коллекция снарядов.
     * @param map Карта игрового поля.
     * @param zombies Список зомби.
     */
    void fire(std::vector<std::unique_ptr<Pea>> &peas, const Map<Block> &map, std::vector<std::unique_ptr<Zombie>> &zombies) override;
    static constexpr int PRICE = 150;
    static constexpr int HP_LIMIT = 5;
    static constexpr int ICON_Y1 = 295;
    static constexpr const char* DIRECTORY = "./Image_Assets/Iceshooter.png";
    static constexpr const char* ICON_BRIGHT_DIRECTORY = "./Image_Assets/Icesh.png";
    static constexpr const char* ICON_DIM_DIRECTORY = "./Image_Assets/Icesh_black.png";
};
