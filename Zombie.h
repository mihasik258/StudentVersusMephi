#pragma once


#include <string>
#include <unordered_map>
#include "Constants.h"
#include "Map.h"

//------------------------------------------------------------------------------
// Класс Zombie
//------------------------------------------------------------------------------
/**
 * @brief Представляет зомби, который перемещается по игровому полю и взаимодействует с растениями.
 */
class Zombie {
public:
    static constexpr int INIT_X = 900; ///< Начальная координата X для зомби.
    static constexpr int DX = 3; ///< Смещение по оси X для движения зомби.
    static constexpr int BYTE_TIME = 100; ///< Время укуса.
    static constexpr int CREATE_TIME = 1200; ///< Время создания студента.
    static constexpr int TIME = 22;
    static constexpr const char* HEALTHY_DIRECTORY =  "./Image_Assets/Zombie_healthy1.png";
    static constexpr const char* MIDDLE_DIRECTORY = "./Image_Assets/Zombie_healthy2.png";
    static constexpr const char* INJURED_DIRECTORY =  "./Image_Assets/Zombie_healthy3.png";
    static constexpr const char* HEALTHY_FREEZE_DIRECTORY = "./Image_Assets/Zombie_healthy1_freeze.png";
    static constexpr const char* MIDDLE_FREEZE_DIRECTORY = "./Image_Assets/Zombie_healthy2_freeze.png";
    static constexpr const char* INJURED_FREEZE_DIRECTORY = "./Image_Assets/Zombie_healthy3_freeze.png";
    static constexpr const char* HEALTHY_FIRE_DIRECTORY = "./Image_Assets/Zombie_healthy1_fire.png";
    static constexpr const char* MIDDLE_FIRE_DIRECTORY = "./Image_Assets/Zombie_healthy2_fire.png";
    static constexpr const char* INJURED_FIRE_DIRECTORY = "./Image_Assets/Zombie_healthy3_fire.png";
	std::string directory; ///< Путь к изображению, представляющему зомби.
    /**
     * @brief Конструктор зомби.
     * @param initial_x_location Начальная координата X.
     * @param initial_health Начальное здоровье.
     * @param moving Флаг движения.
     */
     Zombie();
    /**
     * @brief Добавляет эффект.
     */
    void addEffect(const std::string &effect);
    /**
     * @brief Убирает эффект.
     */
    void removeEffect(const std::string &effect);
    /**
     * @brief Двигает зомби влево на основе скорости.
     */
    void move();
    /**
     * @brief Обновляет изображение зомби в зависимости от его состояния.
     */
    void updateAppearance();
    /**
     * @brief Проверяет есть ли данный эффект в таблице.
     */
    [[nodiscard]] bool hasEffect(const std::string& effect_name) const;
    void draw(window &win, const Map<Block> &map) const;
    void startMoving();
    void stopMoving();
    bool isMoving() const;
    [[nodiscard]] std::vector<std::string> getActiveEffects() const;
    void applyDamage(int damage);
    [[nodiscard]] bool isDead() const;
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] int getSpeed() const;
    void setSpeed(int new_speed);
    [[nodiscard]] int xLocation() const;
    [[nodiscard]] int getRow() const;
    void setLocation(int l);
    void setRow(int l);
protected:
    int row; ///< Ряд, в котором находится зомби.
    int x_location; ///< Позиция по оси X.
private:
    int health; ///< Текущее здоровье зомби.
    bool is_moving; ///< Флаг, указывающий, двигается ли зомби.
    int speed; ///< Скорость движения зомби.
    std::unordered_map<std::string, bool> effects; ///< Эффекты, наложенные на зомби.
    /**
     * @brief Устанавливает изображение зомби.
     * Этот метод является вспомогательным и не должен быть доступен извне.
     */
};
