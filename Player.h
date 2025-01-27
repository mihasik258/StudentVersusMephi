#pragma once


#include "Elements.h"

//------------------------------------------------------------------------------
// Класс Player
//------------------------------------------------------------------------------
/**
 * @brief Класс Player
 * 
 * Представляет игрока в игре, управляет количеством солнечных очков и обработкой 
 * кликов для подбора солнечных очков.
 */
class Player {
public:
    int sun_count; ///< Счетчик солнц.
    bool is_first_click_made; ///< проверка первого клика.
    std::string directory;
    /**
     * @brief Конструктор Player.
     * @param init_sun_count Начальное количество солнечных очков.
     * @param first_click Указывает, был ли сделан первый клик.
     */
    explicit Player(int init_sun_count = Sun::INIT_COUNT, bool first_click = false);
    /**
     * @brief Подбирает солнечное очко, если клик был совершен по нему.
     * @param elements Коллекция игровых объектов.
     * @param map Карта игрового поля.
     * @param mouse_x Координата X мыши.
     * @param mouse_y Координата Y мыши.
     * @param sun_picked Флаг, указывающий на то, что солнечное очко было подобрано.
     */
    void pick_sun_if_clicked_on(Elements & elements, const Map<Block> &map, int mouse_x, int mouse_y, bool & sun_picked);
};
