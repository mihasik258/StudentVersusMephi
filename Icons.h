#pragma once

#include "rsdl.hpp"
#include "Player.h"

//------------------------------------------------------------------------------
// Класс Icons
//------------------------------------------------------------------------------
/**
 * @brief Класс Icons
 * 
 * Управляет отображением и выбором иконок для различных растений.
 */
class Icons {
public:
    /**
     * @brief Структура данных для иконки.
     * 
     * Хранит информацию о выбранной иконке, цене, путях к изображениям для различных состояний и позиции.
     */
    struct IconData {
        bool is_chosen;               ///< Флаг, указывающий, выбрана ли иконка 
        int price;                    ///< Цена растения
        std::string icon_directory_dim;  ///< Путь к изображению иконки в темном состоянии 
        std::string icon_directory_bright; ///< Путь к изображению иконки в ярком состоянии 
        int icon_y_position;          ///< Позиция иконки по оси Y 
    };
    std::map<std::string, IconData> iconData; ///< Коллекция данных иконок
    /**
     * @brief Конструктор Icons.
     * Инициализирует иконки для различных типов растений.
     */
    Icons();
    /**
     * @brief Обновляет состояние выбранной иконки в зависимости от координаты Y мыши.
     * @param mouse_y Координата Y мыши.
     */
    void updateIconSelection(int mouse_y);
    /**
     * @brief Отображает панель иконок на экране.
     * @param win Окно для отображения.
     * @param player Игрок, использующий солнечные очки для выбора растений.
     */
    void displayIconBar(window &win, Player &player);
    /**
     * @brief Отображает общий интерфейс, включая панель иконок и другие элементы.
     * @param win Окно для отображения.
     * @param player Игрок, чье количество солнечных очков отображается.
     */
    void displayLayout(window &win, Player &player);
    static constexpr int BAR_WIDTH = 95;
    static constexpr int BAR_HEIGHT = 194;
    static constexpr int WIDTH = 95;
    static constexpr int HEIGHT = 60;
    static constexpr int X1 = 20;
    static constexpr int X2 = 113;
    static constexpr int Y1 = 102;
    static constexpr int Y2 = 402;
    static constexpr const char* DIRECTORY = "./Image_Assets/Item_Bar.png";
};

