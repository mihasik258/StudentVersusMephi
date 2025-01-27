#pragma once


#include "Plant.h"

//------------------------------------------------------------------------------
// Класс Walnut
//------------------------------------------------------------------------------
/**
 * @brief Класс Walnut
 * 
 * Представляет растение-орех, которое служит защитным барьером на игровом поле.
 */
class Walnut : public Plant {
public:
    /**
     * @brief Конструктор ореха.
     * @param row Ряд на игровом поле.
     * @param col Колонка на игровом поле.
     */
    Walnut(int row, int col);
    /**
     * @brief Обновляет внешний вид ореха в зависимости от его здоровья.
     */
    void updateAppearance();
    /**
     * @brief Обрабатывает взаимодействие с зомби.
     * @param zombie Зомби, взаимодействующий с орехом.
     * @param map Карта игрового поля.
     */
    void handleZombie(Zombie *zombie, const Map<Block> &map) override;
    void draw(window &win, const Map<Block> &map) const override;
    static constexpr int PRICE = 50;
    static constexpr int HP_LIMIT = 15;
    static constexpr int ICON_Y1 = 231;
    static constexpr const char* UNTOUCHED_DIRECTORY = "./Image_Assets/yan.png";
    static constexpr const char* CRACKED_1_DIRECTORY = "./Image_Assets/byte.png";
    static constexpr const char* CRACKED_2_DIRECTORY = "./Image_Assets/byte.png";
    static constexpr const char* ICON_BRIGHT_DIRECTORY = "./Image_Assets/icon_walnut.png";
    static constexpr const char* ICON_DIM_DIRECTORY = "./Image_Assets/icon_walnut_dim.png";
};
