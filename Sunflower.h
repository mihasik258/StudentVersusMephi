#pragma once


#include "Plant.h"
#include "Sun.h"

//------------------------------------------------------------------------------
// Класс Sunflower
//------------------------------------------------------------------------------
/**
 * @brief Класс Sunflower
 * 
 * Растение, генерирующее солнца.
 */
class Sunflower : public Plant {
public:
    int last_sun_generated_time; ///< Время последнего генерации солнца.
    /**
     * @brief Конструктор Sunflower.
     * @param row Ряд на игровом поле.
     * @param col Колонка на игровом поле.
     */
    Sunflower(int row, int col);
    /**
     * @brief Проверяет, может ли Sunflower сгенерировать солнце.
     * @param current_time Текущее игровое время.
     * @return true, если генерация возможна.
     */
    [[nodiscard]] bool canGenerate(int current_time) const;
    /**
     * @brief Обновляет время последней генерации солнца.
     * @param current_time Текущее игровое время.
     */
    void updateTime(int current_time);
    void draw(window &win, const Map<Block> &map) const override;
    static constexpr int PRICE = 50;
    static constexpr int HP_LIMIT = 5;
    static constexpr int ICON_Y1 = 103;
    static constexpr const char* DIRECTORY = "./Image_Assets/Sunflower.png";
    static constexpr const char* ICON_BRIGHT_DIRECTORY = "./Image_Assets/icon_sunflower.png";
    static constexpr const char* ICON_DIM_DIRECTORY = "./Image_Assets/icon_sunflower_dim.png";
};

