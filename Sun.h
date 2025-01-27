#pragma once

//------------------------------------------------------------------------------
// Класс Sun
//------------------------------------------------------------------------------
/**
 * @brief Класс Sun
 * 
 * Представляет солнце, которое может генерироваться на игровом поле или растениями.
 */
class Sun {
public:
    /**
     * @brief Конструктор Sun.
     * @param row Ряд солнца.
     * @param col Колонка солнца.
     * @param y Позиция по Y.
     * @param wait Время ожидания.
     */
    Sun();
    /**
     * @brief Двигает солнце вниз.
     * @param lower_limit Нижняя граница для движения солнца.
     */
    void move(int lower_limit);
    static constexpr int DY = 2;
    static constexpr int INIT_Y = 5;
    static constexpr int WIDTH = 80;
    static constexpr int HEIGHT = 80;
    static constexpr int TIME = 4; 
	static constexpr int INIT_COUNT = 150;
    static constexpr int SUNFLOWER_TIME = 2000;
    static constexpr int SKY_TIME = 2000;
    static constexpr const char* DIRECTORY = "./Image_Assets/sun(1).png";
    void setFinalRow(int row);
    void setFinalCol(int col);
    void setYLocation(int y);
    void resetWaitSeconds();
    void incrementWaitSeconds() { ++wait_seconds; }
    int getFinalRow() const { return final_row; }
    int getFinalCol() const { return final_col; }
    int getYLocation() const { return y_location; }
    int getWaitSeconds() const { return wait_seconds; }
private:
    int final_row; ///< Ряд, в котором солнце должно остановиться.
    int final_col; ///< Колонка, в которой солнце должно остановиться.
    int y_location; ///< Текущее положение по оси Y.
    int wait_seconds; ///< Время ожидания после остановки
};

